class Graph {
	constructor(project, csvInputs, player, virtualAnimationStateKeys) {
		if (!(project instanceof Project))
			throw new Error('Graph requires Project');
		if (!(csvInputs instanceof CsvInputsRepository))
			throw new Error('csvInputs required');
		if (!(player instanceof Player))
			throw new Error('Player required.');
		if (!(virtualAnimationStateKeys instanceof VirtualAnimationStateKeys))
			throw new Error('virtualAnimationStateKeys required.');

		this.virtualAnimationStateKeys = virtualAnimationStateKeys;
		this.project = project;
		this.csvInputs = csvInputs;
		this.player = player;
		this._updateDOMAndBindEvents();
	}

	_updateDOMAndBindEvents() {
		this.e = document.getElementById('graph');
		this.graphCanvas = new GraphCanvas(this.project, this.player);
		const outer = this;
		this.project.addEventListener(function(event) {
			if (event.key === 'pointAutoRemoved') {
				console.error('A point or points were automatically removed.');
			}
			else {
				outer.graphCanvas.requestRedraw();
			}
		});
		new GraphVerticalScale(this.graphCanvas);
		new GraphZoomReset(this.project, this.graphCanvas);
		new GraphCursorPositionViewer(this.graphCanvas);
		const zoomOut = document.getElementById('graph-zoom-out');
		const zoomChangeFactor = 0.7;
		zoomOut.addEventListener('click', function() {
			const oldMiddleTime = outer.graphCanvas.horizontalScale * 0.5 + outer.graphCanvas.startTime;
			const oldMiddleValue = outer.graphCanvas.verticalScale * 0.5 + outer.graphCanvas.verticalOffset;
			outer.graphCanvas.horizontalScale /= zoomChangeFactor;
			outer.graphCanvas.verticalScale /= zoomChangeFactor;
			outer.graphCanvas.startTime = oldMiddleTime - outer.graphCanvas.horizontalScale * 0.5;
			outer.graphCanvas.verticalOffset = oldMiddleValue - outer.graphCanvas.verticalScale * 0.5;
			outer.graphCanvas.requestRedraw();
		});
		const csvKeySelector = document.getElementById('active-csv-key');
		function activeKeyChanged() {
			outer.graphCanvas.setActiveKey(csvKeySelector.value);
		}
		csvKeySelector.addEventListener('change', activeKeyChanged);
		this.csvInputs.refreshCsvInputs().then(function() {
			const allKeys = outer.csvInputs.getNumericCsvInputKeys().concat(outer.virtualAnimationStateKeys.getVirtualKeyStrings());
			allKeys.sort();
			const keys = allKeys.forEach(function(key, index) {
				const option = document.createElement('option');
				option.innerText = key;
				if (index === 0)
					option.setAttribute('selected', 'selected');
				csvKeySelector.appendChild(option);
			});
			activeKeyChanged(); // call after options are added to DOM.
		});
	}
}