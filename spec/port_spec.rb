require File.dirname(__FILE__) + '/spec_helper.rb'

describe RB232::Port do

  it "can be created with default options" do
    RB232::Port.new.should_not be_nil
  end

end
