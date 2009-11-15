#include "port.h"
#include "utility.h"

#include <fcntl.h>
#include <termios.h>
#include <unistd.h>

/* Module and class handles */
VALUE RB232 = Qnil;
VALUE RB232_Port = Qnil;

/*
 * Data structure for storing object data
 */
struct RB232_Port_Data {
    /* Settings */
    char* port_name;
    int baud_rate;
    int data_bits;
    BOOL parity;
    int stop_bits;
    BOOL hardware_flow_control;
    /* Internals */
    int port_handle;
    struct termios settings;
};

/* Helper for accessing port data */
struct RB232_Port_Data* get_port_data(VALUE self) {
    struct RB232_Port_Data *port_data;
    Data_Get_Struct(self, struct RB232_Port_Data, port_data);
    return port_data;
};

/*
 * Port data deallocation
 */
VALUE rb232_port_data_free(void* p) {
    struct RB232_Port_Data* port_data = p;
    /* Close port */
    close(port_data->port_handle);
    /* Free memory */
    free(port_data->port_name);
    free(port_data);
    /* Done */
    return Qnil;
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
    struct RB232_Port_Data *port_data = get_port_data(self);
    /* Store port name */
    int port_name_len = RSTRING(port)->len;
    port_data->port_name = malloc(port_name_len + 1);
    strcpy(port_data->port_name, RSTRING(port)->ptr);
    /* Store options */
    port_data->baud_rate = rbx_int_from_hash_or_default(options, ID2SYM(rb_intern("baud_rate")), 9600);
    port_data->data_bits = rbx_int_from_hash_or_default(options, ID2SYM(rb_intern("data_bits")), 8);
    port_data->parity = rbx_bool_from_hash_or_default(options, ID2SYM(rb_intern("parity")), FALSE);
    port_data->stop_bits = rbx_int_from_hash_or_default(options, ID2SYM(rb_intern("stop_bits")), 1);
    port_data->hardware_flow_control = rbx_bool_from_hash_or_default(options, ID2SYM(rb_intern("hardware_flow_control")), FALSE);
    /* Open the serial port */
    port_data->port_handle = open(port_data->port_name, O_RDWR | O_NOCTTY | O_NONBLOCK);
    if (port_data->port_handle < 0) {
        rb_raise(rb_eArgError, "couldn't open the specified port");
    }
    /* Set port settings */
	cfmakeraw(&(port_data->settings));
    port_data->settings.c_cflag = CRTSCTS | CLOCAL | CREAD;
    /* Baud rate */
	speed_t speed = B0;
    switch (port_data->baud_rate) {
        case 0:
            speed = B0;
            break;
        case 50:
            speed = B50;
            break;
        case 75:
            speed = B75;
            break;
        case 110:
            speed = B110;
            break;
        case 134:
            speed = B134;
            break;
        case 150:
            speed = B150;
            break;
        case 200:
            speed = B200;
            break;
        case 300:
            speed = B300;
            break;
        case 600:
            speed = B600;
            break;
        case 1200:
            speed = B1200;
            break;
        case 1800:
            speed = B1800;
            break;
        case 2400:
            speed = B2400;
            break;
        case 4800:
            speed = B4800;
            break;
        case 9600:
            speed = B9600;
            break;
        case 19200:
            speed = B19200;
            break;
        case 38400:
            speed = B38400;
            break;
        case 57600:
            speed = B57600;
            break;
        default:
            rb_raise(rb_eArgError, "baud_rate must be a valid value");
    }
  	cfsetspeed(&(port_data->settings), speed);
    /* Data bits */
    switch (port_data->data_bits) {
        case 8:
            port_data->settings.c_cflag |= CS8;
            break;
        case 7:
            port_data->settings.c_cflag |= CS7;
            break;
        case 6:
            port_data->settings.c_cflag |= CS6;
            break;
        case 5:
            port_data->settings.c_cflag |= CS5;
            break;
        default:
            rb_raise(rb_eArgError, "data_bits must be 5, 6, 7 or 8");
    }	
    /* Parity */
    if (port_data->parity) port_data->settings.c_cflag |= PARENB;
    /* Stop bits */
    switch (port_data->stop_bits) {
        case 2:
            port_data->settings.c_cflag |= CSTOPB;
            break;
        case 1:
            break;
        default:
            rb_raise(rb_eArgError, "stop_bits must be 1 or 2");
    }
#ifdef CNEW_RTSCTS
    /* Flow control */
    if (port_data->hardware_flow_control) port_data->settings.c_cflag |= CNEW_RTSCTS;
#endif
    /* Other settings */
    port_data->settings.c_iflag = IGNPAR | ICRNL;
    port_data->settings.c_oflag = 0;
    port_data->settings.c_lflag = ICANON;
    /* Flush input buffer */
    tcflush(port_data->port_handle, TCIFLUSH);
    /* Apply settings to port */
    tcsetattr(port_data->port_handle, TCSANOW, &port_data->settings);
    /* Done */
    return Qnil;
}

/*
 * Create a Port object, using the port filename specified in _port_ (e.g. '/dev/ttyS0' or 'COM1').
 *
 * Valid options are :baud_rate (integer), :data_bits (integer), :parity
 * (boolean), and :stop_bits (integer). Default values are 9600, 8, false, and 1 respectively.
 *
 * call-seq:
 *   new(port, options = {})
 *
 */
VALUE rb232_port_initialize(int argc, VALUE* argv, VALUE self) {
    /* Only allow 1 or 2 arguments */
    if (argc == 0 || argc >= 3) {
        rb_raise(rb_eArgError, "wrong number of arguments (must be 1 or 2)");
        return Qnil;
    }
    /* Get port name */
    SafeStringValue(argv[0]);
    VALUE port = argv[0];
    /* Get options */
    VALUE options = Qnil;
    if (argc == 1)
        options = rb_hash_new();
    else
        options = rb_convert_type(argv[1], T_HASH, "Hash", "to_hash");
    /* Call real initialize function */
    return rb232_port_initialize_with_options(self, port, options);
}

/*
 * Get the port name (for instance, '/dev/ttyS0' or 'COM1'), as set in Port#new.
 */
VALUE rb232_port_get_port_name(VALUE self) {
    /* Return baud rate */
    return rb_str_new2(get_port_data(self)->port_name);
}

/*
 * Get the baud rate, as set in the _options_ argument to Port#new.
 */
VALUE rb232_port_get_baud_rate(VALUE self) {
    /* Return baud rate */
    return rb_uint_new(get_port_data(self)->baud_rate);
}

/*
 * Get the number of data bits, as set in the _options_ argument to Port#new.
 */
VALUE rb232_port_get_data_bits(VALUE self) {
    /* Return baud rate */
    return rb_uint_new(get_port_data(self)->data_bits);
}

/*
 * Get the parity setting, as set in the _options_ argument to Port#new.
 */
VALUE rb232_port_get_parity(VALUE self) {
    /* Return parity setting */
    if (get_port_data(self)->parity == TRUE)
        return Qtrue;
    else
        return Qfalse;
}

/*
 * Get the number of stop bits, as set in the _options_ argument to Port#new.
 */
VALUE rb232_port_get_stop_bits(VALUE self) {
    /* Return baud rate */
    return rb_uint_new(get_port_data(self)->stop_bits);
}

/*
 * Get the hardware flow control setting, as set in the _options_ argument to Port#new.
 */
VALUE rb232_port_get_hardware_flow_control(VALUE self) {
    /* Return flow control setting */
    if (get_port_data(self)->hardware_flow_control == TRUE)
        return Qtrue;
    else
        return Qfalse;
}

/* 
 * Read raw data from port
 */
int rb232_port_read(VALUE self, char* buffer, VALUE count) {
    int bytes_to_read = NUM2INT(count);
    if (bytes_to_read > 255)
        rb_raise(rb_eArgError, "can't read more than 255 bytes at once");
    return read(get_port_data(self)->port_handle, buffer, bytes_to_read);
}

/*
 * Read up to _count_ raw byte values from the port.
 * Returns an array of values. If no data is currently available, a zero-length
 * array will be returned.
 * Useful for binary protocols.
 * call-seq:
 *   read_bytes(count)
 *
 */
VALUE rb232_port_read_bytes(VALUE self, VALUE count) {
    char buffer[256];
    int bytes_read = rb232_port_read(self, buffer, count);
    VALUE data = rb_ary_new();
    int i;
    for (i=0; i<bytes_read; i++) {
        rb_ary_push(data, INT2NUM(buffer[i]));
    }
    return data;
}

/*
 * Read up to _count_ characters from the port.
 * Returns a string. If no data is currently available, an empty string will be 
 * returned.
 * Useful for text-based protocols.
 * call-seq:
 *   read_string(count)
 *
 */
VALUE rb232_port_read_string(VALUE self, VALUE count) {
    char buffer[256];
    memset(buffer, 0, 256);
    int bytes_read = rb232_port_read(self, buffer, count);
    if (bytes_read < 1) bytes_read = 0;
    buffer[bytes_read] = 0;
    return rb_str_new2(buffer);
}
