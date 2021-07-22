class GraphSelectPlayTimeMode {
	constructor(project, graphCanvas, player) {
		if (!(project instanceof Project))
			throw new Error('Project required.');
		if (!(graphCanvas instanceof GraphCanvas))
			throw new Error('GraphCanvas required.');
		if (!(player instanceof Player))
			throw new Error('Player required.');
		this.project = project;
		this.graphCanvas = graphCanvas;
		this.player = player;
		this.keyValue = 'select-play-time';
	}

	processClick(key, seconds, units) {
		this.player.setTimeSeconds(seconds);
		this.player.sendCSVStateToServer();
	}

	drawCursorAt(g, x, y) {
		g.strokeStyle = '#ddd';
		g.moveTo(x, 0);
		g.lineTo(x, this.graphCanvas.h - this.graphCanvas.axisPadding.bottom);
		g.stroke();
	}
}