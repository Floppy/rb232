Gem::Specification.new do |s|
  s.name = "rb232"
  s.version = "0.2.2"
  s.date = "2008-08-21"
  s.summary = "A simple serial port library for Ruby"
  s.email = "james@floppy.org.uk"
  s.homepage = "http://github.com/Floppy/rb232"
  s.has_rdoc = true
  s.authors = ["James Smith"]
  s.files = ["README", "COPYING", "extconf.rb"] 
  s.files += ['src/port.c', 'src/port.h', 'src/rb232.c', 'src/utility.c', 'src/utility.h']
  s.files += ['lib/rb232/text_protocol.rb']
  s.files += ['examples/listen.rb']
  s.extensions << 'extconf.rb'
end