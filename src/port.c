#include "port.h"

VALUE RB232 = Qnil;
VALUE RB232_Port = Qnil;

/*
 * Object initialization. Takes a hash of port options.
 */
VALUE rb232_port_initialize_with_options(VALUE self, VALUE options) {
    return Qnil;
}

/*
 * This function implements a default argument for initialize().
 * Equivalent Ruby would be def initialize(options = {}).
 * This function calls the _with_options version, providing an empty
 * hash if one is not passed in.
 */
VALUE rb232_port_initialize(int argc, VALUE* argv, VALUE self) {
    if (argc == 0)
        return rb232_port_initialize_with_options(self, rb_hash_new());
    else if (argc == 1)
        if (!rb_obj_is_kind_of(argv[0], rb_cHash))
            rb_raise(rb_eArgError, "argument must be a hash");
        else
            return rb232_port_initialize_with_options(self, argv[0]);
    else
        rb_raise(rb_eArgError, "wrong number of arguments (must be 0 or 1)");
}

