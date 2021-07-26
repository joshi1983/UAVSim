class CsvInputs extends React.Component {
  constructor(props) {
	  super(props);
	  this.state = {};
	  this.animationState = {};
	  this.isUpdatePending = false;
	  this.isMessageInTransit = false;
  }

  async componentDidMount() {
	const response1 = await fetch('/api/csv-inputs');
	const response = await response1.json();
	const supportedKeys = response.supportedKeys;
	supportedKeys.sort((sk1, sk2) => { return sk1.name.localeCompare(sk2.name); });
	this.setState({'supportedKeys': supportedKeys});
  }

  _animationStateUpdated() {
	// if an update is in transit, 
	// let that eventual update cover the changes.
	// We want at most 1 HTTP request for updating the animation 
	// in transit at any given time.
	if (this.isMessageInTransit) {
		this.isUpdatePending = true;
		return;
	}
	this.isMessageInTransit = true;
	this.isUpdatePending = false;
	var outer = this;
	fetch('/api/csv-inputs', {
		'method': 'POST',
		'body': JSON.stringify(outer.animationState)
	}).then(function() {
		outer.isMessageInTransit = false;
		if (outer.isUpdatePending) {
			outer._animationStateUpdated();
		}
	});
  }

  render() {
	var h2 = React.createElement('h2', {'key': 'csv-inputs-h2'}, 'CSV Inputs');
	var rootElementProps = {'key': 'csv-inputs', 'className': 'csv-inputs'};
	if (this.state.supportedKeys === undefined) {
		let loadingMessage = React.createElement('p', {'key': 'p-csv-inputs-loading'}, 'Loading...');
		return React.createElement('div', rootElementProps, [h2, loadingMessage]);
	}
	else {
		var outer = this;
		function setAnimationStateKey(key, value) {
			outer.animationState[key] = value;
			outer._animationStateUpdated();
		}
		var inputDivs = React.createElement('div', {
				'key': 'csv-inputs-list'
			}, this.state.supportedKeys.map(function(supportedKey, index) {
			supportedKey = Object.assign({}, supportedKey);
			// shallow copy to avoid mutating state.
			supportedKey.setAnimationStateKey = setAnimationStateKey;
			supportedKey.key = 'csv-input-parent-' + index;
			if (supportedKey.dataType === AnimationStateKeyType.tDouble)
				return React.createElement(CsvDoubleInput, supportedKey, null);
			else if (supportedKey.dataType === AnimationStateKeyType.tColour)
				return React.createElement(CsvColourInput, supportedKey, null);
			else
				return React.createElement(CsvBoolInput, supportedKey, null);
		}));
		return React.createElement('div', rootElementProps, [h2, inputDivs]);
	}
  }
}
