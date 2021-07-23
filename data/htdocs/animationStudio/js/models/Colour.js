class Colour {
	constructor(c) {
		if (typeof c === 'number')
			throw new Error('Can not initialize a colour from a number.  Object or string required.');
		this.r = 0;
		this.g = 0;
		this.b = 0;
		if (c instanceof Colour || typeof c === 'object')
			this._loadFromColour(c);
		else if (typeof c === 'string')
			this._loadFromString(c);
	}

	_loadFromColour(c) {
		this.r = Colour._sanitizeNumber(c.r);
		this.g = Colour._sanitizeNumber(c.g);
		this.b = Colour._sanitizeNumber(c.b);
	}

	static _sanitizeNumber(val) {
		if (typeof val === 'number' && !isNaN(val))
			return Math.max(0, Math.min(1, val));
		else
			return 0;
	}

	static _sanitizeColourString(c) {
		// remove all whitespaces and convert to lower case.
		c = c.replaceAll(/\s/g,'').toLowerCase();
		if (c.charAt(0) === '#') {
			if (c.length > 4) {
				while (c.length < 7)
					c = '#0' + c.substring(1);
			}
			while (c.length < 4) {
				c = '#0' + c.substring(1);
			}
			if (c.length === 4) // convert 4-character format to length 7.
				c = '#' + c[1] + c[1] + c[2] + c[2] + c[3] + c[3];
		}
		return c;
	}

	static blend(c1, c2, ratio) {
		if (typeof ratio !== 'number' || isNaN(ratio))
			throw new Error('ratio must be a number');
		if (!(c1 instanceof Colour))
			throw new Error('c1 must be a Colour');
		if (!(c2 instanceof Colour))
			throw new Error('c2 must be a Colour');

		// clamp to a meaningful range.
		ratio = Math.max(0, Math.min(1, ratio));
		
		const ratio2 = 1 - ratio;
		return new Colour({
			'r': c1.r * ratio2 + c2.r * ratio,
			'g': c1.g * ratio2 + c2.g * ratio,
			'b': c1.b * ratio2 + c2.b * ratio
		});
	}

	static getRatioFromTwoHexDigits(digits) {
		const byteVal = parseInt(digits, 16);
		return byteVal / 255;
	}

	static getTwoHexDigitsFromRatio(ratio) {
		const byteVal = ratio * 255;
		var result = Number(byteVal).toString(16);
		const index = result.indexOf(".");
		if (index !== -1)
			result = result.substring(0, index);
		if (result.length < 2)
			result = '0' + result;
		return result;
	}

	_loadFromString(c) {
		c = Colour._sanitizeColourString(c);
		if (c.length === 7) {
			this.r = Colour.getRatioFromTwoHexDigits(c.substring(1, 3));
			this.g = Colour.getRatioFromTwoHexDigits(c.substring(3, 5))
			this.b = Colour.getRatioFromTwoHexDigits(c.substring(5))
		}
	}

	/*
	I'm spelling as Color since the world does that generally for the phrase for 
	 "HTML color code".  
	*/
	toHTMLColorCode() {
		return '#' + Colour.getTwoHexDigitsFromRatio(this.r) +
			Colour.getTwoHexDigitsFromRatio(this.g) +
			Colour.getTwoHexDigitsFromRatio(this.b);
	}
}