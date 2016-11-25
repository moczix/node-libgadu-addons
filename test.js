const Gadu = require('./build/Release/gadu');

this.libgadu = new Gadu.Session();

this.libgadu.login(8203225, 'akapulko', (status) => {
	if (status === true) {
		console.log('login true');
	}else {
		console.log('login false');
	}
});