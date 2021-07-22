class ParabolicBlendFunction {
	_validateInfo(info) {
		if (typeof info !== 'object')
			throw new Error('info Object required.');
		if (!(info.from instanceof DataPoint))
			throw new Error('from required.');
		if (!(info.to instanceof DataPoint))
			throw new Error('to required.');
		if (isNaN(info.from.previousSlope))
			throw new Error('from point must have a numeric previousSlope.');
	}

	getOptionName() {
		return 'Parabolic';
	}

	_getABCFromInfo(info) {
		// find a parabolic curve matching info.from.previousSlope, and
		// intersects info.from and info.to.

		var len = info.to.time - info.from.time;
		var deltaT = len * 0.01;
		// FIXME: get the math working perfectly from slope of info.from, from, and to.
		// For now, we're estimating the curve using a point that is very close to info.from.
		var points = [
			{'x': info.from.time - deltaT, 'y': info.from.value - (info.from.previousSlope * deltaT)},
			{'x': info.from.time, 'y': info.from.value},
			{'x': info.to.time, 'y': info.to.value}
		];
		return getAbcFromPoints(points);
	}

	blend(info, time) {
		this._validateInfo(info);
		const [a, b, c] = this._getABCFromInfo(info);
		return a * time * time + b * time + c;
	}

	getEndingSlope(info) {
		this._validateInfo(info);
		const [a, b, c] = this._getABCFromInfo(info);
		return 2 * a * info.to.time + b;
	}

	static matchesSerializableData(serializableData) {
		return serializableData === 'parabolic';
	}

	getSerializableData() {
		return 'parabolic';
	}
}