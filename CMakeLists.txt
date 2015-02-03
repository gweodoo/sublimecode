###########################################################################
#                                                                         #
# This file is part of Sublime Code.                                      #
#                                                                         #
# Sublime Code is free software: you can redistribute it and/or modify    #
# it under the terms of the GNU General Public License as published by    #
# the Free Software Foundation, either version 3 of the License, or       #
# (at your option) any later version.                                     #
#                                                                         #
# Sublime Code is distributed in the hope that it will be useful,         #
# but WITHOUT ANY WARRANTY; without even the implied warranty of          #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           #
# GNU General Public License for more details.                            #
#                                                                         #
# You should have received a copy of the GNU General Public License       #
# along with Sublime Code.  If not, see <http://www.gnu.org/licenses/>.   #
#                                                                         #
###########################################################################

CMAKE_MINIMUM_REQUIRED(VERSION 2.8)
PROJECT(SublimeCode)

##########################################
# Global vars :
# - SV_ENABLE_TESTS : activate test suite
# - SC_ENABLE_FOC : activate doxygen generation from source code
set(SC_VERSION "1.0")
set(SC_ENABLE_TESTS no CACHE BOOL "Var to enable tests")
set(SC_ENABLE_DOC yes CACHE BOOL "var to enable doc")
set(SC_EXTRA_FLAGS "-Wall -ansi -pedantic -Wextra")
#CMake Vars
set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${CMAKE_SOURCE_DIR}/cmake/")
set(CMAKE_VERBOSE_MAKEFILE "no")
#set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin CACHE)
set(CMAKE_BUILD_TYPE "Release")
set(CMAKE_PREFIX_PATH "${CMAKE_BINARY_DIR}/install")

##########################################
#displaying vars
include(cmake/macros.cmake)
print_variable_content("SC_VERSION")
print_variable_content("CMAKE_BUILD_TYPE")
print_variable_status("SC_ENABLE_DOC")
print_variable_status("SC_ENABLE_TESTS")
print_variable_status("CMAKE_VERBOSE_MAKEFILE")
print_variable_content("SC_EXTRA_FLAGS")
print_variable_content("CMAKE_EXECUTABLE_OUTPUT_PATH")
print_variable_content("CMAKE_PREFIX_PATH")

##########################################
# Externals libs
#FIND_PACKAGE(CTags REQUIRED) #checked by packages
#FIND_PACKAGE(CScope REQUIRED) # checked by package
FIND_PACKAGE(Qt4 REQUIRED QtGui QtXml QtXmlPatterns)
#FIND_PACKAGE(Cloc) # checked by package
FIND_PACKAGE(Doxygen)

#########################################
# Sub loadings
ADD_SUBDIRECTORY(src)

#Loading doc if enabled and doxygen found
IF(SC_ENABLE_DOC AND DOXYGEN_FOUND)
	ADD_SUBDIRECTORY(doc) 
ENDIF(SC_ENABLE_DOC AND DOXYGEN_FOUND)

#Need to define a framework
IF(SC_ENABLE_TESTS)
	enable_testing()
	ADD_SUBDIRECTORY(tests)
ENDIF(SC_ENABLE_TESTS)


