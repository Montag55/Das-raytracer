# CMake generated Testfile for 
# Source directory: /home/lo/Dropbox/2. Semester/Programmiersprachen/Das-raytracer
# Build directory: /home/lo/Dropbox/2. Semester/Programmiersprachen/Das-raytracer/framework
# 
# This file includes the relevant testing commands required for 
# testing this directory and lists subdirectories to be tested as well.
add_test(tests "/home/lo/Dropbox/2. Semester/Programmiersprachen/Das-raytracer/framework/build/Release/tests")
subdirs(external/glfw-3.0.3)
subdirs(framework)
subdirs(source)
subdirs(tests)
