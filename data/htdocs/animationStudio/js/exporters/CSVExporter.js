class CSVExporter {
	constructor(project) {
		if (!(project instanceof Project))
			throw new Error('Project required.');

		this.project = project;
		const downloadButton = document.getElementById('download-csv');
		const outer = this;
		downloadButton.addEventListener('click', function() {
			outer.download();
		});
	}

	async download() {
		const keys = this.project.getCsvKeys();
		const lines = [keys];
		const _animationSettings = AnimationSettingsRepository.getInstance();
		const animationSettings = await _animationSettings.getSettingsAsync();
		const fps = animationSettings.fps;
		const numFrames = Math.ceil(this.project.getDurationSeconds() * fps);
		const numBlurFramesPerFrame = animationSettings.blurBetweenRows ? 1 : Math.max(1, animationSettings.blurFrameCount);
		for (var frameIndex = 0; frameIndex < numFrames; frameIndex++) {
			for (var blurFrameIndex = 0; blurFrameIndex < numBlurFramesPerFrame; blurFrameIndex++) {
				const blurRatio = blurFrameIndex * 0.5 / numBlurFramesPerFrame;
				const t = (frameIndex + blurRatio) / fps;
				const valuesForLine = [];
				for (var columnIndex = 0; columnIndex < keys.length; columnIndex++) {
					const v = this.project.getValue(keys[columnIndex], t);
					valuesForLine.push(v);
				}
				lines.push(valuesForLine.join(","));
			}
		}
		
		const csvData = lines.join("\n");
		ExportUtils.download('animation.csv', csvData);
	}
}