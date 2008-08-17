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
    rb_define_alloc_func(RB232_Port, rb232_port_alloc);
    rb_define_method(RB232_Port, "initialize", rb232_port_initialize, -1);
    rb_define_method(RB232_Port, "baud_rate", rb232_port_get_baud_rate, 0);
    rb_define_method(RB232_Port, "data_bits", rb232_port_get_data_bits, 0);
    rb_define_method(RB232_Port, "parity", rb232_port_get_parity, 0);
    rb_define_method(RB232_Port, "stop_bits", rb232_port_get_stop_bits, 0);
}
