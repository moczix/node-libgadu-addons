const GaduGadu = require('./index');

let myGG = new GaduGadu();
myGG.debug(true);
myGG.event.on('connected', () => {
	console.log('connected');
});
myGG.event.on('notConnected', () => {
	console.log('wrong login and password');
});


myGG.login(8203225, 'akapulkoo');