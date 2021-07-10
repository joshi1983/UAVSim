class UAVStatisticsRow extends React.Component {
	render() {
		const label = React.createElement('label', {'key': 'label'}, this.props.labelText);
		const value = React.createElement('span', {'key': 'span'}, this.props.valueText);
		return React.createElement('div', {
			'key': ''
		}, [label, value]);
	}
}