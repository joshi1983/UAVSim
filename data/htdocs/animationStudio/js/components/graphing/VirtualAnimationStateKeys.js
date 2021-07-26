class VirtualAnimationStateKeys {
	constructor(csvInputsData) {
		if (typeof csvInputsData !== 'object' || !(csvInputsData.supportedKeys instanceof Array))
			throw new Error('Invalid csvInputsData');

		this.virtualKeys = {}; // key off the virtual key.
		this.sourceToVirtualKeys = {}; // key off the source key.
		const supportedKeys = csvInputsData.supportedKeys;
		const outer = this;
		for (var i = 0; i < supportedKeys.length; i++) {
			const newKeys = VirtualAnimationStateKeys.getVirtualKeysFrom(supportedKeys[i]);
			newKeys.forEach(function(virtualKeyInstance) {
				outer.virtualKeys[virtualKeyInstance.getVirtualKeyString()] = virtualKeyInstance;
				outer.sourceToVirtualKeys[virtualKeyInstance.getSourceKeyString()] = virtualKeyInstance;
			});
		}
	}

	getVirtualKeyFor(sourceKeyString) {
		if (this.sourceToVirtualKeys[sourceKeyString] === undefined)
			return sourceKeyString;
		else
			return this.sourceToVirtualKeys[sourceKeyString].getVirtualKeyString();
	}

	getSourceKeyFor(keyString) {
		if (this.virtualKeys[keyString] === undefined)
			return keyString;
		else
			return this.virtualKeys[keyString].getSourceKeyString();
	}

	getAllSourceKeys(project) {
		if (!(project instanceof Project))
			throw new Error('Project required.');
		const outer = this;
		return project.getCsvKeys().map(function(keyString) {
			return outer.getSourceKeyFor(keyString);
		});
	}

	convertNumberToSourceType(sourceKeyString, num) {
		if (this.sourceToVirtualKeys[sourceKeyString] === undefined)
			return num;
		else
			return this.sourceToVirtualKeys[sourceKeyString].numberToSourceType(num);
	}

	getVirtualKeyStrings() {
		return Object.keys(this.virtualKeys);
	}

	static getVirtualKeysFrom(keyInfo) {
		const result = [];
		if (keyInfo.dataType === AnimationStateKeyType.tColour) {
			result.push(new ColourBlendAnimationStateKey(new Colour('#ffffff'), new Colour('#ff0000'), keyInfo.name));
		}
		else if (keyInfo.dataType === AnimationStateKeyType.tBool) {
			result.push(new BoolAnimationStateKey(keyInfo.name));
		}
		return result;
	}
}