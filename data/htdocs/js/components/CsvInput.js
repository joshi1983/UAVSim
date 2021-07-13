class CsvInput extends React.Component {
  constructor(props) {
	  super(props);
	  this.state = {'min': this.props.min, 'max': this.props.max};
  }

  setMin(newMin) {
	  this.setState(prevState => ({... prevState, 'min': newMin}));
  }

  setMax(newMax) {
	  this.setState(prevState => ({... prevState, 'max': newMax}));
  }

  render() {
		let label = React.createElement('label', {
			'key': 'label-' + this.props.name
		}, this.props.name);
		let setAnimationStateKey = this.props.setAnimationStateKey;
		let name = this.props.name;
		let input = React.createElement('input', {
			'min': this.state.min,
			'max': this.state.max,
			'type': 'range',
			'defaultValue': this.props.value,
			'step': 0.0001,
			'key': 'input-' + name,
			'onChange': function(event) {
				setAnimationStateKey(name, parseFloat(event.target.value));
			}
		}, null);
		const outer = this;
		let min = React.createElement(NumericValueSelector, {
			'key': 'min-' + name,
			'labelText': 'Min',
			'className': 'min',
			'max': this.state.max,
			'onChange': function(e) {
				outer.setMin(parseFloat(e.currentTarget.value));
			},
			'defaultValue': this.state.min
		}, 'Min ' + this.props.min);
		let max = React.createElement(NumericValueSelector, {
			'key': 'max-' + name,
			'labelText': 'Max',
			'className': 'max',
			'min': this.state.min,
			'onChange': function(e) {
				outer.setMax(parseFloat(e.currentTarget.value));
			},
			'defaultValue': this.state.max
		}, 'Max ' + this.props.max);
		return React.createElement('div', {
			'key': 'item-' + name
		}, [label, input, min, max]);
  }
}