#include "ruby.h"
#include "port.h"

/*
 * Library initialization.
 * Registers all classes and methods with the Ruby interpreter.
 * Called automatically on require 'rb232'.
 */
void Init_rb232() {
    RB232 = rb_define_module("RB232");
    RB232_Port = rb_define_class_under(RB232, "Port", rb_cObject);
    rb_define_method(RB232_Port, "initialize", rb232_port_initialize, -1);
}
