#include <nan.h>
#include <libgadu/include/libgadu.h>
#include "session.h"

void InitAll(v8::Local<v8::Object> exports) {
  Session::Init(exports);
}

NODE_MODULE(gadu, InitAll)