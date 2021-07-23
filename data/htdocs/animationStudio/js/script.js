document.addEventListener('DOMContentLoaded', function() {
	const project = new Project();
	const csvInputsRepo = new CsvInputsRepository();
	const durationSelector = new DurationSelector(project);
	const animationSettings = AnimationSettingsRepository.getInstance();
	csvInputsRepo.refreshCsvInputs().then(function(csvInputs) {
		const virtualAnimationStateKeys = new VirtualAnimationStateKeys(csvInputs);
		const player = new Player(project, virtualAnimationStateKeys);
		new CSVExporter(project, virtualAnimationStateKeys);
		const graph = new Graph(project, csvInputsRepo, player, virtualAnimationStateKeys);
	});
	new ProjectExporter(project);
});