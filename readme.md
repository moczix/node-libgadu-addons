# Node LibGadu Addon
 - - - -
### Description
Node GaduGadu library for javascript and typescript.

### Installation

npm install git+ssh://git@bitbucket.org/moczniak/node-libgadu-addons-js-ts.git


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