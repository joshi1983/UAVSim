class CsvInputsRepository {
	constructor() {
	}

	refreshCsvInputs() {
		const outer = this;
		return fetch('/api/csv-inputs').then(function(response1) {
			return response1.json().then(function(response) {
				outer.supportedKeys = response.supportedKeys;
			});
		});
	}

	getCsvInputKeys() {
		return this.supportedKeys.map((csvInput) => csvInput.name);
	}
}