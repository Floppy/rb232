require 'rubygems'
require 'spec'

$:.unshift(File.dirname(__FILE__) + '/..')
require 'rb232'

Spec::Runner.configure do |config|
  config.mock_with :flexmock
end

