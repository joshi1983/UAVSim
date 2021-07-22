class GraphCanvasModes {
	constructor(project, graphCanvas, player) {
		this.graphCanvas = graphCanvas;
		const e = document.getElementById('graph-modes');
		const modeInstances = [
			new GraphAddPointMode(project),
			new GraphDeletePointMode(project, graphCanvas),
			new GraphZoomInMode(graphCanvas),
			new GraphParabolizeBlendMode(project, graphCanvas),
			new GraphStraightenBlendMode(project, graphCanvas),
			new GraphDragPointsMode(project, graphCanvas),
			new GraphSelectPlayTimeMode(project, graphCanvas, player),
			new GraphSinglePointDetailsMode(project, graphCanvas)
		];
		const modesMap = {};
		modeInstances.forEach(function(mode) {
			modesMap[mode.keyValue] = mode;
		});
		const inputs = e.querySelectorAll('input[name="graph-mode"]');
		const outer = this;
		function modeChanged() {
			const checkedInput = e.querySelector('input[name="graph-mode"]:checked');
			// if a change is happening
			if (outer.mode === undefined || outer.mode.keyValue !== checkedInput.value) {
				if (outer.mode !== undefined && typeof outer.mode.onExitMode === 'function')
					outer.mode.onExitMode();
				outer.mode = modesMap[checkedInput.value];
				if (outer.mode === undefined)
					throw new Error("Unable to find mode for value " + checkedInput.value);
			}
		}
		inputs.forEach(function(input) {
			input.addEventListener('change', modeChanged);
		});
		modeChanged();
	}

	downPoint(activeKey, seconds, units) {
		this.mode.processClick(activeKey, seconds, units);
	}

	movePoint(x, y) {
		if (typeof this.mode.drawCursorAt === 'function') {
			const g = this.graphCanvas.canvas.getContext('2d');
			this.mode.drawCursorAt(g, x, y);
		}
	}
}