#include "ruby.h"

VALUE RB232 = Qnil;
VALUE RB232_Port = Qnil;

void Init_rb232() {
	RB232 = rb_define_module("RB232");
	RB232_Port = rb_define_class_under(RB232, "Port", rb_cObject);
}
