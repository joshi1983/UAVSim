document.addEventListener('DOMContentLoaded', function() {
	const resultsElement = document.getElementById('test-results');
	function addFailure(msg) {
		var p = document.createElement('p');
		p.innerText = msg;
		resultsElement.appendChild(p);
	}
	
	const project = new Project({'isAutoSaving': false, 'isAutoLoading': false});
	const testTimes = [{'time': 1, 'indexAfter': undefined}, 
		{'time': 10, 'indexAfter': undefined},
		{'time': 5, 'indexAfter': 1},
		{'time': 15, 'indexAfter': undefined},
		{'time': 3, 'indexAfter': 1},
		{'time': 0, 'indexAfter': 0},
		{'time': 20, 'indexAfter': undefined},
		{'time': 11, 'indexAfter': 5}
	];
	function checkPointOrder(points) {
		for (var j = 1; j < points.length; j++) {
			if (points[j].time <= points[j - 1].time) {
				addFailure('Points out of order at indexes ' + (j - 1) + ' and ' + j);
			}
		}
	}
	var key = 'test-csv-key';
	for (var i = 0; i < testTimes.length; i++) {
		var dp = new DataPoint({
			'time': testTimes[i].time,
			'value': 0
		});
		var points = project.getDataPointsFor(key);
		var actualIndexAfter = Project.findIndexJustAfter(dp.time, points);
		if (actualIndexAfter !== testTimes[i].indexAfter)
			addFailure('Expected index after of ' + testTimes[i].indexAfter + ' but got ' + actualIndexAfter + ' for time ' + dp.time + ', points = ' + JSON.stringify(points));
		project.addPoint(key, dp);
		points = project.getDataPointsFor(key);
		if (points.length != i + 1)
			addFailure('Points length expected to be ' + (i + 1) + ' but is ' + points.length);
		checkPointOrder(points);
	}
	project.clear(key);
	for (var i = 0; i < 100; i++) {
		var dp = new DataPoint({
			'time': Math.random() * 100,
			'value': 0
		});
		points = project.getDataPointsFor(key);
		var expectedAfterIndex = undefined;
		for (var j = 0; j < points.length; j++) {
			if (points[j].time > dp.time) {
				expectedAfterIndex = j;
				break;
			}
		}
		const actualIndexAfter = Project.findIndexJustAfter(dp.time, points);
		if (actualIndexAfter !== expectedAfterIndex) {
			addFailure('Expected after index to be ' + expectedAfterIndex + ' but got '+ actualIndexAfter + ', points are ' + JSON.stringify(points));
		}
		project.addPoint(key, dp);
		points = project.getDataPointsFor(key);
		checkPointOrder(points);
	}
});