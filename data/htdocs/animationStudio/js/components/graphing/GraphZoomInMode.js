class GraphZoomInMode {
	constructor(graphCanvas) {
		if (!(graphCanvas instanceof GraphCanvas))
			throw new Error('GraphCanvas required.');
		this.graphCanvas = graphCanvas;
		this.keyValue = 'zoom-in';
	}

	static getZoomStep() {
		return 0.7;
	}

	processClick(key, seconds, units) {
		const zoomStep = GraphZoomInMode.getZoomStep();
		var newWidth = this.graphCanvas.horizontalScale * zoomStep;
		var newHeight = this.graphCanvas.verticalScale * zoomStep;
		var newStartTime = (seconds - newWidth * 0.5);
		var newVerticalOffset = (units - newHeight * 0.5);
		this.graphCanvas.startTime = newStartTime;
		this.graphCanvas.verticalOffset = newVerticalOffset;
		this.graphCanvas.horizontalScale = newWidth;
		this.graphCanvas.verticalScale = newHeight;
		this.graphCanvas.requestRedraw();
	}
}