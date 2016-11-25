var binary = require('node-pre-gyp');
var path = require('path')
var binding_path = binary.find(path.resolve(path.join(__dirname,'./package.json')));
var Gadu = require(binding_path);


libgadu = new Gadu.Session();
this.libgadu.login(8203225, 'acipoka', (status) => {
	if (status === true) {
		console.log('login true');
	}else {
		console.log('login false');
	}
});