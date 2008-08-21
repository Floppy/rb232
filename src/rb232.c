#include "ruby.h"
#include "port.h"

/*
 * Serial port communications. The class RB232::Port provides access to a hardware
 * port on the local machine. Currently only Linux systems are supported.
 */
void Init_rb232() {
    RB232 = rb_define_module("RB232");
    RB232_Port = rb_define_class_under(RB232, "Port", rb_cObject);
    rb_define_alloc_func(RB232_Port, rb232_port_alloc);
    rb_define_method(RB232_Port, "initialize", rb232_port_initialize, -1); /* in port.c */
    rb_define_method(RB232_Port, "port_name", rb232_port_get_port_name, 0); /* in port.c */
    rb_define_method(RB232_Port, "baud_rate", rb232_port_get_baud_rate, 0); /* in port.c */
    rb_define_method(RB232_Port, "data_bits", rb232_port_get_data_bits, 0); /* in port.c */
    rb_define_method(RB232_Port, "parity", rb232_port_get_parity, 0); /* in port.c */
    rb_define_method(RB232_Port, "stop_bits", rb232_port_get_stop_bits, 0); /* in port.c */
    rb_define_method(RB232_Port, "read_bytes", rb232_port_read_bytes, 1); /* in port.c */
    rb_define_method(RB232_Port, "read_string", rb232_port_read_string, 1); /* in port.c */
}
