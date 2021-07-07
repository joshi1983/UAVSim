document.addEventListener('DOMContentLoaded', function() {
	ReactDOM.render(
	  React.createElement(CsvInputs, {'key': 'csv-inputs-root'}, null),
	  document.getElementById('root')
	);
});