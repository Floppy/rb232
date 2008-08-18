Gem::Specification.new do |s|
  s.name = "rb232"
  s.version = "0.1.0"
  s.date = "2008-08-18"
  s.summary = "A simple serial port library for Ruby"
  s.email = "james@floppy.org.uk"
  s.homepage = "http://github.com/Floppy/rb232"
  s.has_rdoc = false
  s.authors = ["James Smith"]
  s.files = ["README", "COPYING", "extconf.rb"] 
  s.files += ['src/port.c', 'src/port.h', 'src/rb232.c', 'src/utility.c', 'src/utility.h']
  s.extensions << 'extconf.rb'
end