require File.dirname(__FILE__) + '/spec_helper.rb'

TEST_PORT = '/dev/ttyUSB0'

describe RB232::Port do

  describe "upon creation" do

    it "cannot be created without a port name" do
      lambda {
        RB232::Port.new()
      }.should raise_error(ArgumentError, "wrong number of arguments (must be 1 or 2)")
    end

    it "can be created with port name only" do
      port = RB232::Port.new(TEST_PORT)
      port.should_not be_nil
      port.port_name.should == TEST_PORT
    end

    it "can be created with port name and a hash of options" do
      RB232::Port.new(TEST_PORT, {}).should_not be_nil
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
        RB232::Port.new(TEST_PORT, "hello")
      }.should raise_error(TypeError, "can't convert String into Hash")
    end

    it "raises an error if the port couldn't be opened" do
      lambda {
        RB232::Port.new("fail")
      }.should raise_error(ArgumentError, "couldn't open the specified port")
    end

  end

  describe "created with default options" do
    before :each do
      @port = RB232::Port.new(TEST_PORT)
    end

    it "should have a baud rate of 9600" do
      @port.baud_rate.should be(9600)
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
      @port = RB232::Port.new(TEST_PORT, :baud_rate => 19200, :data_bits => 7, :parity => true, :stop_bits => 2)
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

  describe "created with faulty options" do
 
    it "should only allow valid baud rates" do
      lambda {
        RB232::Port.new(TEST_PORT, :baud_rate => 12)
      }.should raise_error(ArgumentError, "baud_rate must be a valid value")
    end

    it "should only allow 5 to 8 data bits" do
      lambda {
        RB232::Port.new(TEST_PORT, :data_bits => 12)
      }.should raise_error(ArgumentError, "data_bits must be 5, 6, 7 or 8")
    end

    it "should only allow 1 or 2 stop bits" do
      lambda {
        RB232::Port.new(TEST_PORT, :stop_bits => 0)
      }.should raise_error(ArgumentError, "stop_bits must be 1 or 2")
    end

  end

  describe "reading from a device" do

    before :each do
      @port = RB232::Port.new(TEST_PORT)
    end

    it "should support reading a specified number of bytes" do
      data = @port.read_bytes(10)
      data.is_a?(Array).should be_true
      data.size.should == 10
    end

    it "should support reading a specified number of characters into a string" do
      data = @port.read_string(10)
      data.is_a?(String).should be_true
      data.size.should == 10
    end

  end

end