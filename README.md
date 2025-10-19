This is testing repo used for me to learn OpenGL using GLEW.

After cloning, don't forget to set the project's properties
  configuration properties ->
    c/c++ -> 
      general -> additional include directories -> [location of glew/include directory]
    linker -> 
      general -> additional library dependencies -> [location of glew/lib/Release/x64]
      input -> additional dependencies -> [add glew32.lib; opengl32.lib to the beginning of whatever is already there]

Additionally, copy the glew32.dll file into the x64/release (or debug, whichever you use to compile).
