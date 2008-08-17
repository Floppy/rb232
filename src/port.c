#include "port.h"
#include "utility.h"

/* Module and class handles */
VALUE RB232 = Qnil;
VALUE RB232_Port = Qnil;

/*
 * Data structure for storing object data
 */
struct RB232_Port_Data {
    int baud_rate;
    int data_bits;
    BOOL parity;
    int stop_bits;
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
    port_data->baud_rate = rbx_int_from_hash_or_default(options, ID2SYM(rb_intern("baud_rate")), 2400);
    port_data->data_bits = rbx_int_from_hash_or_default(options, ID2SYM(rb_intern("data_bits")), 8);
    port_data->parity = rbx_bool_from_hash_or_default(options, ID2SYM(rb_intern("parity")), FALSE);
    port_data->stop_bits = rbx_int_from_hash_or_default(options, ID2SYM(rb_intern("stop_bits")), 1);
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

/*     def data_bits */
VALUE rb232_port_get_data_bits(VALUE self) {
    /* Get port data */
    struct RB232_Port_Data *port_data;
    Data_Get_Struct(self, struct RB232_Port_Data, port_data);
    /* Return baud rate */
    return rb_uint_new(port_data->data_bits);
}

/*     def parity */
VALUE rb232_port_get_parity(VALUE self) {
    /* Get port data */
    struct RB232_Port_Data *port_data;
    Data_Get_Struct(self, struct RB232_Port_Data, port_data);
    /* Return baud rate */
    if (port_data->parity == TRUE)
        return Qtrue;
    else
        return Qfalse;
}

/*     def stop_bits */
VALUE rb232_port_get_stop_bits(VALUE self) {
    /* Get port data */
    struct RB232_Port_Data *port_data;
    Data_Get_Struct(self, struct RB232_Port_Data, port_data);
    /* Return baud rate */
    return rb_uint_new(port_data->stop_bits);
}
