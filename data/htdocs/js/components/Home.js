class Home extends React.Component {
	constructor(props) {
	  super(props);
	  this.state = {};
	}

	async componentDidMount() {
		const response = await fetch('/content/home.txt');
		const txt = await response.text();
		this.setState({'text': txt});
	}

	render() {
		var text = 'This web application is hosted in UAVSim enabling you to test your UAV control system while UAVSim represents the physical environment and some features of your UAV\'s sensors and actuator devices.';
		if (this.state !== undefined && this.state.text !== undefined)
			text = this.state.text;
		var lines = text.split('\n');
		var paragraphs = lines.map((line, index) => {
			return React.createElement('p', {'key': 'home-p-' + index}, line);
		});
		return React.createElement('div', {'key': 'home-content'}, 
			paragraphs);
	}
}