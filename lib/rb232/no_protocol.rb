require 'rb232'
require 'observer'

module RB232

  # A helper class for RB232::Port which implements a simple
  # protocol on top of a serial port. Data is read from the serial port and sent
  # on without further processing
  #
  # This class is Observable. Client code should implement an update(string) function
  # add call NoProtocol#add_observer(self). When a message is received,
  # the update() function will be called with the message string.
  class NoProtocol

    include Observable

    # Create a protocol object. _port_ should be a RB232::Port object.
    def initialize(port)
      @port = port
    end

    # Port object, as specified in NoProtocol#new
    attr_reader :port

    # Begin processing incoming data from the serial port.
    # A thread is started which monitors the port for data.
    # Call NoProtocol#stop to halt this process.
    def start
      @stop = false
      @reader_thread = Thread.new {
        while (@stop == false)
          # Read in data
          new_string = @port.read_string(5)
          if new_string.length > 0
            changed
            notify_observers(new_string)
          end
        end
      }
    end

    # Stop processing incoming data from the serial port.
    def stop
      @stop = true
      @reader_thread.join
    end

  end

end
