#!/usr/bin/env ruby

dir = File.dirname(__FILE__) + '/../lib'
$LOAD_PATH << dir unless $LOAD_PATH.include?(dir)

require 'rubygems'
require 'rb232'
require 'rb232/no_protocol'

class SimpleClient
  def update(message)
    puts("Message received:")
    puts message
    puts(message.split('').map{|x| Integer(?x)}.join(' '))
  end
end

require 'optparse'

# Command-line options - just baud rate and separator for now
options = {:port => '/dev/ttyS0', :baud_rate => 9600, :separator => "\n"}
OptionParser.new do |opts|
  opts.on("-p", "--serial_port SERIAL_PORT", "serial port") do |p|
    options[:port] = p
  end  
  opts.on("-b", "--baud_rate BAUD_RATE", "baud rate") do |b|
    options[:baud_rate] = b.to_i
  end  
end.parse!

port = RB232::Port.new(options[:port], :baud_rate => options[:baud_rate].to_i)

protocol = RB232::NoProtocol.new(port)
client = SimpleClient.new
protocol.add_observer(client)

# Start receiving messags
protocol.start

# Wait a while
sleep(30)

# OK, finish now
protocol.stop
