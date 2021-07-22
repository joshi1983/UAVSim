class GraphCanvasGrid {

	static getTimeIntervalFromSecondsWidth(secondsWidth) {
		if (secondsWidth < 5)
			return 0.5;
		else if (secondsWidth < 10)
			return 1;
		else if (secondsWidth < 50)
			return 5;
		else if (secondsWidth < 100)
			return 10;
		else if (secondsWidth < 250)
			return 25;
		else if (secondsWidth < 1000)
			return 60;
		else
			return 120;
	}

	static getUnitsIntervalFromUnitsHeight(unitsHeight) {
		if (unitsHeight < 1)
			return 0.1;
		else if (unitsHeight < 5)
			return 0.5;
		else if (unitsHeight < 10)
			return 1;
		else if (unitsHeight < 50)
			return 5;
		else if (unitsHeight < 100)
			return 10;
		else if (unitsHeight < 1000)
			return 100;
		else if (unitsHeight < 10000)
			return 1000;
		else
			return 10000;
	}
}