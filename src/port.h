#include "ruby.h"

/* module RB232 */
extern VALUE RB232;

/*   class Port */
extern VALUE RB232_Port;

/* Allocator for Port class */
VALUE rb232_port_alloc(VALUE klass);

/*     def initialize(options = {}) */
VALUE rb232_port_initialize(int argc, VALUE* argv, VALUE self);

/*     def baud_rate */
VALUE rb232_port_get_baud_rate(VALUE self);
