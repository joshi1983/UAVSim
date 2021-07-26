class BoolAnimationStateKey extends VirtualAnimationStateKey {
	constructor(sourceKey) {
		if (typeof sourceKey !== 'string')
			throw new Error('sourceKey must be a string.');

		super();
		this.sourceKey = sourceKey;
	}

	getSourceKeyString() {
		return this.sourceKey;
	}

	getSourceKeyStrings() {
		return [this.sourceKey];
	}

	getVirtualKeyString() {
		return this.sourceKey + '-one-or-zero';
	}

	numberToSourceType(ratio) {
		return Math.abs(ratio) > 0.5;
	}
}