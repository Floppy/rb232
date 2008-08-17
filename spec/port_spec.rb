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

end
