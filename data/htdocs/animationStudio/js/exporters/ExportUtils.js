class ExportUtils {
	static download(filename, stringData) {
		const a = document.createElement('a');
		a.setAttribute('download', filename);
		// convert stringData to data URL.
		const dataUrl = 'data:text/plain;charset=utf-8,' + encodeURIComponent(stringData);
		a.setAttribute('href', dataUrl);
		a.click();
	}
}