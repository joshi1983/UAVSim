class CsvInputs extends React.Component {
  render() {
	var setAnimationStateKey = this.props.setAnimationStateKey;
	var inputDivs = React.createElement('div', {'key': 'csv-inputs-list'}, this.props.supportedKeys.map(function(supportedKey, index) {
		supportedKey.setAnimationStateKey = setAnimationStateKey;
		supportedKey.key = 'csv-input-parent-' + index;
		return React.createElement(CsvInput, supportedKey, null);
	}));
	var h2 = React.createElement('h2', {'key': 'csv-inputs-h2'}, 'CSV Inputs');
    return  React.createElement('div', {'key': 'csv-inputs', 'className': 'csv-inputs'}, [h2, inputDivs]);
  }
}
