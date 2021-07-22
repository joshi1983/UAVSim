class StraightBlendFunction {
	blend(info, time) {
		this._validateInfo(info);
		const len = info.to.time - info.from.time;
		const ratio = (time - info.from.time) / len;
		const ratio2 = 1 - ratio;
		return ratio * info.to.value + ratio2 * info.from.value;
	}

	getOptionName() {
		return 'Straight';
	}

	_validateInfo(info) {
		if (typeof info !== 'object')
			throw new Error('info Object required.');
		if (!(info.from instanceof DataPoint))
			throw new Error('from required.');
		if (!(info.to instanceof DataPoint))
			throw new Error('to required.');
	}

	getEndingSlope(info) {
		this._validateInfo(info);
		// same slope for the entire interval since this is a straight line segment.
		var rise = info.to.value - info.from.value;
		var run = info.to.time - info.from.time;
		return rise / run;
	}

	static matchesSerializableData(serializableData) {
		return serializableData === 'straight' || serializableData === undefined;
	}

	getSerializableData() {
		return 'straight';
	}
}