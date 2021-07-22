class Project extends EventDispatcher {
	constructor(projectSettings) {
		super();
		if (typeof projectSettings !== 'object') {
			projectSettings = {
				'isAutoSaving': true,
				'isAutoLoading': true
			};
		}
		this._settings = projectSettings;
		this.localStorageKey = 'animationProject';
		this._dataPoints = {};
		this._durationSeconds = 100;
		this.listeners = [];
		this._loadFromLocalStorage();
	}

	getDurationSeconds() {
		return this._durationSeconds;
	}

	getBoundingRect(key) {
		if (typeof key !== 'string')
			throw new Error('key string required.');
		var maxTimeSeconds = this.getDurationSeconds();
		var maxValue = -Number.MAX_VALUE;
		var minValue = Number.MAX_VALUE;
		var minTimeSeconds = 0;
		if (this._dataPoints[key] === undefined || this._dataPoints[key].length === 0)
		{
			maxValue = 1;
			minValue = 0;
		}
		else {
			// get range for points.
			this._dataPoints[key].forEach(function(dp) {
				maxValue = Math.max(maxValue, dp.value);
				minValue = Math.min(minValue, dp.value);
				minTimeSeconds = Math.min(minTimeSeconds, dp.time);
				maxTimeSeconds = Math.max(maxTimeSeconds, dp.time);
			});
			// Curves may extend the range so sample at many times.
			const numSamples = 1000;
			for (var i = 0; i < numSamples; i++) {
				const seconds = minTimeSeconds + i * (maxTimeSeconds - minTimeSeconds) / numSamples;
				const v = this.getValue(key, seconds);
				minValue = Math.min(minValue, v);
				maxValue = Math.max(maxValue, v);
			}
		}

		return {
			'minValue': minValue,
			'maxValue': maxValue,
			'minTimeSeconds': minTimeSeconds,
			'maxTimeSeconds': maxTimeSeconds
		};
	}

	setDurationSeconds(newDurationSeconds) {
		if (typeof newDurationSeconds !== 'number' || isNaN(newDurationSeconds))
			throw new Error('number required.');

		this._durationSeconds = newDurationSeconds;
		this._dispatchEvent({'key': 'durationChange'});
		this._saveToLocalStorage();
	}

	getProjectData() {
		const serializableDataPoints = {};
		for (var key in this._dataPoints) {
			serializableDataPoints[key] = this._dataPoints[key].map(function(dp) {
				return dp.getSerializableData();
			});
		}
		var result = {
			'durationSeconds': this._durationSeconds,
			'dataPoints': serializableDataPoints
		};
		return result;
	}

	setProjectData(newProjectData) {
		if (typeof newProjectData === 'string') {
			try {
				newProjectData = JSON.parse(newProjectData);
			}
			catch (e) {
				console.error('Giving up on loading project due to the following parse error.');
				console.error(e);
				return;
			}
		}
		if (typeof newProjectData !== 'object') {
			console.error('project data must be an object');
			return;
		}
		if (typeof newProjectData.durationSeconds === 'number') {
			this._durationSeconds = newProjectData.durationSeconds;
		}
		if (typeof newProjectData.dataPoints === 'object') {
			this.dataPoints = {};
			for (let key in newProjectData.dataPoints) {
				if (!key) // ignore data associated with empty keys.
					continue;
				this._dataPoints[key] = newProjectData.dataPoints[key].map(function(dataPointData) {
					return new DataPoint(dataPointData);
				});
				// sanitize a bit in case input points are out of order or don't have correct slopes.
				this._sortPoints(key);
				this._removePointsTooClose(key);
				this._refreshSlopes(key);
			}
		}
		this._dispatchEvent({'key': 'loaded'});
	}

	_loadFromLocalStorage() {
		if (!this._settings.isAutoLoading)
			return;

		const projectData = localStorage.getItem(this.localStorageKey);
		if (projectData !== null)
			this.setProjectData(projectData);
	}

	_saveToLocalStorage() {
		if (!this._settings.isAutoSaving)
			return;
		const projectData = JSON.stringify(this.getProjectData());
		localStorage.setItem(this.localStorageKey, projectData);
	}

	getDataPointsFor(key) {
		if (this._dataPoints[key] === undefined)
			return [];
		return this._dataPoints[key];
	}

	static findIndexJustAfter(time, dataPoints) {
		if (typeof time !== 'number')
			throw new Error('time must be a number.');
		if (!(dataPoints instanceof Array))
			throw new Error('dataPoints must be an Array.');

		// perform binary search.
		var startIndex = 0;
		var endIndex = dataPoints.length - 1;
		if (dataPoints.length === 0 || dataPoints[endIndex].time < time)
			return undefined; // indicate no index is after the specified time.
		while (startIndex < endIndex) {
			var midIndex = Math.floor((startIndex + endIndex) * 0.5);
			const e = dataPoints[midIndex];
			if (e.time > time) {
				endIndex = midIndex;
			}
			else if (e.time < time) {
				startIndex = midIndex + 1;
			}
			else
				return midIndex + 1;
		}
		return Math.max(0, endIndex);
	}

	addPoint(key, dataPoint) {
		if (!key)
			throw new Error('key must not be empty');
		if (typeof key !== 'string')
			throw new Error('key must be a string.');
		if (!(dataPoint instanceof DataPoint) || dataPoint === undefined)
			throw new Error('addPoint requires a DataPoint instance.');
		if (this._dataPoints[key] === undefined)
			this._dataPoints[key] = [];
		var isInserted = false;
		// find the index to insert into.
		const dp = this._dataPoints[key];
		const afterIndex = Project.findIndexJustAfter(dataPoint.time, dp);
		if (afterIndex === undefined) {
			dp.push(dataPoint);
		}
		else if (afterIndex > 0 && dp[afterIndex - 1].time === dataPoint.time)
			dp[afterIndex - 1].value = dataPoint.value;
		else {
			this._dataPoints[key].splice(afterIndex, 0, dataPoint);
		}
		this._refreshSlopes(key);
		this._dispatchEvent({'key': 'pointAdded'});
		this._saveToLocalStorage();
	}

	clear(key) {
		this._dataPoints[key] = undefined;
		this._saveToLocalStorage();
	}

	_sortPoints(key) {
		this._dataPoints[key].sort(function(dp1, dp2) {
			return dp1.time - dp2.time;
		});
	}

	_refreshSlopes(key) {
		const dp = this._dataPoints[key];
		if (dp.length === 0)
			return; // nothing to do.
		dp[0].previousSlope = 0;
		for (var i = 1; i < dp.length; i++) {
			const info = {
				'from': dp[i - 1],
				'to': dp[i]
			};
			dp[i].previousSlope = dp[i - 1].getEndingSlope(info);
		}
	}

	deletePoints(key, querySettings) {
		if (typeof key !== 'string')
			throw new Error('key must be a string.');
		if (this._dataPoints[key] === undefined) // nothing to delete.
			return;

		const oldLength = this._dataPoints[key].length;
		this._dataPoints[key] = this._dataPoints[key].filter(function(dataPoint) {
			return !dataPoint.matchesQuery(querySettings);
		});

		// if something was deleted, save.
		if (oldLength !== this._dataPoints[key].length) {
			this._refreshSlopes(key);
			this._dispatchEvent({'key': 'pointDeleted'});
			this._saveToLocalStorage();
		}
	}

	_queryPoints(key, querySettings) {
		if (typeof querySettings !== 'object')
			throw new Error('_queryPoints requires a querySettings object.');
		return this._dataPoints[key].filter(function(dataPoint) {
			return dataPoint.matchesQuery(querySettings);
		});
	}

	areAnyPointsFound(key, querySettings) {
		return this._queryPoints(key, querySettings).length !== 0;
	}

	/*
	When points have matching time, the slope calculation can be problematic.
	To prevent these problems, there is a minimum time change threshold.
	Points that are too close together will be removed until each remaining point meets the minimum threshold.

	This assumes the points are already sorted.
	*/
	_removePointsTooClose(key) {
		const dp = this._dataPoints[key];
		const minTimeChange = 0.005;
		const pointsToRemove = new Set();
		for (var i = 1; i < dp.length; i++) {
			if (dp[i].time - dp[i - 1].time < minTimeChange) {
				pointsToRemove.add(dp[i - 1]);
			}
		}
		if (pointsToRemove.size > 0) {
			this._dispatchEvent({'key': 'pointAutoRemoved', 'numPoints': pointsToRemove.size, 'csvKey': key});
			console.error(pointsToRemove.size + ' points are being automatically removed for key ' + key);
			this._dataPoints[key] = dp.filter(function(point) {
				return !pointsToRemove.has(point);
			});
		}
	}

	_respondToPointDisplacement(key) {
		this._sortPoints(key);
		this._removePointsTooClose(key);
		this._refreshSlopes(key);
		this._dispatchEvent({'key': 'pointDisplaced'});
		this._saveToLocalStorage();
	}

	displacePoints(key, pointQuery, displacement) {
		if (typeof pointQuery !== 'object')
			throw new Error('displacePoints requires a pointQuery object.');
		if (typeof displacement !== 'object' || isNaN(displacement.time) || isNaN(displacement.value)) {
			throw new Error('displacePoints given invalid displacement parameter.');
		}
		var points = this._queryPoints(key, pointQuery);
		points.forEach(function(dataPoint) {
			dataPoint.time += displacement.time;
			dataPoint.value += displacement.value;
		});
		this._respondToPointDisplacement(key);
	}

	// Don't mutate the returned point directly.
	// Call updatePoint so the required updates are made on this project.
	getSinglePointAt(key, queryInfo) {
		var matchedPoints = this._queryPoints(key, queryInfo);
		if (matchedPoints.length === 1)
			return matchedPoints[0];
	}

	updatePoint(key, dataPoint, changes) {
		if (typeof key !== 'string')
			throw new Error('key must be a string.');
		if (!(dataPoint instanceof DataPoint))
			throw new Error('DataPoint required.');
		if (typeof changes !== 'object')
			throw new Error('changes must be an object.');
		dataPoint.applyChanges(changes);
		this._respondToPointDisplacement(key);
	}

	setBlendFunctionForPoints(key, querySettings, newBlendFunction) {
		if (typeof newBlendFunction !== 'object')
			throw new Error('blend function must be an object');
		var affectedPoints = this._queryPoints(key, querySettings);
		if (affectedPoints.length !== 0) {
			affectedPoints.forEach(function(dp) {
				dp.blendFunction = newBlendFunction;
			});
			this._refreshSlopes(key);
			this._dispatchEvent({'key': 'pointEdited'});
			this._saveToLocalStorage();
		}
	}

	getCsvKeys() {
		return Object.keys(this._dataPoints);
	}

	getValue(key, time) {
		if (typeof key !== 'string')
			throw new Error('key must be a string.');
		if (typeof time !== 'number')
			throw new Error('time must be number.');
		if (this._dataPoints[key] === undefined || this._dataPoints[key].length === 0) {
			return 0;
		}
		const lastDataPoint = this._dataPoints[key][this._dataPoints[key].length - 1];
		if (lastDataPoint.time < time)
			return lastDataPoint.value;
		else {
			const dp = this._dataPoints[key];
			const afterIndex = Project.findIndexJustAfter(time, dp);
			if (afterIndex === undefined || afterIndex === 0)
				return 0;
			else {
				return dp[afterIndex - 1].blend({
					'from': dp[afterIndex - 1],
					'to': dp[afterIndex]
				}, time);
			}
		}
	}
}