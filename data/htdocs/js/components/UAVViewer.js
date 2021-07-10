class UAVViewer extends React.Component {
	constructor(props) {
	  super(props);
	  this.state = {};
	}

	async componentDidMount() {
		const response1 = await fetch('/api/uav-model');
		const arrayBuffer = await response1.arrayBuffer();
		var triangles = getTrianglesFromUAVSimModel(arrayBuffer);
		this.setState({'triangles': triangles});
	}

	render() {
		const h3 = React.createElement('h3', {'key': 'uav-viewer-title'}, 'UAV Viewer');
		if (this.state.triangles === undefined) {
			const p = React.createElement('p', {'key': 'uav-viewer-loading'}, 'Loading...');
			return React.createElement('div', {'key': 'uav-viewer-div'}, [h3, p]);
		}
		else {
			const canvas = React.createElement(UAVViewerCanvas, {
				'key': 'uav-viewer-canvas',
				'triangles': this.state.triangles
			}, null);
			var statisticsElement = React.createElement(UAVViewerStatistics, {
				'key': 'uav-viewer-statistics',
				'triangles': this.state.triangles
			}, null);
			return React.createElement('div', {'key': 'uav-viewer-div'}, [h3, canvas, statisticsElement]);
		}
	}
}