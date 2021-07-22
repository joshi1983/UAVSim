async function urlToDataURL(url) {
	let blob = await fetch(url).then(r => r.blob());
	let dataUrl = await new Promise(resolve => {
		let reader = new FileReader();
		reader.onload = () => resolve(reader.result);
		reader.readAsDataURL(blob);
	});
	return dataUrl;
}