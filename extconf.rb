require 'mkmf'

$CFLAGS = '-Wall ' + $CFLAGS

create_makefile('rb232', 'src')
