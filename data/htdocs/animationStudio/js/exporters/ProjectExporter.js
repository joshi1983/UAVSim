class ProjectExporter {
	constructor(project) {
		if (!(project instanceof Project))
			throw new Error('Project required.');
		this.project = project;
		var button = document.getElementById('download-project');
		const outer = this;
		button.addEventListener('click', function() {
			outer.download();
		});
	}

	download() {
		ExportUtils.download('animation.json', JSON.stringify(this.project.getProjectData()));
	}
}