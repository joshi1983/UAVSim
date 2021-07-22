class GraphZoomReset {
	constructor(project, graphCanvas) {
		if (!(project instanceof Project))
			throw new Error('Project required.');
		if (!(graphCanvas instanceof GraphCanvas))
			throw new Error('GraphCanvas required.');

		const e = document.getElementById('graph-zoom-reset');
		e.addEventListener('click', function() {
			const bounds = project.getBoundingRect(graphCanvas.activeKey);
			graphCanvas.startTime = bounds.minTimeSeconds;
			graphCanvas.verticalOffset = bounds.minValue;
			graphCanvas.verticalScale = bounds.maxValue - bounds.minValue;
			graphCanvas.horizontalScale = bounds.maxTimeSeconds - bounds.minTimeSeconds;
			graphCanvas.requestRedraw();
		});
	}
}