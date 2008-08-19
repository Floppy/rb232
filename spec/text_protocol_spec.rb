require File.dirname(__FILE__) + '/spec_helper.rb'

require 'rb232/text_protocol'

describe RB232::TextProtocol do

  describe "upon creation" do

    it "requires a Port object" do
      port = flexmock "port"
      protocol = RB232::TextProtocol.new(port)
      protocol.should_not be_nil
    end

    it "provides access to the Port object" do
      port = flexmock "port"
      port.should_receive(:test).and_return(true)
      protocol = RB232::TextProtocol.new(port)
      protocol.port.test.should be_true
    end

    it 'has a default separator of \n' do
      port = flexmock "port"
      protocol = RB232::TextProtocol.new(port)
      protocol.separator.should == "\n"
    end

    it "accepts an optional separator character" do
      port = flexmock "port"
      protocol = RB232::TextProtocol.new(port, " ")
      protocol.separator.should == " "
    end

  end

  describe "after creation" do

    class TestClient
      def update(message)
        @messages ||= []
        @messages << message
      end
      attr_reader :messages
    end

    it "is Observable" do
      port = flexmock "port"
      protocol = RB232::TextProtocol.new(port)
      protocol.is_a?(Observable).should be_true
    end

    it "extracts messages and sends them to Observers" do
      port = flexmock "port"
      port.should_receive(:read_string).and_return('h','e','l','l','o',' ','w','o','r','l','d', ' ')
      protocol = RB232::TextProtocol.new(port, ' ')
      client = TestClient.new
      protocol.add_observer(client)
      protocol.start
      client.messages.should == ["hello", "world"]
      protocol.stop
    end

  end

end