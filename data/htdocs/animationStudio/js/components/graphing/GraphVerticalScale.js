class GraphVerticalScale {
	constructor(graphCanvas) {
		if (!(graphCanvas instanceof GraphCanvas))
			throw new Error('GraphCanvas required.');

		const zoomStep = GraphZoomInMode.getZoomStep();
		const zoomIn = document.getElementById('graph-vertical-zoom-in');
		const zoomOut = document.getElementById('graph-vertical-zoom-out');
		function setNewVerticalScale(newVerticalScale) {
			var oldMiddleY = graphCanvas.verticalScale * 0.5 + graphCanvas.verticalOffset;
			graphCanvas.verticalScale = newVerticalScale;
			graphCanvas.verticalOffset = oldMiddleY - graphCanvas.verticalScale * 0.5;
			graphCanvas.requestRedraw();
		}
		zoomIn.addEventListener('click', function() {
			setNewVerticalScale(graphCanvas.verticalScale * zoomStep);
		});
		zoomOut.addEventListener('click', function() {
			setNewVerticalScale(graphCanvas.verticalScale / zoomStep);
		});
	}
}