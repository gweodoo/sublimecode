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

CMAKE_MINIMUM_REQUIRED(VERSION 2.6)
PROJECT(SublimeCode)
SET(SC_VERSION "1.0")

##########################################
# Externals libs
FIND_PACKAGE(Doxygen)

##########################################
# Global vars :
# - SV_ENABLE_TESTS : activate test suite
# - SC_ENABLE_FOC : activate doxygen generation from source code

#########################################
# Sub loadings
ADD_SUBDIRECTORY(src)
ADD_SUBDIRECTORY(lib)

#Loading doc if enabled and doxygen found
IF(SC_ENABLE_DOC AND DOXYGEN_FOUND)
	ADD_SUBDIRECTORY(doc) 
ENDIF(SC_ENABLE_DOC AND DOXYGEN_FOUND)

#Need to define a framework
IF(SC_ENABLE_TESTS)
	ADD_SUBDIRECTORY(tests)
ENDIF(SC_ENABLE_TESTS)


