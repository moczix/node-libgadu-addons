#ifndef SESSION_H
#define SESSION_H

#include <nan.h>
#include <libgadu/libgadu.h>


class Session : public Nan::ObjectWrap {
 public:
  static void Init(v8::Local<v8::Object> exports);

 private:
  explicit Session();
  ~Session();

  static void New(const Nan::FunctionCallbackInfo<v8::Value>& info);

  
  static Nan::Persistent<v8::Function> constructor;
  
	
	static void Login(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Ping(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Notify(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void CheckEvents(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void SendMessage(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void ChangeStatus(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void Logout(const Nan::FunctionCallbackInfo<v8::Value>& info);
	static void ContactsRequest(const Nan::FunctionCallbackInfo<v8::Value>& info);
	
	static int getStatusNumber(int status);
	
	
	struct gg_session * session_;
	  
	struct gg_login_params login_params_;
	
  
};

#endif