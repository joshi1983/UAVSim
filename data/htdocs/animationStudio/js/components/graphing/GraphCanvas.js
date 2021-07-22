class GraphCanvas extends EventDispatcher {
	constructor(project, player) {
		super();
		this.project = project;
		this.canvas = document.querySelector('#graph-canvas-container > canvas');
		this.player = player;
		this.horizontalScale = 100;
		this.startTime = 10;
		this.verticalOffset = 0;
		this.verticalScale = 10;
		this.activeKey = '';
		this.axisPadding = {
			'left': 40,
			'bottom': 20
		};
		this.inputMode = new GraphCanvasModes(project, this, player);
		this.draw();
		this._bindEvents();
	}

	_bindEvents() {
		const outer = this;

		function eventToPoint(event) {
			// get point coordinates relative to canvas.
			const box = outer.canvas.getBoundingClientRect();
			var x, y;
			if (!isNaN(event.clientX) && !isNaN(event.clientY)) {
				x = event.clientX - box.left;
				y = event.clientY - box.top;
			}
			else if (event.touches.length > 0) {
				x = event.touches[0].clientX - box.left;
				y = event.touches[0].clientY - box.top;
			}
			else {
				console.error('Unable to determine canvasDown coordinates');
				return;
			}
			return {
				'x': x,
				'y': y
			};
		}

		function canvasDown(event) {
			// convert pixels to units and seconds.
			var {x, y} = eventToPoint(event);
			const seconds = outer._pixelsToSeconds(x);
			const units = outer._pixelsToUnits(y);
			outer.inputMode.downPoint(outer.activeKey, seconds, units);
			outer.draw();
		}

		function canvasMove(event) {
			// convert pixels to units and seconds.
			const {x, y} = eventToPoint(event);
			const seconds = outer._pixelsToSeconds(x);
			const units = outer._pixelsToUnits(y);
			outer._dispatchEvent({'key': 'cursor_moved', 'seconds': seconds, 'value': units});
			outer.latestPoint = {'x': x, 'y': y};
			outer.requestRedraw();
		}
		function canvasExit(event) {
			outer.latestPoint = undefined;
			outer._dispatchEvent({'key': 'cursor_exited'});
			outer.requestRedraw();
		}
		this.player.addEventListener(function(e) {
			if (e.key === 'player-time-changed')
				outer.requestRedraw();
		});
		this.canvas.addEventListener('mousedown', canvasDown);
		this.canvas.addEventListener('touchstart', canvasDown);
		this.canvas.addEventListener('mousemove', canvasMove);
		this.canvas.addEventListener('mouseexit', canvasExit);
		window.addEventListener('resize', function() {
			outer.requestRedraw();
		});
	}

	requestRedraw() {
		if (this._redrawRequested)
			return; // nothing to do.  A redraw is already requested.

		this._redrawRequested = true;
		const outer = this;
		requestAnimationFrame(function() {
			outer.draw();
		});
	}

	setActiveKey(newKey) {
		// check if there is anything to change.
		if (newKey !== this.activeKey) {
			this.activeKey = newKey;
			this.draw();
		}
	}

	_secondsToPixels(seconds) {
		return (seconds - this.startTime) * this.scale.x + this.axisPadding.left;
	}

	_pixelsToSeconds(pixels) {
		return (pixels - this.axisPadding.left) / this.scale.x + this.startTime;
	}

	pixelsToSecondsScaleOnly(pixels) {
		return pixels / this.scale.x;
	}

	pixelsToUnitsScaleOnly(pixels) {
		return pixels / this.scale.y;
	}

	_unitsToPixels(units) {
		return (this.h - this.axisPadding.bottom) - (units - this.verticalOffset) * this.scale.y;
	}

	_pixelsToUnits(pixels) {
		return (this.h - this.axisPadding.bottom - pixels) / this.scale.y + this.verticalOffset;
	}

	_drawVerticalLines() {
		const secondsWidth = this.horizontalScale;
		const verticalGridLineInterval = GraphCanvasGrid.getTimeIntervalFromSecondsWidth(secondsWidth);
		this.g.strokeStyle = '#bbb';
		var offsetSeconds = Math.floor(this.startTime/verticalGridLineInterval)*verticalGridLineInterval;
		for (let i = 0;i < 1000;i++) {
			const t = offsetSeconds + i * verticalGridLineInterval;
			const x = this._secondsToPixels(t);
			if (x > this.w || isNaN(x))
				break;
			else if (x > this.axisPadding.left) {
				this.g.beginPath();
				this.g.moveTo(x, 0);
				this.g.lineTo(x, this.h - this.axisPadding.bottom);
				this.g.stroke();
				this.g.closePath();
				this.g.fillText(Math.round(this._pixelsToSeconds(x)), x - 5, this.h - this.axisPadding.bottom + 12);
			}
		}
	}

	_drawHorizontalLines() {
		const unitsHeight = this.verticalScale;
		const horizontalGridLineInterval = GraphCanvasGrid.getUnitsIntervalFromUnitsHeight(unitsHeight);
		const offsetUnits = 0;
		this.g.strokeStyle = '#bbb';
		for (let i = 0;i < 1000;i++) {
			const u = offsetUnits + i * horizontalGridLineInterval;
			const y = this._unitsToPixels(u);
			if (y > this.h - this.axisPadding.bottom || isNaN(y))
				break;
			else if (y > 0) {
				this.g.beginPath();
				this.g.moveTo(this.axisPadding.left, y);
				this.g.lineTo(this.w, y);
				this.g.stroke();
				this.g.closePath();
				this.g.fillText(Math.round(u), 10, y + 7);
			}
		}
	}

	_drawGrid() {
		this._drawVerticalLines();
		this._drawHorizontalLines();
	}

	_drawLineGraph() {
		const step = 1;
		this.g.strokeStyle = '#008';
		this.g.beginPath();
		let firstIteration = true;
		for (let x = this.axisPadding.left; x < this.w; x += step) {
			const unitsY = this.project.getValue(this.activeKey, this._pixelsToSeconds(x));
			const pxY = this._unitsToPixels(unitsY);
			if (firstIteration) {
				this.g.moveTo(x, pxY);
				firstIteration = false;
			}
			else
				this.g.lineTo(x, pxY);
		}
		this.g.stroke();
		this.g.closePath();
	}

	_drawPoints() {
		const outer = this;
		this.g.fillStyle = '#008';
		this.project.getDataPointsFor(this.activeKey).forEach(function(dataPoint) {
			const px = outer._secondsToPixels(dataPoint.time);
			const py = outer._unitsToPixels(dataPoint.value);
			outer.g.beginPath();
			outer.g.arc(px, py, 5, 0, 2 * Math.PI, false);
			outer.g.closePath();
			outer.g.fill();
		});
	}

	draw() {
		const box = this.canvas.parentNode.getBoundingClientRect();
		this.w = Math.round(box.width);
		this.h = Math.round(box.height);
		if (this.w < 1 || this.h < 1)
			return; // avoid drawing when the dimensions make the canvas nearly invisible.

		this.canvas.setAttribute('width', this.w);
		this.canvas.setAttribute('height', this.h);
		this.g = this.canvas.getContext('2d');
		this.scale = {
			'x': (this.w - this.axisPadding.left)/this.horizontalScale, // pixels per second
			'y': (this.h - this.axisPadding.bottom)/this.verticalScale // pixels per unit
		};
		this.g.clearRect(0, 0, this.w, this.h);
		this.g.strokeStyle = '#000';
		this.g.beginPath();
		this.g.moveTo(this.axisPadding.left, 0);
		this.g.lineTo(this.axisPadding.left, this.h - this.axisPadding.bottom);
		this.g.lineTo(this.w, this.h - this.axisPadding.bottom);
		this.g.stroke();
		this.g.closePath();
		const outer = this;
		var verticalLines = [{'time': this.project.getDurationSeconds(), 'colour': '#800'}];
		verticalLines.push({'time': this.player.getTimeSeconds(), 'colour': '#080'});
		verticalLines.forEach(function(line) {
			var px = outer._secondsToPixels(line.time);
			if (px > outer.axisPadding.left) {
				outer.g.strokeStyle = line.colour;
				// draw vertical line at the duration limit.
				outer.g.beginPath();
				outer.g.moveTo(px, 0);
				outer.g.lineTo(px, outer.h - outer.axisPadding.bottom);
				outer.g.closePath();
				outer.g.stroke();
			}
		});
		this._drawGrid();
		this._drawLineGraph();
		this._drawPoints();
		if (this.latestPoint !== undefined)
			this.inputMode.movePoint(this.latestPoint.x, this.latestPoint.y);
		this._redrawRequested = false; // indicate request complete.
	}
}