class EventDispatcher {
	constructor() {
		this.listeners = [];
	}

	addEventListener(listener) {
		this.listeners.push(listener);
	}

	_dispatchEvent(e) {
		this.listeners.forEach(function(listener) {
			listener(e);
		});
	}
}