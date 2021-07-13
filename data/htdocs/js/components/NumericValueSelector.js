class NumericValueSelector extends React.Component {
	constructor(props) {
		super(props);
		this.state = {'isReadOnly': true};
	}

	render() {
		var valueControl;
		const outer = this;
		if (this.state.isReadOnly === true)
			valueControl = React.createElement('span', 
				{
					'key': 'span',
					'onClick': function() {
						outer.setState({'isReadOnly': false});
					}
				}, '' + this.props.defaultValue);
		else
			valueControl = React.createElement('input', {
				'key': 'input',
				'type': 'number',
				'step': 0.0001,
				'min': this.props.min,
				'max': this.props.max,
				'onChange': this.props.onChange,
				'onBlur': function(e) {
					outer.setState({'isReadOnly': true});
				},
				'onExit': function(e) {
					outer.setState({'isReadOnly': true});
				},
				'value': this.props.defaultValue
			}, null);
		const label = React.createElement('label', {'key': 'label', 'onClick': function() {
			outer.setState({'isReadOnly': !outer.state.isReadOnly});
		}}, this.props.labelText);
		return React.createElement('div', {'key': 'div', 'className': 'numeric-value-selector'}, [label, valueControl]);
	}
}