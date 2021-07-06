class CsvInput extends React.Component {
  render() {
		let label = React.createElement('label', {
			'key': 'label-' + this.props.name
		}, this.props.name);
		let setAnimationStateKey = this.props.setAnimationStateKey;
		let name = this.props.name;
		let input = React.createElement('input', {
			'min': this.props.min,
			'max': this.props.max,
			'type': 'range',
			'defaultValue': this.props.value,
			'step': 0.0001,
			'key': 'input-' + name,
			'onChange': function(event) {
				setAnimationStateKey(name, parseFloat(event.target.value));
			}
		}, null);
		let min = React.createElement('span', {
			'key': 'min-' + name,
			'className': 'min'
		}, 'Min ' + this.props.min);
		let max = React.createElement('span', {
			'key': 'max-' + name,
			'className': 'max'
		}, 'Max ' + this.props.max);
		return React.createElement('div', {
			'key': 'item-' + name
		}, [label, input, min, max]);
  }
}