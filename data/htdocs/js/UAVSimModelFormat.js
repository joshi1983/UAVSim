function getTrianglesFromUAVSimModel(arrayBuffer) {
	if (!(arrayBuffer instanceof ArrayBuffer))
		throw new Error('Parameter must be an ArrayBuffer.');
	var dataView = new DataView(arrayBuffer);
	var triangles = [];
	var offset = 0;
	// loop through triangles.
	while (offset < dataView.byteLength) {
		var vertices = [];
		// loop through vertices.
		for (var vIndex = 0; vIndex < 3; vIndex++) {
			var coordinates = [];
			// loop through coordinates.
			for (var cIndex = 0; cIndex < 3; cIndex++) {
				coordinates.push(dataView.getFloat32(offset, true));
				offset += 4;
			}
			vertices.push(coordinates);
		}
		triangles.push(vertices);
	}
	return triangles;
}