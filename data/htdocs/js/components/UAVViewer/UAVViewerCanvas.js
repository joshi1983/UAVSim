class UAVViewerCanvas extends React.Component {
	constructor(props) {
		super(props);
		this.scale2D = 100;
		const maxZ = UAVViewerStatistics.getMax(this.props.triangles, 2);
		const minZ = UAVViewerStatistics.getMin(this.props.triangles, 2);
		const zLength = maxZ - minZ;
		this.offsetZ = minZ - zLength * 0.5;
		var filteredTriangles = props.triangles;
		// More than 1,000 triangles is problematically slow to draw 
		// so we'll draw only a fraction of the ones from the actual mesh.
		if (filteredTriangles.length > 1000) {
			var skipFactor = Math.floor(filteredTriangles.length / 500);
			filteredTriangles = filteredTriangles.filter(function(triangle, index) {
				return index % skipFactor === 0;
			});
		}
		console.log('Filtered down to ' + filteredTriangles.length + ' triangles.');
		this.state = {'triangles': filteredTriangles, 'canvasWidth': 100, 'canvasHeight': 100};
	}

	componentDidMount() {
        this._drawTriangles();
    }

	_transformVector3DTo2D(v) {
		var z = v[2] - this.offsetZ;
		if (z <= 0.01)
			return; // indicate not to draw.

		var x = v[0] / z;
		var y = v[1] / z;
		x *= this.scale2D;
		y *= this.scale2D;
		x += this.centre[0];
		y += this.centre[1];
		return [x, y];
	}

	_drawLineSegment(g, v1, v2) {
		v1 = this._transformVector3DTo2D(v1);
		v2 = this._transformVector3DTo2D(v2);
		if (v1 !== undefined && v2 !== undefined) {
			if (Math.random() < 0.01)
				console.log('drawing line from ' + JSON.stringify(v1) + ' to ' + JSON.stringify(v2));
			g.beginPath();
			g.moveTo(Math.round(v1[0]), Math.round(v1[1]));
			g.lineTo(Math.round(v2[0]), Math.round(v2[1]));
			g.lineTo(0, 0);
			g.stroke();
			g.closePath();
			g.beginPath();
			g.fillRect(Math.round(v1[0]), Math.round(v1[1]), 5, 5);
			g.fillRect(Math.round(v2[0]), Math.round(v2[1]), 5, 5);
			g.fill();
			g.closePath();
		}
	}

	_drawTriangles() {
		const canvas = this.refs.canvas;
		const g = canvas.getContext('2d');
		const bounds = canvas.getBoundingClientRect();
		var width = Math.round(bounds.width);
		var height = Math.round(bounds.height);
		if (width !== this.state.canvasWidth || height !== this.state.canvasHeight) {
			var newState = Object.assign({}, this.state);
			newState.canvasWidth = width;
			newState.canvasHeight = height;
			console.log('newState = ' + JSON.stringify(newState));
			this.setState(newState);
			canvas.setAttribute('width', width);
			canvas.setAttribute('height', height);
			console.log('Trying to set width to ' + width + ', and height to ' + height);
		}
		this.centre = [width * 0.5, height * 0.5];
		console.log('width = ' + width + ', height = ' + height + ', centre = ' + JSON.stringify(this.centre));
		g.clearRect(0, 0, width, height);
		g.fillStyle = '#f00';
		g.fillRect(0, 0, 100, 100);
		g.strokeStyle = '#000';
		g.fillStyle = '#f00';
		g.rect(10, 10, 20, 20);
		g.fill();
		g.lineWidth = 3;
		console.log('About to draw the ' + this.state.triangles.length + ' triangles.');
		var outer = this;
		this.state.triangles.forEach((triangle) => {
			for (var i = 0; i < 3; i++) {
				outer._drawLineSegment(g, triangle[i], triangle[(i + 1) % 3]);
			}
		});
	}

	render() {		
		console.log('render() called. canvasWidth = ' + this.state.canvasWidth + ', canvasHeight = ' + this.state.canvasHeight);
		return React.createElement('canvas', {
			'key': 'canvas',
			'ref': 'canvas',
			'width': this.state.canvasWidth,
			'height': this.state.canvasHeight,
			'className': 'uav-viewer-canvas'}, null);
	}
}