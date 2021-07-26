// FIXME: This needs to be manually tested when the server supports CSV boolean inputs.
class CsvBoolInput extends React.Component {
  render() {
		let label = React.createElement('label', {
			'key': 'label-' + this.props.name
		}, this.props.name);
		let setAnimationStateKey = this.props.setAnimationStateKey;
		let name = this.props.name;
		let input = React.createElement('input', {
			'type': 'checkbox',
			'defaultChecked': this.props.value,
			'key': 'input-' + name,
			'onChange': function(event) {
				setAnimationStateKey(name, event.target.checked);
			}
		}, null);
		const outer = this;
		return React.createElement('div', {
			'key': 'item-' + name
		}, [label, input]);
  }
}