document.addEventListener('DOMContentLoaded', function() {
	fetch('/api/csv-inputs').then(function(response) {
		return response.json();
	}).then(function(response) {
		var animationState = {};
		var isUpdatePending = false;
		var isMessageInTransit = false;
		function animationStateUpdated() {
			// if an update is in transit, 
			// let that eventual update cover the changes.
			// We want at most 1 HTTP request for updating the animation 
			// in transit at any given time.
			if (isMessageInTransit) {
				isUpdatePending = true;
				return;
			}
			isMessageInTransit = true;
			isUpdatePending = false;
			fetch('/api/csv-inputs', {
				'method': 'POST',
				'body': JSON.stringify(animationState)
			}).then(function() {
				isMessageInTransit = false;
				if (isUpdatePending) {
					animationStateUpdated();
				}
			});
		}
		function setAnimationStateKey(key, value) {
			animationState[key] = value;
			animationStateUpdated();
		}
		response.setAnimationStateKey = setAnimationStateKey;
		response.key = 'csv-inputs-root';
		ReactDOM.render(
		  React.createElement(CsvInputs, response, null),
		  document.getElementById('root')
		);
	});
});