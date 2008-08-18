require File.dirname(__FILE__) + '/spec_helper.rb'

describe RB232::Port do

  describe "upon creation" do

    it "cannot be created without a port name" do
      lambda {
        RB232::Port.new()
      }.should raise_error(ArgumentError, "wrong number of arguments (must be 1 or 2)")
    end

    it "can be created with port name only" do
      port = RB232::Port.new('/dev/ttyS0')
      port.should_not be_nil
      port.port_name.should == '/dev/ttyS0'
    end

    it "can be created with port name and a hash of options" do
      RB232::Port.new('/dev/ttyS0', {}).should_not be_nil
    end

    it "takes only two arguments" do
      lambda {
        RB232::Port.new('',{},{})
      }.should raise_error(ArgumentError, "wrong number of arguments (must be 1 or 2)")
    end

    it "ensures that first argument is a string" do
      lambda {
        RB232::Port.new({})
      }.should raise_error(TypeError, "can't convert Hash into String")
    end

    it "ensures that second argument is a hash" do
      lambda {
        RB232::Port.new('/dev/ttyS0', "hello")
      }.should raise_error(TypeError, "second argument must be a hash (port options)")
    end

  end

  describe "created with default options" do
    before :each do
      @port = RB232::Port.new('/dev/ttyS0')
    end

    it "should have a baud rate of 2400" do
      @port.baud_rate.should be(2400)
    end

    it "should have 8 data bits" do
      @port.data_bits.should be(8)
    end

    it "should have parity set to false" do
      @port.parity.should be_false
    end

    it "should have 1 stop bit" do
      @port.stop_bits.should be(1)
    end

  end

  describe "created with non-default options" do
    before :each do
      @port = RB232::Port.new('/dev/ttyS0', :baud_rate => 19200, :data_bits => 7, :parity => true, :stop_bits => 2)
    end

    it "should have a baud rate of 19200" do
      @port.baud_rate.should be(19200)
    end

    it "should have 7 data bits" do
      @port.data_bits.should be(7)
    end

    it "should have parity set to true" do
      @port.parity.should be_true
    end

    it "should have 2 stop bits" do
      @port.stop_bits.should be(2)
    end

  end

end
