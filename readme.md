# Node LibGadu Addon
 - - - -
### Description
Node GaduGadu library for javascript and typescript.

### Installation Linux
##### Requirements
* libgadu 1.12.1 (http://libgadu.net/)
##### Get repo
``git clone https://moczniak@bitbucket.org/moczniak/node-libgadu-addons-js-ts.git``
##### Compile libgadu
You can compile libgadu globally or localy, if you want to use it on hosting choose localy

##### Globally
go to libgadu directory in terminal and then:
```
sh ./configure
make
make install 
```
Then go to addon directory and open binding.gyp file in your text editor then this
``libraries": [ "/home/moczniak/my_native_libs/libgadu/lib/libgadu.so" ],``
change for 
``libraries": [ "-lgadu" ],``
if you install globally the lib will go to folder /usr/local/lib and you don't need absolute path about libgadu.

##### Locally
go to libgadu directory in terminal and then:
```
sh ./configure --prefix=/your/path/to/libgadu
make
make install
```
then go to addon directory and open binding.gyp file in your text editor then this
``libraries": [ "/home/moczniak/my_native_libs/libgadu/lib/libgadu.so" ],``
change for 
``libraries": [ "/your/path/to/libgadu/lib/libgadu.so" ],``

##### static lib
You can compile libgadu an use static version instead of shared (change .so for .a) but i notice that in my case it only worked on x32 OS.

#### Locally compilation
If you compile libgadu locally you probably should add these three things to your enviroment path:
1. ``export CPLUS_INCLUDE_PATH=/your/path/to/libgadu/include:$CPLUS_INCLUDE_PATH``
2. ``export LD_LIBRARY_PATH=/your/path/to/libgadu/lib:$LD_LIBRARY_PATH``
3. ``export C_INCLUDE_PATH=/your/path/to/libgadu/include:$C_INCLUDE_PATH``

If you don't add it you could notice error "libgadu.h not found" at build time And "libgadu.so if not file or directory" or something like that at runtime.

##### Build Addon
in addon directory use *npm install* and if you have node-gyp installed globally you can use it *node-gyp clean configure build* or just run build.js *node build.js*

##### Test Addon
if you have no errors at build time, just check the test.js *node test.js* you should see *wrong login and password" 

##### How to use this addon?
You can just require it like that 
``const GaduGadu = require('./node-libgadu-addons-js-ts');``
or install it to your node_modules
``npm install ./node-libgadu-addons-js-ts``
and require it just like any npm package

### GaduGadu Statuses
use one of these number to change your status:
 
* 0 = GG_STATUS_NOT_AVAIL = 	Niedostępny
* 1 = GG_STATUS_NOT_AVAIL_DESCR = 	Niedostępny (z opisem)
* 2 = GG_STATUS_FFC = 	PoGGadaj ze mną
* 3 = GG_STATUS_FFC_DESCR = 	PoGGadaj ze mną (z opisem)
* 4 = GG_STATUS_AVAIL = Dostępny
* 5 = GG_STATUS_AVAIL_DESCR = Dostępny (z opisem)
* 6 = GG_STATUS_BUSY = Zajęty
* 7 = GG_STATUS_BUSY_DESCR = Zajęty (z opisem)
* 8 = GG_STATUS_DND = Nie przeszkadzać
* 9 = GG_STATUS_DND_DESCR = Nie przeszkadzać (z opisem)
* 10 = GG_STATUS_INVISIBLE = 	Niewidoczny
* 11 = GG_STATUS_INVISIBLE_DESCR = Niewidoczny (z opisem)
* 12 = GG_STATUS_BLOCKED = Zablokowany
* 13 = GG_STATUS_IMAGE_MASK = Maska bitowa oznaczająca ustawiony opis graficzny (tylko odbierane)
* 14 = GG_STATUS_DESCR_MASK = Maska bitowa oznaczająca ustawiony opis
* 15 = GG_STATUS_FRIENDS_MASK = Maska bitowa oznaczająca tryb tylko dla przyjaciół

### Javascript usage
#### Connection
```
let myGG = new GaduGadu(); 
myGG.event.on('connected', () => {
    //rest of events if you like, or method like sends
});
myGG.login(gg_number, 'gg password');
```

#### Methods
You can use this methods inside *connected event* or outside, it's depends on you but i preffer the inside way.

##### Debug (default: disabled)
```
myGG.debug(true); // enable debbuging
myGG.debug(false); // disable debbuging
```


##### Get contacts
```
myGG.contactsRequest().then(contacts => {
	// console.log(contacts);
}).catch((err) => { });
```

##### Send message
```
myGG.sendMessage(recipment_number, "message").then(() => {
	console.log('sended');
}).catch(err => { 
    console.log('sending error');
});
```
##### Change status
GG_STATUS_NUMBER = its number, you can check which number means above.
```
myGG.changeStatus(GG_STATUS_NUMBER, "description").then(() => {
	console.log('wyslano');
}).catch(err => { });
```

#### Events
You can listen for this events inside *connected events* or outside, i preffer inside way.

##### Receive new message
```
myGG.event.on('newMsg', (response) => { });
```

##### Message send event
```
myGG.event.on('msgSend', (response) => { });
```

##### Current statuses after login *Array*
```
myGG.event.on('statusChangedMulti', (response) => { });
```
##### Status changed
```
myGG.event.on('statusChanged', (response) => { });
```

##### Raw contacts data
```
myGG.event.on('receiveContacts', (response) => { });
```
##### Error events
```
myGG.event.on('error', (err) => { });
```
## Typescript usage
*soon* 






## Issues
If you nottice error "segmentation fault" after use *contactsRequest* then you should use *contactsRequest_old* method and should be all right!