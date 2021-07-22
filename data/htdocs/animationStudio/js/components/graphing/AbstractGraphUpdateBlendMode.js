class AbstractGraphUpdateBlendMode {
	constructor(project, graphCanvas, keyValue, blendFunction) {
		if (!(project instanceof Project))
			throw new Error('Project required.');
		if (!(graphCanvas instanceof GraphCanvas))
			throw new Error('GraphCanvas required.');
		this.project = project;
		this.graphCanvas = graphCanvas;
		this.keyValue = keyValue;
		this.blendFunction = blendFunction;
	}

	processClick(key, seconds, units) {
		this.project.setBlendFunctionForPoints(key,
			GraphDeletePointMode.getPointQueryInfo(seconds, units, this.graphCanvas),
			this.blendFunction);
	}

	drawCursorAt(g, x, y) {
		GraphDeletePointMode.drawSquareCursorAt(g, x, y);
	}
}