document.addEventListener('DOMContentLoaded', function() {
	const csvInputsElement = React.createElement(CsvInputs, {'key': 'csv-inputs-root'}, null);
	const devicesElement = React.createElement(Devices, {'key': 'devices-root'}, null);
	const homeElement = React.createElement(Home, {'key': 'home'}, null);
	const csvInputsRoute = React.createElement(ReactRouterDOM.Route, {
		'key': 'csv-inputs-route',
		'path': '/csv-inputs',
		'exact': true
	}, csvInputsElement);
	const homeRoute = React.createElement(ReactRouterDOM.Route, {
		'key': 'home-route',
		'path': '/',
		'exact': true
	}, homeElement);
	const devicesRoute = React.createElement(ReactRouterDOM.Route, {
		'key': 'devices-route',
		'path': '/devices',
		'exact': true
	}, devicesElement);
	let linkProperties = {
		'devices': {},
		'csv-inputs': {},
		'home': {'to': '/', 'exact': true, 'end': ''}
	};
	for (var key in linkProperties) {
		if (linkProperties[key].to === undefined)
			linkProperties[key].to = '/' + key;
		linkProperties.activeClassName = 'active';
	}
	const devicesLink = React.createElement(ReactRouterDOM.NavLink, linkProperties.devices, 'Devices');
	const csvLink = React.createElement(ReactRouterDOM.NavLink, linkProperties['csv-inputs'], 'Csv-Inputs');
	const homeLink = React.createElement(ReactRouterDOM.NavLink, linkProperties.home, 'Home');
	const devices = React.createElement('li', {'key': 'li-devices'}, devicesLink);
	const csvInputs = React.createElement('li', {'key': 'li-csv-inputs'}, csvLink);
	const homeLi = React.createElement('li', {'key': 'li-home'}, homeLink);
	const ul = React.createElement('ul', {'key': 'ul-r'}, [homeLi, csvInputs, devices]);
	const nav = React.createElement('nav', {'key': 'nav-r'}, [ul]);
	const switchE = React.createElement(ReactRouterDOM.Switch, {'key': 'switchE-r'}, [homeRoute, csvInputsRoute, devicesRoute]);
	const router = React.createElement(ReactRouterDOM.HashRouter, {'key': 'router'}, [nav, switchE]);
	ReactDOM.render(
	  router,
	  document.getElementById('root')
	);
});