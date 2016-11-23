#include "session.h"


Nan::Persistent<v8::Function> Session::constructor;

Session::Session() {
}

Session::~Session() {
}

void Session::Init(v8::Local<v8::Object> exports) {
  Nan::HandleScope scope;

  // Prepare constructor template
  v8::Local<v8::FunctionTemplate> tpl = Nan::New<v8::FunctionTemplate>(New);
  tpl->SetClassName(Nan::New("Session").ToLocalChecked());
  tpl->InstanceTemplate()->SetInternalFieldCount(1);

  // Prototype
  
  Nan::SetPrototypeMethod(tpl, "login", Login);
  Nan::SetPrototypeMethod(tpl, "ping", Ping);
  Nan::SetPrototypeMethod(tpl, "notify", Notify);
  Nan::SetPrototypeMethod(tpl, "checkEvents", CheckEvents);
  Nan::SetPrototypeMethod(tpl, "sendMessage", SendMessage);
  Nan::SetPrototypeMethod(tpl, "changeStatus", ChangeStatus);
  Nan::SetPrototypeMethod(tpl, "logout", Logout);
  Nan::SetPrototypeMethod(tpl, "contactsRequest", ContactsRequest);
  
  

  constructor.Reset(tpl->GetFunction());
  exports->Set(Nan::New("Session").ToLocalChecked(), tpl->GetFunction());
}

void Session::New(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  if (info.IsConstructCall()) {
    // Invoked as constructor: `new Session(...)`
    Session* obj = new Session();
    obj->Wrap(info.This());
    info.GetReturnValue().Set(info.This());
  } else {
    // Invoked as plain function `Session(...)`, turn into construct call.
    const int argc = 1;
    v8::Local<v8::Value> argv[argc] = { info[0] };
    v8::Local<v8::Function> cons = Nan::New<v8::Function>(constructor);
    info.GetReturnValue().Set(cons->NewInstance(argc, argv));
  }
}



void Session::Login(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Session* obj = ObjectWrap::Unwrap<Session>(info.Holder());
  v8::Local<v8::Function> callback = info[2].As<v8::Function>();
  const unsigned callback_argc = 1;
  
	if (info.Length() < 2) {
		v8::Local<v8::Value> callback_response[callback_argc] = { Nan::New(false) };
		Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, callback_argc, callback_response);
		return;
	}
	struct gg_login_params gg;
	memset(&gg, 0, sizeof(struct gg_login_params));
	gg.uin = info[0]->NumberValue();
	Nan::Utf8String ggPassword(info[1]->ToString());
	gg.password = *ggPassword;
	gg.protocol_features = GG_FEATURE_DND_FFC | GG_FEATURE_IMAGE_DESCR | GG_FEATURE_ALL | GG_FEATURE_MULTILOGON;
	gg.encoding = GG_ENCODING_UTF8;
	
	// gg_debug_level = 255;
	// gg.async = 1;
	struct ::gg_session * sess = ::gg_login(&gg);
	if (!sess) {
		gg_free_session(sess);
		v8::Local<v8::Value> callback_response[callback_argc] = { Nan::New(false) };
		Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, callback_argc, callback_response);
	}else {
		obj->session_ = sess;
		v8::Local<v8::Value> callback_response[callback_argc] = { Nan::New(true) };
		Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, callback_argc, callback_response);
	}
}

void Session::SendMessage(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Session* obj = ObjectWrap::Unwrap<Session>(info.Holder());
  v8::Local<v8::Function> callback = info[2].As<v8::Function>();
  const unsigned callback_argc = 1;
  
	if (info.Length() < 2) {
		v8::Local<v8::Value> callback_response[callback_argc] = { Nan::New(false) };
		Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, callback_argc, callback_response);
	}
  
	unsigned long uin = info[0]->NumberValue();
	unsigned char * text = reinterpret_cast<unsigned char*>(*Nan::Utf8String(info[1]->ToString()));
	int seq = gg_send_message(obj->session_, GG_CLASS_MSG, uin, text);

	v8::Local<v8::Value> callback_response[callback_argc] = { Nan::New(seq) };
	Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, callback_argc, callback_response);
}

void Session::ChangeStatus(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Session* obj = ObjectWrap::Unwrap<Session>(info.Holder());
	v8::Local<v8::Function> callback = info[2].As<v8::Function>();
	const unsigned callback_argc = 1;
	int result = 0;
	
	int statusNumber = info[0]->NumberValue();
	int status = 0;
	switch(statusNumber) {
		case 0: {
			status = GG_STATUS_NOT_AVAIL;
			break;
		}
		case 1: {
			status = GG_STATUS_NOT_AVAIL_DESCR;
			break;
		}
		case 2: {
			status = GG_STATUS_FFC;
			break;
		}
		case 3: {
			status = GG_STATUS_FFC_DESCR;
			break;
		}
		case 4: {
			status = GG_STATUS_AVAIL;
			break;
		}
		case 5: {
			status = GG_STATUS_AVAIL_DESCR;
			break;
		}
		case 6: {
			status = GG_STATUS_BUSY;
			break;
		}
		case 7: {
			status = GG_STATUS_BUSY_DESCR;
			break;
		}
		case 8: {
			status = GG_STATUS_DND;
			break;
		}
		case 9: {
			status = GG_STATUS_DND_DESCR;
			break;
		}
		case 10: {
			status = GG_STATUS_INVISIBLE;
			break;
		}
		case 11: {
			status = GG_STATUS_INVISIBLE_DESCR;
			break;
		}
		case 12: {
			status = GG_STATUS_BLOCKED;
			break;
		}
		case 13: {
			status = GG_STATUS_IMAGE_MASK;
			break;
		}
		case 14: {
			status = GG_STATUS_DESCR_MASK;
			break;
		}
		case 15: {
			status = GG_STATUS_FRIENDS_MASK;
			break;
		}
	}
	
	
	if (info[1]->NumberValue() != 0) {
		
		const char * description = *Nan::Utf8String(info[1]->ToString());;
		result = gg_change_status_descr(obj->session_, status, description);
	}else {
		result = gg_change_status(obj->session_, status);
	}
	
	v8::Local<v8::Value> callback_response[callback_argc] = { Nan::New(result) };
	Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, callback_argc, callback_response);
	
}

void Session::Ping(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Session* obj = ObjectWrap::Unwrap<Session>(info.Holder());
	if (gg_ping(obj->session_) < 0) {
		return;
	}
}

void Session::ContactsRequest(const Nan::FunctionCallbackInfo<v8::Value>& info) {
	Session* obj = ObjectWrap::Unwrap<Session>(info.Holder());
	v8::Local<v8::Function> callback = info[0].As<v8::Function>();
	const unsigned callback_argc = 1;
  
	if(gg_userlist100_request(obj->session_, GG_USERLIST100_GET, 0, GG_USERLIST100_FORMAT_TYPE_GG70, NULL) == 0) {
		v8::Local<v8::Value> callback_response[callback_argc] = { Nan::New(true) };
		Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, callback_argc, callback_response);
		return;
	}else {
		const char * error = strerror(errno);
		v8::Local<v8::Value> callback_response[callback_argc] = { Nan::New(error).ToLocalChecked() };
		Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, callback_argc, callback_response);
		return;
	}
}


void Session::Notify(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Session* obj = ObjectWrap::Unwrap<Session>(info.Holder());
	
	std::vector<uin_t> contacts;
	if ((info.Length() == 1) && info[0]->IsObject()) {
		v8::Local<v8::Object>  nodeContacts  = info[0]->ToObject();
		v8::Local<v8::Array> nodeContactsProperties = nodeContacts->GetOwnPropertyNames();
		
		std::vector<uin_t> vec(nodeContactsProperties->Length());
		
		for (int i = 0; i < nodeContactsProperties->Length(); ++i) {
			v8::Local<v8::Value> key = nodeContactsProperties->Get(i);
			v8::Local<v8::Value> value = nodeContacts->Get(key);
			
			uin_t uin = value->ToObject()->Uint32Value();
			vec[i] = uin;
		}
		contacts.swap(vec);
	}
	gg_notify(obj->session_, contacts.data(), contacts.size());
	return;
}

void Session::Logout(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Session* obj = ObjectWrap::Unwrap<Session>(info.Holder());
  gg_logoff(obj->session_);
  gg_free_session(obj->session_);
  return;
}

int Session::getStatusNumber(int status) {
	switch(status) {
		case GG_STATUS_NOT_AVAIL: {
			return 0;
		}
		case GG_STATUS_NOT_AVAIL_DESCR: {
			return 1;
		}
		case GG_STATUS_FFC: {
			return 2;
		}
		case GG_STATUS_FFC_DESCR: {
			return 3;
		}
		case GG_STATUS_AVAIL: {
			return 4;
		}
		case GG_STATUS_AVAIL_DESCR: {
			return 5;
		}
		case GG_STATUS_BUSY: {
			return 6;
		}
		case GG_STATUS_BUSY_DESCR: {
			return 7;
		}
		case GG_STATUS_DND: {
			return 8;
		}
		case GG_STATUS_DND_DESCR: {
			return 9;
		}
		case GG_STATUS_INVISIBLE: {
			return 10;
		}
		case GG_STATUS_INVISIBLE_DESCR: {
			return 11;
		}
		case GG_STATUS_BLOCKED: {
			return 12;
		}
		case GG_STATUS_IMAGE_MASK: {
			return 13;
		}
		case GG_STATUS_DESCR_MASK: {
			return 14;
		}
		case GG_STATUS_FRIENDS_MASK: {
			return 15;
		}
	}
}

void Session::CheckEvents(const Nan::FunctionCallbackInfo<v8::Value>& info) {
  Session* obj = ObjectWrap::Unwrap<Session>(info.Holder());
  
  v8::Local<v8::Function> callback = info[0].As<v8::Function>();
  const unsigned callback_argc = 1;
  v8::Local<v8::Value> callback_response[callback_argc];
  
	
	struct gg_event * e = 0;
	if (!(e = gg_watch_fd(obj->session_))) {
		gg_logoff(obj->session_);
		gg_free_session(obj->session_);
		
		v8::Local<v8::Object> objectResponse = Nan::New<v8::Object>();
		objectResponse->Set(Nan::New("error").ToLocalChecked(), Nan::New("Connection Lost").ToLocalChecked());
		callback_response[0] = objectResponse;
		Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, callback_argc, callback_response);
		return;
	}
		
	v8::Local<v8::Object> objectResponse = Nan::New<v8::Object>();
	objectResponse->Set(Nan::New("error").ToLocalChecked(), Nan::Null());
	
	switch (e->type) {
		case GG_EVENT_CONN_FAILED: {
			objectResponse->Set(Nan::New("error").ToLocalChecked(), Nan::New("disconnect").ToLocalChecked());
			gg_logoff(obj->session_);
			return;
		}
		case GG_EVENT_DISCONNECT: {
			objectResponse->Set(Nan::New("error").ToLocalChecked(), Nan::New("disconnect").ToLocalChecked());
			gg_logoff(obj->session_);
			return;
		}
		case GG_EVENT_MSG: {
			objectResponse->Set(Nan::New("error").ToLocalChecked(), Nan::Null());
			objectResponse->Set(Nan::New("type").ToLocalChecked(), Nan::New("newMsg").ToLocalChecked());
			
			objectResponse->Set(Nan::New("sender").ToLocalChecked(), Nan::New(e->event.msg.sender));
			objectResponse->Set(Nan::New("msgclass").ToLocalChecked(), Nan::New(e->event.msg.msgclass));
			objectResponse->Set(Nan::New("time").ToLocalChecked(), Nan::New<v8::Number>(e->event.msg.time));
			objectResponse->Set(Nan::New("seq").ToLocalChecked(), Nan::New<v8::Number>(e->event.msg.seq));
			
			char * message = reinterpret_cast<char*>(e->event.msg.message);
			objectResponse->Set(Nan::New("message").ToLocalChecked(), Nan::New(message).ToLocalChecked());
			char * xhtml_message = reinterpret_cast<char*>(e->event.msg.xhtml_message);
			objectResponse->Set(Nan::New("xhtmlMessage").ToLocalChecked(), Nan::New(xhtml_message).ToLocalChecked());
			
			v8::Local<v8::Array> recipients = Nan::New<v8::Array>();
			for (int i = 0; i < e->event.msg.recipients_count; i++) {
				recipients->Set(Nan::New(i), Nan::New(*(e->event.msg.recipients + i)));
			}
			objectResponse->Set(Nan::New("recipients").ToLocalChecked(), recipients);	
			break;
		}
		case GG_EVENT_ACK: {
			objectResponse->Set(Nan::New("error").ToLocalChecked(), Nan::Null());
			objectResponse->Set(Nan::New("type").ToLocalChecked(), Nan::New("msgSend").ToLocalChecked());
			objectResponse->Set(Nan::New("recipient").ToLocalChecked(), Nan::New(e->event.ack.recipient));
			objectResponse->Set(Nan::New("status").ToLocalChecked(), Nan::New(e->event.ack.status));
			objectResponse->Set(Nan::New("seq").ToLocalChecked(), Nan::New(e->event.ack.seq));
			break;
		}
		case GG_EVENT_STATUS60: {
			objectResponse->Set(Nan::New("error").ToLocalChecked(), Nan::Null());
			objectResponse->Set(Nan::New("type").ToLocalChecked(), Nan::New("statusChanged").ToLocalChecked());
			objectResponse->Set(Nan::New("uin").ToLocalChecked(), Nan::New(e->event.status60.uin));
			objectResponse->Set(Nan::New("status").ToLocalChecked(), Nan::New(getStatusNumber(e->event.status60.status)));
			objectResponse->Set(Nan::New("remote_ip").ToLocalChecked(), Nan::New(e->event.status60.remote_ip));
			objectResponse->Set(Nan::New("remote_port").ToLocalChecked(), Nan::New(e->event.status60.remote_port));
			objectResponse->Set(Nan::New("version").ToLocalChecked(), Nan::New(e->event.status60.version));
			objectResponse->Set(Nan::New("image_size").ToLocalChecked(), Nan::New(e->event.status60.image_size));
			if (e->event.status60.descr != NULL) {
				char *descr = reinterpret_cast<char*>(e->event.status60.descr);
				objectResponse->Set(Nan::New("descr").ToLocalChecked(), Nan::New(e->event.status60.descr).ToLocalChecked());
			}else {
				objectResponse->Set(Nan::New("descr").ToLocalChecked(), Nan::Null());
			}
			objectResponse->Set(Nan::New("time").ToLocalChecked(), Nan::New<v8::Number>(e->event.status60.time));
			
			break;
		}
		case GG_EVENT_NOTIFY60: {
			objectResponse->Set(Nan::New("error").ToLocalChecked(), Nan::Null());
			objectResponse->Set(Nan::New("type").ToLocalChecked(), Nan::New("statusChangedMulti").ToLocalChecked());
			
			v8::Local<v8::Array> statuses = Nan::New<v8::Array>();
			
			for (int i=0 ; e->event.notify60[i].uin != NULL ; i++) {
				v8::Local<v8::Object> currentStatus = Nan::New<v8::Object>();
				
				currentStatus->Set(Nan::New("uin").ToLocalChecked(), Nan::New(e->event.notify60[i].uin));
				currentStatus->Set(Nan::New("status").ToLocalChecked(), Nan::New(getStatusNumber(e->event.notify60[i].status)));
				if (e->event.notify60[i].descr != NULL) {
					char *descr = reinterpret_cast<char*>(e->event.notify60[i].descr);
					currentStatus->Set(Nan::New("descr").ToLocalChecked(), Nan::New(e->event.notify60[i].descr).ToLocalChecked());
				}else {
					currentStatus->Set(Nan::New("descr").ToLocalChecked(), Nan::Null());
				}
				currentStatus->Set(Nan::New("remote_ip").ToLocalChecked(), Nan::New(e->event.notify60[i].remote_ip));
				currentStatus->Set(Nan::New("remote_port").ToLocalChecked(), Nan::New(e->event.notify60[i].remote_port));
				currentStatus->Set(Nan::New("version").ToLocalChecked(), Nan::New(e->event.notify60[i].version));
				currentStatus->Set(Nan::New("time").ToLocalChecked(), Nan::New<v8::Number>(e->event.notify60[i].time));
				statuses->Set(i, currentStatus);
			}
			
			objectResponse->Set(Nan::New("statuses").ToLocalChecked(), statuses);
			
			break;
		}
		case GG_EVENT_USERLIST100_REPLY: {
			objectResponse->Set(Nan::New("error").ToLocalChecked(), Nan::Null());
			objectResponse->Set(Nan::New("type").ToLocalChecked(), Nan::New("receiveContacts").ToLocalChecked());
			objectResponse->Set(Nan::New("contacts").ToLocalChecked(), Nan::New(e->event.userlist100_reply.reply).ToLocalChecked());
			objectResponse->Set(Nan::New("version").ToLocalChecked(), Nan::New(e->event.userlist100_reply.version));
			break;
		}
		case GG_EVENT_NONE: {
			printf("GG_EVENT_NONE");
			objectResponse->Set(Nan::New("error").ToLocalChecked(), Nan::Null());
			objectResponse->Set(Nan::New("type").ToLocalChecked(), Nan::New("none").ToLocalChecked());
			break;
		}
		default:
			break;
	}
	gg_free_event(e);
	callback_response[0] = objectResponse;
	Nan::MakeCallback(Nan::GetCurrentContext()->Global(), callback, callback_argc, callback_response);
		
}


