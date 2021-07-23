class CsvInputsRepository {
	constructor() {
	}

	refreshCsvInputs() {
		const outer = this;
		return fetch('/api/csv-inputs').then(function(response1) {
			return response1.json().then(function(response) {
				outer.supportedKeys = response.supportedKeys;
				return response;
			});
		});
	}

	getNumericCsvInputKeys() {
		return this.supportedKeys.
			filter((csvInput) => csvInput.dataType === AnimationStateKeyType.tDouble).
			map((csvInput) => csvInput.name);
	}
}