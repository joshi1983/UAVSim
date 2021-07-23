class CsvColourInput extends React.Component {
  render() {
		let label = React.createElement('label', {
			'key': 'label-' + this.props.name
		}, this.props.name);
		let setAnimationStateKey = this.props.setAnimationStateKey;
		let name = this.props.name;
		let input = React.createElement('input', {
			'type': 'color',
			'defaultValue': this.props.value,
			'key': 'input-' + name,
			'onChange': function(event) {
				setAnimationStateKey(name, event.target.value);
			}
		}, null);
		const outer = this;
		return React.createElement('div', {
			'key': 'item-' + name
		}, [label, input]);
  }
}