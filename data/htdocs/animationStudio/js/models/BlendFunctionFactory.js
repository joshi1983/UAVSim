class BlendFunctionFactory {
	static createFrom(serializableData) {
		if (StraightBlendFunction.matchesSerializableData(serializableData))
			return new StraightBlendFunction(serializableData);
		else if (ParabolicBlendFunction.matchesSerializableData(serializableData))
			return new ParabolicBlendFunction(serializableData);
		else {
			console.error('Unable to match serializableData to a blend function: ', serializableData);
			throw new Error('Unrecognized blend function.');
		}
	}

	static getSelectableBlendFunctions() {
		return [
			new StraightBlendFunction(),
			new ParabolicBlendFunction()
		];
	}
}