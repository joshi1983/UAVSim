class UAVViewerStatistics extends React.Component {

	static getMax(triangles, coordinateIndex) {
		var result = Number.NEGATIVE_INFINITY;
		triangles.forEach(function(triangle) {
			result = Math.max(result, 
				Math.max(...triangle.map(v => { return v[coordinateIndex]}))
			);
		});
		return result;
	}

	static getMin(triangles, coordinateIndex) {
		var result = Number.POSITIVE_INFINITY;
		triangles.forEach(function(triangle) {
			result = Math.min(result, 
				Math.min(...triangle.map(v => { return v[coordinateIndex]}))
			);
		});
		return result;
	}

	render() {
		const statisticsChildren = [];
		const fixedPrecision = 3;
		const outer = this;
		const range = {};
		['x', 'y', 'z'].forEach(function(coordinateKey, coordinateIndex) {
			var value = UAVViewerStatistics.getMin(outer.props.triangles, coordinateIndex);
			statisticsChildren.push(React.createElement(UAVStatisticsRow, {
				'key': 'min-' + coordinateKey, 
				'labelText': 'Min-' + coordinateKey.toUpperCase(),
				'valueText': value.toFixed(fixedPrecision)
			}, null));
			range['min' + coordinateKey] = value;
			value = UAVViewerStatistics.getMax(outer.props.triangles, coordinateIndex);
			statisticsChildren.push(React.createElement(UAVStatisticsRow, {
				'key': 'max-' + coordinateKey, 
				'labelText': 'Max-' + coordinateKey.toUpperCase(),
				'valueText': value.toFixed(fixedPrecision)
			}, null));
			range['max' + coordinateKey] = value;
		});
		statisticsChildren.push(React.createElement(UAVStatisticsRow, {
				'key': 'height', 
				'labelText': 'Height',
				'valueText': (range.maxy - range.miny).toFixed(fixedPrecision) + "m"
			}, null));
		statisticsChildren.push(React.createElement(UAVStatisticsRow, {
				'key': 'triangle-count', 
				'labelText': 'Triangle Count',
				'valueText': this.props.triangles.length
			}, null));
		return React.createElement('div', {'key': 'uav-viewer-statistics-container', 'className': 'uav-viewer-statistics'}, statisticsChildren);
	}
}