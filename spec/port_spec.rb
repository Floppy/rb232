require File.dirname(__FILE__) + '/spec_helper.rb'

describe RB232::Port do

  describe "upon creation" do

    it "can be created with default options" do
      RB232::Port.new.should_not be_nil
    end

    it "can be created with a hash of options" do
      RB232::Port.new({}).should_not be_nil
    end

    it "takes only one argument" do
      lambda {
        RB232::Port.new({},{})
      }.should raise_error(ArgumentError, "wrong number of arguments (must be 0 or 1)")
    end

    it "ensures that argument is a hash" do
      lambda {
        RB232::Port.new("hello")
      }.should raise_error(ArgumentError, "argument must be a hash")
    end

  end

  describe "created with default options" do
    before :each do
      @port = RB232::Port.new
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
      @port = RB232::Port.new(:baud_rate => 19200, :data_bits => 7, :parity => true, :stop_bits => 2)
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
