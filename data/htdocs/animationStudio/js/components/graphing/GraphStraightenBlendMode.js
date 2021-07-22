class GraphStraightenBlendMode extends AbstractGraphUpdateBlendMode {
	constructor(project, graphCanvas) {
		super(project, graphCanvas, 'blend-mode-straight', new StraightBlendFunction());
	}
}