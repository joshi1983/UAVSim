function getAbcFromPoints(points) {
	// implementation taken from: 
	// http://smackaay.com/2009/04/29/3-point-quadratic-regression-formula/
	var denominator = (points[0].x - points[1].x) *
		(points[0].x - points[2].x) *
		(points[1].x - points[2].x);

	var aTop = points[2].x * (-points[0].y + points[1].y) +
		points[1].x * (points[0].y - points[2].y) +
		points[0].x * (-points[1].y + points[2].y);

	var bTop = points[2].x * points[2].x * 
		(points[0].y - points[1].y) +
		points[0].x * points[0].x * (points[1].y - points[2].y) +
		points[1].x * points[1].x * (-points[0].y + points[2].y);
	
	var cTop = points[2].x *
		(points[1].x * (points[1].x - points[2].x) * points[0].y + 
			points[0].x * (-points[0].x + points[2].x) * points[1].y
		) + 
		points[0].x * (points[0].x - points[1].x) * points[1].x * points[2].y;
	
	var a = aTop / denominator;
	var b = bTop / denominator;
	var c = cTop / denominator;
	return [a, b, c];
}