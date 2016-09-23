## Compiling

### Linux

	$ mkdir Build && cd Build
	$ cmake ..
	$ make

Then, to run it,

	$ cd Binaries
	$ ./ProjectName

### Windows (Visual Studio 2013)

1. Open CMake-Gui and set the source path, and the build path to the source path + Build
2. Add Entry OGRE_HOME and set it to your OGRE SDK path.
3. Configure for Visual Studio 2013
4. Generate
5. Open Build/ProjectName.sln
6. Build & Debug

On Windows, the DLLs needed to run the application are copied automatically to the binary folder.

## Tips

* If you are using version control, do not commit the Build folder. The generated build scripts are for your local working copy, not anyone else.
* To add Ogre plugins, simply add them to the `find_package` line in the `CMakeLists.txt` and add to linking/includes. You will also have to add the `loadPlugin` line in `Source/Core/Application.cpp` to load the library before you can use it.
* To add code modules, use the `add_project_module` macro.

## Notes

Created by Ron Kinard. Don't make this repository public

Visual Studio 2015 Preview is probably not supported because OGRE won't compile in it. It's a bummer. :disappointed:

You need a recent version of g++ to compile under Linux.
