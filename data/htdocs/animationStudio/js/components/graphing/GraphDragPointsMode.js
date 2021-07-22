class GraphDragPointsMode {
	constructor(project, graphCanvas) {
		this.project = project;
		this.graphCanvas = graphCanvas;
		this.keyValue = 'graph-drag-points-mode';
		this.from = undefined; // not dragging yet.
	}

	onModeExit() {
		this.from = undefined; // quit any pending drag operation.
	}

	processClick(key, seconds, units) {
		if (this.from === undefined || this.from.key !== key) {
			this.from = {
				'seconds': seconds,
				'units': units,
				'key': key,
				'pointQuery': GraphDeletePointMode.getPointQueryInfo(seconds, units, this.graphCanvas)
			}
			if (!this.project.areAnyPointsFound(key, this.from.pointQuery)) {
				this.from = undefined; // no need to start a drag operation if no points will be moved.
			}
		}
		else {
			// process drag end stage.
			this.project.displacePoints(key, this.from.pointQuery, {
				'time': seconds - this.from.seconds,
				'value': units - this.from.units});
			this.from = undefined; // drag operation is complete.
		}
	}

	drawCursorAt(g, x, y) {
		GraphDeletePointMode.drawSquareCursorAt(g, x, y, this.from === undefined ? 'rgba(0,0,0,0.3)' : 'rgba(0,150,0,0.4)');
	}
}