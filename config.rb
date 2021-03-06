#require 'compass'
require 'compass-colors'
require 'ninesixty'
#http://github.com/imathis/fancy-buttons
#require 'fancy-buttons'

# Require any additional compass plugins here.

project_type = :stand_alone
# Set this to the root of your project when deployed:
http_path = "/sites/all/themes"
css_dir = "./"
sass_dir = "sass"
images_dir = "images"
output_style = :nested
relative_assets = true
# http://groups.google.com/group/compass-users/browse_thread/thread/417429db92a92305
# sass_options = {:cache_location => "#{Compass.configuration.project_path}\tmp\sass-cache"}
sass_options = {:cache_location => "/tmp/sass-cache", :debug_info => true} 