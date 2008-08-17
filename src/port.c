#include "port.h"

/* Module and class handles */
VALUE RB232 = Qnil;
VALUE RB232_Port = Qnil;

/*
 * Data structure for storing object data
 */
struct RB232_Port_Data {
    int baud_rate;
};

/*
 * Object allocation
 */
VALUE rb232_port_alloc(VALUE klass) {
    struct RB232_Port_Data* port_data = malloc(sizeof(struct RB232_Port_Data)); 
    memset(port_data, 0, sizeof(struct RB232_Port_Data));
    return Data_Wrap_Struct(klass, 0, free, port_data);
}

/*
 * Object initialization. Takes a hash of port options.
 */
VALUE rb232_port_initialize_with_options(VALUE self, VALUE options) {
    /* Get port data */
    struct RB232_Port_Data *port_data;
    Data_Get_Struct(self, struct RB232_Port_Data, port_data);
    /* Store options */
    VALUE baud_rate = (rb_hash_aref(options, ID2SYM(rb_intern("baud_rate"))));
    if (baud_rate == Qnil)
        port_data->baud_rate = 2400;
    else
        port_data->baud_rate = NUM2INT(baud_rate);
    /* Done */
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

/*     def baud_rate */
VALUE rb232_port_get_baud_rate(VALUE self) {
    /* Get port data */
    struct RB232_Port_Data *port_data;
    Data_Get_Struct(self, struct RB232_Port_Data, port_data);
    /* Return baud rate */
    return rb_uint_new(port_data->baud_rate);
}
