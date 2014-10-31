Sublime Code Documentation (Last Edit : Oct 23rd 2014) Version 1.0  {#mainpage}
===============================================================================


PREAMBLE
-------------------------------------------------------------------------------

TBW


HOW-TO : CONFIGURATION, COMPILATION, AND INSTALLATION
-------------------------------------------------------------------------------

Compiler compliance :

| Compiler | Version | Status |
| :------: | :-----: | :----: |
|   GCC    |         |        |

First of all, to simply compile the project:

	$user> cd SublimeCode && mkdir -p build && cd build 
	$user> cmake .. 
	$user> make
	$user> make install

By default, `make install` command simply copy SublimeCode binary file into
/usr/local/bin. So, you need high privileges to do this. However, you can stop
at `make` step, the application will work as well.


#### CONFIGURATION ############################################################

There are some options to customize CMake producing. It is
possible to enable test-suite module from SublimeCode :

	$user> cmake .. -DSC_ENABLE_TESTS=yes 
	
Or enable documentation generatoin target for Sublime Code :

	$user> cmake .. -DSC_ENABLE_DOC=yes

You can change the prefix for installation with the comand:

	$user> cmake .. -DCMAKE_INSTALL_PREFIX=/path/as/prefix

Of course, all others CMake variables can be set at configuration time, the most
usefuls are:
 * CMAKE_BUILD_TYPE : Defines type of build (Debug or Release)
 * CMAKE_VERBOSE_MAKEFILE : Enable verbose mode during compilation
 * EXECUTABLE_OUTPUT_PATH : Where output files will be stored
 * CMAKE_CXX_FLAGS : Some extra flags to pass to the compilation
 * etc...


#### COMPILATION ##############################################################

Some target are available to customize SublimeCode compilation through CMake.
First of all, the most known option is -j, allowing to start multiple
independent targets simultaneously. According to what specified when CMake
creates makefiles, this command can be compile either the tool, the test-suite
or both:

	$user> make -j 

If you want to just execute the test-suite :
	$user> make test

To generate the documentation (through doxygen, generates HTML and Latex
documentation)

	$user> make doc


#### INSTALLATION #############################################################

	$user> make install

