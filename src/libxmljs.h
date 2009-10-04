#ifndef __libxmljs_h__
#define __libxmljs_h__

#define LIBXMLJS_VERSION '0.0.1'

#define BAD_ARGUMENTS      Exception::TypeError(String::New("Bad argument"))

#define LIBXMLJS_SET_METHOD(obj, name, callback)                      \
  obj->Set(v8::String::NewSymbol(name),                               \
           v8::FunctionTemplate::New(callback)->GetFunction())

#define LIBXMLJS_SET_PROTOTYPE_METHOD(templ, name, callback)              \
{                                                                         \
  v8::Local<v8::Signature> __callback##_SIG = v8::Signature::New(templ);  \
  v8::Local<v8::FunctionTemplate> __callback##_TEM =                      \
    v8::FunctionTemplate::New(callback, v8::Handle<v8::Value>(),          \
                          __callback##_SIG);                              \
  templ->PrototypeTemplate()->Set(v8::String::NewSymbol(name),            \
                                  __callback##_TEM);                      \
}

#define LIBXMLJS_SET_METHOD(obj, name, callback)                \
  obj->Set(v8::String::NewSymbol(name),                         \
           v8::FunctionTemplate::New(callback)->GetFunction())

#define LIBXMLJS_THROW_EXCEPTION(err)                         \
  v8::Local<v8::Value> exception = v8::Exception::TypeError(  \
    v8::String::New(err));                                    \
  ThrowException(exception);

#define LIBXMLJS_ARGUMENT_TYPE_CHECK(arg, type, err)                  \
  if (!arg->type()) {                                                 \
    Local<Value> exception = Exception::TypeError(String::New(err));  \
    return ThrowException(exception);                                 \
  }

#define BUILD_NODE(klass, type, name, node)                               \
{                                                                         \
  klass *name = new klass(node);                                          \
  v8::Handle<v8::Value> argv[1] = { v8::Null() };                         \
  v8::Persistent<v8::Object> name##JS = v8::Persistent<v8::Object>::New(  \
    klass::constructor_template->GetFunction()->NewInstance(1, argv));    \
  XmlObj::Wrap<type>(node, name##JS);                                     \
  name->Wrap(name##JS);                                                   \
}


#include <v8.h>
#include <libxml/parser.h>

namespace libxmljs {


} //namespace libxmljs

#endif //__libxmljs_h__
