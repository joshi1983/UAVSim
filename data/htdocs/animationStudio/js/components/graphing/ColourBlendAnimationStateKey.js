class ColourBlendAnimationStateKey extends VirtualAnimationStateKey {
	constructor(fromColour, toColour, sourceKey) {
		if (!(fromColour instanceof Colour))
			throw new Error('fromColour must be a Colour');
		if (!(toColour instanceof Colour))
			throw new Error('toColour must be a Colour');
		if (typeof sourceKey !== 'string')
			throw new Error('sourceKey must be a string.');

		super();
		this.sourceKey = sourceKey;
		this.fromColour = fromColour;
		this.toColour = toColour;
	}

	getSourceKeyString() {
		return this.sourceKey;
	}

	getSourceKeyStrings() {
		return [this.sourceKey];
	}

	getVirtualKeyString() {
		return this.sourceKey + '-blend-ratio';
	}

	numberToSourceType(ratio) {
		return Colour.blend(this.fromColour, this.toColour, ratio).toHTMLColorCode();
	}
}