class AnimationSettingsRepository {
	constructor() {
		this.getSettingsAsync();
	}

	static getInstance() {
		if (AnimationSettingsRepository.singleton === undefined)
			AnimationSettingsRepository.singleton = new AnimationSettingsRepository();

		return AnimationSettingsRepository.singleton;
	}

	getSettingsAsync() {
		if (this.promise === undefined)
			this.promise = new Promise(function(resolver, rejecter) {
				fetch('/api/animation-settings').then(function(response1) {
					response1.json().then(function(responseData) {
						resolver(responseData);
					});
				});
			});
		return this.promise;
	}
}