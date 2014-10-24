CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(SublimeCode)

FIND_PACKAGE(Doxygen)

set(SC_ENABLE_TESTS NO)
set(SC_ENABLE_DOC NO)

add_subdirectory(src)
add_subdirectory(lib)

#Need to define a framework
if(SC_ENABLE_TESTS)
	add_subdirectory(tests)
endif(SC_ENABLE_TESTS)

if(SC_ENABLE_DOC AND DOXYGEN_FOUND)
	add_subdirectory(doc) 
endif(SC_ENABLE_DOC AND DOXYGEN_FOUND)
