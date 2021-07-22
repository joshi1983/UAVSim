class GraphParabolizeBlendMode extends AbstractGraphUpdateBlendMode {
	constructor(project, graphCanvas) {
		super(project, graphCanvas, 'blend-mode-parabolic', new ParabolicBlendFunction());
	}
}