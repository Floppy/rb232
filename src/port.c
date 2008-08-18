#include "port.h"
#include "utility.h"

/* Module and class handles */
VALUE RB232 = Qnil;
VALUE RB232_Port = Qnil;

/*
 * Data structure for storing object data
 */
struct RB232_Port_Data {
    char* port_name;
    int baud_rate;
    int data_bits;
    BOOL parity;
    int stop_bits;
};

/*
 * Port data deallocation
 */
VALUE rb232_port_data_free(void* p) {
    struct RB232_Port_Data* port_data = p;
    free(port_data->port_name);
    free(port_data);
}

/*
 * Object allocation
 */
VALUE rb232_port_alloc(VALUE klass) {
    struct RB232_Port_Data* port_data = malloc(sizeof(struct RB232_Port_Data)); 
    memset(port_data, 0, sizeof(struct RB232_Port_Data));
    return Data_Wrap_Struct(klass, 0, rb232_port_data_free, port_data);
}

/*
 * Object initialization. Takes a port name and a hash of port options.
 */
VALUE rb232_port_initialize_with_options(VALUE self, VALUE port, VALUE options) {
    /* Get port data */
    struct RB232_Port_Data *port_data;
    Data_Get_Struct(self, struct RB232_Port_Data, port_data);
    /* Store port name */
    int port_name_len = RSTRING(port)->len;
    port_data->port_name = malloc(port_name_len + 1);
    strcpy(port_data->port_name, RSTRING(port)->ptr);
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
 * Equivalent Ruby would be def initialize(port, options = {}).
 * This function calls the _with_options version, providing an empty
 * hash if one is not passed in.
 */
VALUE rb232_port_initialize(int argc, VALUE* argv, VALUE self) {
    /* Only allow 1 or 2 arguments */
    if (argc == 0 || argc >= 3) {
        rb_raise(rb_eArgError, "wrong number of arguments (must be 1 or 2)");
        return Qnil;
    }
    /* Get port name */
    VALUE port = StringValue(argv[0]);
    /* Get options */
    VALUE options = Qnil;
    if (argc == 1)
        options = rb_hash_new();
    else {
        if (!rb_obj_is_kind_of(argv[1], rb_cHash))
            rb_raise(rb_eTypeError, "second argument must be a hash (port options)");
        else
            options = argv[1];
    }
    /* Call real initialize function */
    return rb232_port_initialize_with_options(self, port, options);
}

/*     def port_name */
VALUE rb232_port_get_port_name(VALUE self) {
    /* Get port data */
    struct RB232_Port_Data *port_data;
    Data_Get_Struct(self, struct RB232_Port_Data, port_data);
    /* Return baud rate */
    return rb_str_new2(port_data->port_name);
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
