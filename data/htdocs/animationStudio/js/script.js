document.addEventListener('DOMContentLoaded', function() {
	const project = new Project();
	const csvInputs = new CsvInputsRepository();
	const durationSelector = new DurationSelector(project);
	const animationSettings = AnimationSettingsRepository.getInstance();
	const player = new Player(project);
	const graph = new Graph(project, csvInputs, player);
	new CSVExporter(project);
	new ProjectExporter(project);
});