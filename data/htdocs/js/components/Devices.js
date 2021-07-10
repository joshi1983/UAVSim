class Devices extends React.Component {
	constructor(props) {
	  super(props);
	  this.state = {};
	}

	async componentDidMount() {
		const response1 = await fetch('/api/devices');
		const response = await response1.json();
		this.setState({'devices': response});
	}
  
	render() {
		const h2 = React.createElement('h2', {'key': 'devices-h2'}, 'Devices');
		if (this.state.devices === undefined) {
			const loadingMessage = React.createElement('p', {'key': 'devices-loading-p'}, 'Loading...');
			return React.createElement('div', {
				'key': 'devices-loading',
				'className': 'devices'
			}, [h2, loadingMessage]);
		}
		else {
			const headingChildren = ['Name', 'Type', 'Position'].map(function(innerText) {
				return React.createElement('div', {
					'key': 'device-heading-' + innerText
				}, innerText);
			});
			const headings = React.createElement('div', {
				'key': 'device-headings',
				'className': 'device-headings'
			}, headingChildren);
			const devicesE = this.state.devices.map(function(device, index) {
				const name = React.createElement('div', {'key': 'device-name-' + index}, device.name);
				const type = React.createElement('div', {'key': 'device-type-' + index}, device.type);
				const positionText = ['x', 'y', 'z'].map(function(key) {
					return device.position[key];
				}).join(',');
				const position = React.createElement('div', {'key': 'device-position-' + index}, positionText);
				return React.createElement('div', {'key': 'device-' + index}, [name, type, position]);
			});
			devicesE.unshift(headings);
			const container = React.createElement('div', {'key': 'devices-container', 'className': 'devices-container'}, devicesE);
			return React.createElement('div', {
				'key': 'devices-root',
				'className': 'devices'
			}, [h2, container]);
		}
	}
}