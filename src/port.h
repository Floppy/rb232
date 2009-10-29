#include "ruby.h"

/* module RB232 */
extern VALUE RB232;

/*   class Port */
extern VALUE RB232_Port;

/* Allocator for Port class */
VALUE rb232_port_alloc(VALUE klass);

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
VALUE rb232_port_initialize(int argc, VALUE* argv, VALUE self);

/*
 * Get the port name (for instance, '/dev/ttyS0' or 'COM1'), as set in Port#new.
 */
VALUE rb232_port_get_port_name(VALUE self);

/*
 * Get the baud rate, as set in the _options_ argument to Port#new.
 */
VALUE rb232_port_get_baud_rate(VALUE self);

/*
 * Get the number of data bits, as set in the _options_ argument to Port#new.
 */
VALUE rb232_port_get_data_bits(VALUE self);

/*
 * Get the parity setting, as set in the _options_ argument to Port#new.
 */
VALUE rb232_port_get_parity(VALUE self);

/*
 * Get the number of stop bits, as set in the _options_ argument to Port#new.
 */
VALUE rb232_port_get_stop_bits(VALUE self);

/*
 * Get the hardware flow control setting, as set in the _options_ argument to Port#new.
 */
VALUE rb232_port_get_hardware_flow_control(VALUE self);

/*
 * Read _count_ raw byte values from the port.
 * Returns an array of values. Useful for binary protocols.
 * call-seq:
 *   read_bytes(count)
 *
 */
VALUE rb232_port_read_bytes(VALUE self, VALUE count);

/*
 * Read _count_ characters from the port.
 * Returns a string. Useful for text-based protocols.
 * call-seq:
 *   read_string(count)
 *
 */
VALUE rb232_port_read_string(VALUE self, VALUE count);
