class DeviceRow extends React.Component {
	render() {
		const device = this.props.device;
		const name = React.createElement('div', {'key': 'device-name-' + this.props.index}, device.name);
		const type = React.createElement('div', {'key': 'device-type-' + this.props.index}, device.type);
		const positionText = ['x', 'y', 'z'].map(function(key) {
			return device.position[key];
		}).join(',');
		const position = React.createElement('div', {'key': 'device-position-' + this.props.index}, positionText);
		const imageStyles = {};
		if (device['image-url'])
			imageStyles.backgroundImage = 'url(\"' + device['image-url'] + '\")';
		const image = React.createElement('div', {
			'key': 'device-image-' + this.props.index,
			'className': 'device-image',
			'style': imageStyles
		}, null);
		const specProps = {'key': 'device-' + this.props.index + '-specs'};
		var specChild;
		if (device['spec-url']) {
			specProps.href=device['spec-url'];
			specProps.target="_empty";
			specChild = React.createElement('a', specProps, 'specs');
		}
		else {
			specChild = React.createElement('span', specProps, 'N/A');
		}
		const specDiv = React.createElement('div', specProps, [specChild]);
		return React.createElement('div', {'key': 'device-' + this.props.index}, [name, type, position, image, specDiv]);
	}
}