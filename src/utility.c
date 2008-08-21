#include "utility.h"

/*
 * Get a key from a hash, or if it's not there, use the default.
 * A bit like doing hash[key] || default_val in Ruby.
 * Integer version.
 */
int rbx_int_from_hash_or_default(VALUE hash, VALUE key, int default_val) {
    VALUE data = (rb_hash_aref(hash, key));
    if (data == Qnil)
        return default_val;
    else
        return NUM2INT(data);
}

/*
 * Get a key from a hash, or if it's not there, use the default.
 * A bit like doing hash[key] || default_val in Ruby.
 * Boolean version.
 */
BOOL rbx_bool_from_hash_or_default(VALUE hash, VALUE key, BOOL default_val) {
    VALUE data = (rb_hash_aref(hash, key));
    if (data == Qnil)
        return default_val;
    else
        if (data == Qtrue)
            return TRUE;
        else
            return FALSE;
}
