class DurationSelector {
	constructor(project) {
		this.project = project;
		this.input = document.getElementById('duration-seconds');
		const outer = this;
		function durationUpdated() {
			const val = parseFloat(outer.input.value);
			if (typeof val === 'number' && !isNaN(val)) {
				project.setDurationSeconds(val);
			}
		}
		this.input.value = project.getDurationSeconds();
		this.input.addEventListener('input', function() {
			durationUpdated();
		});
		project.addEventListener(function(event) {
			if (event.key === 'loaded') {
				console.log('trying to load new value from project: ' + project.getDurationSeconds());
				outer.input.value = project.getDurationSeconds();
			}
		});
	}
}