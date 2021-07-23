class CSVExporter {
	constructor(project, virtualAnimationStateKeys) {
		if (!(project instanceof Project))
			throw new Error('Project required.');
		if (!(virtualAnimationStateKeys instanceof VirtualAnimationStateKeys))
			throw new Error('VirtualAnimationStateKeys required');

		this.project = project;
		this.virtualAnimationStateKeys = virtualAnimationStateKeys;
		const downloadButton = document.getElementById('download-csv');
		const outer = this;
		downloadButton.addEventListener('click', function() {
			outer.download();
		});
	}

	async download() {
		const outer = this;
		const keys = this.virtualAnimationStateKeys.getAllSourceKeys(this.project);
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
					const virtualKeyString = outer.virtualAnimationStateKeys.getVirtualKeyFor(keys[columnIndex]);
					const v = this.project.getValue(virtualKeyString, t);
					valuesForLine.push(outer.virtualAnimationStateKeys.convertNumberToSourceType(keys[columnIndex], v));
				}
				lines.push(valuesForLine.join(","));
			}
		}
		
		const csvData = lines.join("\n");
		ExportUtils.download('animation.csv', csvData);
	}
}