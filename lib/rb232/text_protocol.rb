require 'rb232'
require 'observer'

module RB232

  class TextProtocol

    include Observable

    def initialize(port, separator = "\n")
      @port = port
      @separator = separator
    end

    attr_reader :separator
    attr_reader :port

    def start
      @stop = false
      @reader_thread = Thread.new {
        buffer = ""
        while (@stop == false)
          buffer += @port.read_string(1)
          messages = buffer.split(@separator,3)
          if messages.size > 1
            changed
            notify_observers(messages[0])
            buffer = ""
          end
        end
      }
    end

    def stop
      @stop = true
      @reader_thread.join
    end

  end

end