const Gadu = require('./../build/Release/gadu');
const EventEmitter = require('events');


/* OPIS STATUSOW: 

0 = GG_STATUS_NOT_AVAIL = 	Niedostępny
1 = GG_STATUS_NOT_AVAIL_DESCR = 	Niedostępny (z opisem)
2 = GG_STATUS_FFC = 	PoGGadaj ze mną
3 = GG_STATUS_FFC_DESCR = 	PoGGadaj ze mną (z opisem)
4 = GG_STATUS_AVAIL = Dostępny
5 = GG_STATUS_AVAIL_DESCR = Dostępny (z opisem)
6 = GG_STATUS_BUSY = Zajęty
7 = GG_STATUS_BUSY_DESCR = Zajęty (z opisem)
8 = GG_STATUS_DND = Nie przeszkadzać
9 = GG_STATUS_DND_DESCR = Nie przeszkadzać (z opisem)
10 = GG_STATUS_INVISIBLE = 	Niewidoczny
11 = GG_STATUS_INVISIBLE_DESCR = Niewidoczny (z opisem)
12 = GG_STATUS_BLOCKED = Zablokowany
13 = GG_STATUS_IMAGE_MASK = Maska bitowa oznaczająca ustawiony opis graficzny (tylko odbierane)
14 = GG_STATUS_DESCR_MASK = Maska bitowa oznaczająca ustawiony opis
15 = GG_STATUS_FRIENDS_MASK = Maska bitowa oznaczająca tryb tylko dla przyjaciół

*/



class GaduGadu {
	
	constructor() {
		this.libgadu = new Gadu.Session();
		this.event = new EventEmitter();
		this.pingInterval;
		
		this.contactsArray = [];
		this.contactsOnlyNumbers = [];
	}
	
	login(ggNumber, password) {
		this.libgadu.login(ggNumber, password, (status) => {
			if (status === true) {
				this.notify();
				this.event.emit('connected');
				this.watchForEvents();
			}else {
				this.event.emit('notConnected');
			}
		});
	}
	
	_ping() {
		this.pingInterval = setInterval(() => {
			this.libgadu.ping();
		}, 55000);
	}
	
	watchForEvents() {
		setTimeout(() => {
			this.libgadu.checkEvents(response => {
				if (response.error === null) {
					if (typeof response.type !== 'undefined') {
						switch(response.type) {
							case 'newMsg':
								delete response.error;
								delete response.type;
								this.event.emit('newMsg', response);
							break;
							case 'msgSend':
								delete response.error;
								delete response.type;
								this.event.emit('msgSend', response);
							break;
							case 'receiveContacts'://niesparsowane
								this.event.emit('receiveContacts', response.contacts, response.version);
							break;
							case 'statusChangedMulti':
								this.event.emit('statusChangedMulti', response);
							break;
							case 'statusChanged': //moj sie tez zmienia
								this.event.emit('statusChanged', response);
							break;
							case 'none':
								console.log('none!');
							break;
						}
					}
				}else {
					if (response.error === 'disconnect') {
						this.event.emit('disconnect');
					}else {
						this.event.emit('error', response.error);
					}
				}
				this.libgadu.ping();
				this.watchForEvents();
			});
		},50);
	}
	
	sendMessage(ggNumber, message) {
		return new Promise((resolve, reject) => {
			this.libgadu.sendMessage(ggNumber, message, (seq) => {
				if(seq > 0) {
					resolve();
				}else {
					reject();
				}
			});
			
		});
	}
	
	changeStatus(statusNumber, description) {
		return new Promise((resolve, reject) => {
			if (typeof description === 'undefined') {
				description = 0;
			}
			if (statusNumber  >= 0 && statusNumber < 16) {
				this.libgadu.changeStatus(statusNumber, description, (status) => {
					resolve(status);
				});
			}
		});
	}
	notify() {
		this.libgadu.notify();
	}
	
	logout() {
		this.libgadu.logout();
	}
	contactsRequest() {
		return new Promise((resolve, reject) => {
			this.event.on('receiveContacts', (contacts)=> {
				this._parseContacts(contacts);
				this.libgadu.notify(this.contactsOnlyNumbers);
				resolve(this.contactsArray);
			});
			this.libgadu.contactsRequest(function(status){
				if (status !== true) {
					reject(status);
				}
			});
		});
	}
		_parseContacts(contacts) {
			this.contactsArray = [];
			this.contactsOnlyNumbers = [];
			const contactsByLine = contacts.split("\n");
			contactsByLine
			.filter((contact, index) => index > 0)
			.map(contact => {
				const contactTwoParts = contact.split(';;;');
				if (contactTwoParts.length > 1) {
					const username = contactTwoParts[1];
					const ggNumberParts = contactTwoParts[2].split(';;');
					const ggNumber = parseInt(ggNumberParts[0], 10);
					this.contactsArray.push({username, ggNumber});
					this.contactsOnlyNumbers.push(parseInt(ggNumber, 10));
				}
			});
		}
	
}



module.exports = GaduGadu;