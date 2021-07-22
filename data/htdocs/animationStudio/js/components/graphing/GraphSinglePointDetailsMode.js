class GraphSinglePointDetailsMode extends Dialog {
	constructor(project, graphCanvas) {
		if (!(project instanceof Project))
			throw new Error('Project required');
		if (!(graphCanvas instanceof GraphCanvas))
			throw new Error('GraphCanvas required');

		super('data-point-details');
		this.project = project;
		this.graphCanvas = graphCanvas;
		this.keyValue = 'single-point-details';

		const close = document.getElementById('graph-data-point-details-close');
		const outer = this;
		close.addEventListener('click', function() {
			outer.hide();
		});
		this.timeElement = document.getElementById('graph-data-point-details-time');
		this.valueElement = document.getElementById('graph-data-point-details-value');
		this.curveTypeElement = document.getElementById('graph-data-point-details-curve-type');
		const optionsData = BlendFunctionFactory.getSelectableBlendFunctions();
		optionsData.forEach(function(optionData) {
			const option = document.createElement('option');
			option.innerText = optionData.getOptionName();
			outer.curveTypeElement.appendChild(option);
		});
		this.curveTypeElement.addEventListener('change', function() {
			const val = outer.curveTypeElement.value;
			const matchingOption = optionsData.filter(function(optionData) {
				return optionData.getOptionName() === val;
			})[0];
			if (matchingOption !== undefined) {
				outer.project.updatePoint(graphCanvas.activeKey, outer.dataPoint, {'blendFunc': matchingOption.getSerializableData()});
			}
		});
		this.timeElement.addEventListener('change', function() {
			const time = parseFloat(outer.timeElement.value);
			if (typeof time === 'number' && !isNaN(time))
				outer.project.updatePoint(graphCanvas.activeKey, outer.dataPoint, {'time': time});
		});
		this.valueElement.addEventListener('change', function() {
			const value = parseFloat(outer.valueElement.value);
			if (typeof value === 'number' && !isNaN(value))
				outer.project.updatePoint(graphCanvas.activeKey, outer.dataPoint, {'value': value});
		});
	}

	showDetails(dataPoint) {
		if (!(dataPoint instanceof DataPoint))
			throw new Error('DataPoint required.');

		this.dataPoint = dataPoint;
		this.timeElement.value = dataPoint.time;
		this.valueElement.value = dataPoint.value;
		this.curveTypeElement.value = dataPoint.blendFunction.getOptionName();
		this.show();
	}

	processClick(key, seconds, units) {
		const queryInfo = GraphDeletePointMode.getPointQueryInfo(seconds, units, this.graphCanvas);
		const dataPoint = this.project.getSinglePointAt(this.graphCanvas.activeKey, queryInfo);
		if (dataPoint !== undefined)
			this.showDetails(dataPoint);
	}

	drawCursorAt(g, x, y) {
		const seconds = this.graphCanvas._pixelsToSeconds(x);
		const units = this.graphCanvas._pixelsToUnits(y);
		const queryInfo = GraphDeletePointMode.getPointQueryInfo(seconds, units, this.graphCanvas);
		const dataPoint = this.project.getSinglePointAt(this.graphCanvas.activeKey, queryInfo);
		var colour;
		if (dataPoint === undefined)
			colour = '#ddd';
		else
			colour = '#000';

		GraphDeletePointMode.drawSquareCursorAt(g, x, y, colour);
	}	
}