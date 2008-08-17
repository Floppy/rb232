#include "ruby.h"

#define BOOL char
#define TRUE 1
#define FALSE 0

/*
 * Get a key from a hash, or if it's not there, use the default.
 * A bit like doing hash[key] || default_val in Ruby.
 * Integer version.
 */
int rbx_int_from_hash_or_default(VALUE hash, VALUE key, int default_val);

/*
 * Get a key from a hash, or if it's not there, use the default.
 * A bit like doing hash[key] || default_val in Ruby.
 * Boolean version.
 */
BOOL rbx_bool_from_hash_or_default(VALUE hash, VALUE key, BOOL default_val);
