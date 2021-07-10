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
			const headingChildren = ['Name', 'Type', 'Position', 'Image', 'Specs'].map(function(innerText) {
				return React.createElement('div', {
					'key': 'device-heading-' + innerText
				}, innerText);
			});
			const headings = React.createElement('div', {
				'key': 'device-headings',
				'className': 'device-headings'
			}, headingChildren);
			const devicesE = this.state.devices.map(function(device, index) {
				return React.createElement(DeviceRow, {
					'key': 'device-' + index,
					'index': index,
					'device': device
				}, null);
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