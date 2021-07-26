class CompositeAnimationStateKey extends VirtualAnimationStateKey {
	constructor(virtualKeyString, childKeys) {
		if (typeof virtualKeyString !== 'string')
			throw new Error('virtualKeyString must be a string.');
		if (!(childKeys instanceof Array))
			throw new Error('childKeys must be an Array');
		for (var i = 0; i < childKeys.length; i++)
			if (typeof childKeys[i] !== 'string')
				throw new Error('childKeys must be an array of nothing but strings.  Non-string found at index: ' + i);

		super();
		this.childKeys = childKeys;
		this.virtualKeyString = virtualKeyString;
	}

	getSourceKeyStrings() {
		return this.childKeys;
	}

	getVirtualKeyString() {
		return this.virtualKeyString;
	}

	numberToSourceType(num) {
		return num;
	}
}