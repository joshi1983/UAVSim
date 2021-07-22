class GraphCursorPositionViewer {
	constructor(graphCanvas) {
		if (!(graphCanvas instanceof GraphCanvas))
			throw new Error('GraphCanvas required');
		const span = document.getElementById('graph-cursor-position');
		graphCanvas.addEventListener(function(event) {
			if (event.key === 'cursor_moved') {
				span.innerText = 'seconds: ' + event.seconds.toFixed(3) + ', value: ' + event.value.toFixed(3);
			}
			else if (event.key === 'cursor_exited') {
				span.innerText = '';
			}
		});
	}
}