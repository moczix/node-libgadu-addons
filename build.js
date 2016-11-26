var Gyp = require('node-gyp')

var gyp = Gyp()
gyp.parseArgv([])

// run "clean", "configure", then "build"


gyp.commands.clean([], function (err) {
  console.error('clean', arguments);

  gyp.commands.configure([], function (err) {
    if (err) throw err;
    console.error('configure', arguments);
	
    gyp.commands.build([], function (err) {
      if (err) throw err;

      console.error('build', arguments);
    });

  });
});

