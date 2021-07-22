class GraphDeletePointMode {
	constructor(project, graphCanvas) {
		if (!(project instanceof Project))
			throw new Error('Project required.');
		if (!(graphCanvas instanceof GraphCanvas))
			throw new Error('GraphCanvas required.');
		this.project = project;
		this.graphCanvas = graphCanvas;
		this.keyValue = 'delete-point';
	}

	processClick(key, seconds, units) {
		this.project.deletePoints(key, GraphDeletePointMode.getPointQueryInfo(seconds, units, this.graphCanvas));
	}

	static getPointQueryInfo(seconds, units, graphCanvas) {
		if (typeof seconds !== 'number')
			throw new Error('seconds number required.');
		if (typeof units !== 'number')
			throw new Error('units number required.');
		if (!(graphCanvas instanceof GraphCanvas))
			throw new Error('GraphCanvas required.');

		const range = GraphDeletePointMode.range;
		const timeDelta = graphCanvas.pixelsToSecondsScaleOnly(range);
		const valueDelta = graphCanvas.pixelsToUnitsScaleOnly(range);
		return {
			'minTime': seconds - timeDelta,
			'maxTime': seconds + timeDelta,
			'minValue': units - valueDelta,
			'maxValue': units + valueDelta
		};
	}

	static drawSquareCursorAt(g, x, y, colour) {
		const range = GraphDeletePointMode.range;
		if (typeof colour !== 'string')
			colour = 'rgba(0, 0, 0, 0.3)';
		g.fillStyle = colour;
		g.fillRect(x - range, y - range, range*2, range*2);
	}

	drawCursorAt(g, x, y) {
		GraphDeletePointMode.drawSquareCursorAt(g, x, y);
	}
}

GraphDeletePointMode.range = 5;