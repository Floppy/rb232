#include "ruby.h"

/* module RB232 */
extern VALUE RB232;

/*   class Port */
extern VALUE RB232_Port;

/* Allocator for Port class */
VALUE rb232_port_alloc(VALUE klass);

/*     def initialize(options = {}) */
VALUE rb232_port_initialize(int argc, VALUE* argv, VALUE self);

/*     def port_name */
VALUE rb232_port_get_port_name(VALUE self);

/*     def baud_rate */
VALUE rb232_port_get_baud_rate(VALUE self);

/*     def data_bits */
VALUE rb232_port_get_data_bits(VALUE self);

/*     def parity */
VALUE rb232_port_get_parity(VALUE self);

/*     def stop_bits */
VALUE rb232_port_get_stop_bits(VALUE self);

/*     def read_bytes(count) */
VALUE rb232_port_read_bytes(VALUE self, VALUE count);

/*     def read_string(count) */
VALUE rb232_port_read_string(VALUE self, VALUE count);
