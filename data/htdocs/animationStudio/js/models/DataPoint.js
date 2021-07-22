class DataPoint {
	constructor(data) {
		if (typeof data !== 'object')
			throw new Error('data must be an object.');
		if (typeof data.time !== 'number' || isNaN(data.time)) {
			console.error('Invalid DataPoint data in: ', data);
			throw new Error('time must be a number.');
		}
		if (typeof data.value !== 'number' || isNaN(data.value))
			throw new Error('value must be a number.');

		this.blendFunction = BlendFunctionFactory.createFrom(data.blendFunc);
		this.applyChanges(data);
		this.previousSlope = 0; // updated by Project.
	}

	applyChanges(changes) {
		if (typeof changes !== 'object')
			throw new Error('applyChanges requires an object.');
		if (typeof changes.time === 'number' && !isNaN(changes.time))
			this.time = changes.time;
		if (typeof changes.value === 'number' && !isNaN(changes.value))
			this.value = changes.value;
		if (changes.blendFunc !== undefined)
			this.blendFunction = BlendFunctionFactory.createFrom(changes.blendFunc);
	}

	getSerializableData() {
		return {
			'time': this.time,
			'value': this.value,
			'blendFunc': this.blendFunction.getSerializableData()
		};
	}

	getEndingSlope(info) {
		return this.blendFunction.getEndingSlope(info);
	}

	blend(info, time) {
		return this.blendFunction.blend(info, time);
	}

	matchesQuery(querySettings) {
		if (typeof querySettings !== 'object') {
			console.error('Object expected instead of: ', querySettings);
			throw new Error('matchesQuery requires a querySettings object.');
		}
		if (typeof querySettings.minTime === 'number' && this.time < querySettings.minTime)
			return false;
		if (typeof querySettings.maxTime === 'number' && this.time > querySettings.maxTime)
			return false;
		if (typeof querySettings.minValue === 'number' && this.value < querySettings.minValue)
			return false;
		if (typeof querySettings.maxValue === 'number' && this.value > querySettings.maxValue)
			return false;
		return true;
	}
}