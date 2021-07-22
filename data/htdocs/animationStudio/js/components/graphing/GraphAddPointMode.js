class GraphAddPointMode {
	constructor(project) {
		if (!(project instanceof Project))
			throw new Error('Project required.');
		this.project = project;
		this.keyValue = 'add-point';
	}

	processClick(key, seconds, units) {
		this.project.addPoint(key, new DataPoint({
			'time': seconds,
			'value': units
		}));
	}
}