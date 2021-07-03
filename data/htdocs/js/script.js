document.addEventListener('DOMContentLoaded', function() {
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
	fetch('/api/csv-inputs').then(function(response) {
		return response.json();
	}).then(function(response) {
		var supportedKeys = response.supportedKeys;
		var root = document.getElementById('root');
		var ul = document.createElement('ul');
		supportedKeys.forEach(function(key) {
			var e = document.createElement('input');
			key.max = Math.max(key.max, key.value);
			key.min = Math.min(key.min, key.value);
			e.setAttribute('max', key.max);
			e.setAttribute('min', key.min);
			e.setAttribute('step', 0.001);
			e.setAttribute('type', 'range');
			e.value = key.value;
			e.addEventListener('input', function() {
				animationState[key.name] = parseFloat(e.value);
				animationStateUpdated();
			});
			var label = document.createElement('label');
			label.innerText = key.name;
			var li = document.createElement('li');
			li.appendChild(label);
			li.appendChild(e);
			ul.appendChild(li);
		});
		root.appendChild(ul);
	});
});