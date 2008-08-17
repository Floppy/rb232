#include "ruby.h"

/* module RB232 */
extern VALUE RB232;

/*   class Port */
extern VALUE RB232_Port;

/*     def initialize(options = {}) */
VALUE rb232_port_initialize(int argc, VALUE* argv, VALUE self);
