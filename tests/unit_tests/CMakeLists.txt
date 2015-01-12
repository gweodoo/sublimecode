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


set(TEST_FILES TagTest TagManagerTest TagParserTest LauncherCTagsTest)
set(SRC_FILES ${CMAKE_SOURCE_DIR}/src/Utils.cpp ${CMAKE_SOURCE_DIR}/src/Utils.cpp ${CMAKE_SOURCE_DIR}/src/Configuration.cpp ${CMAKE_SOURCE_DIR}/src/Tag.cpp ${CMAKE_SOURCE_DIR}/src/TagImpl.cpp ${CMAKE_SOURCE_DIR}/src/TagsManager.cpp ${CMAKE_SOURCE_DIR}/src/TagsManagerImpl.cpp ${CMAKE_SOURCE_DIR}/src/TagsParser.cpp ${CMAKE_SOURCE_DIR}/src/TagsParserImpl.cpp ${CMAKE_SOURCE_DIR}/src/LauncherCTags.cpp)

configure_file(${CMAKE_CURRENT_SOURCE_DIR}/tags ${CMAKE_CURRENT_BINARY_DIR}/tags)

foreach(i ${TEST_FILES})
	add_executable(${i}Bin ${i} ${SRC_FILES})
	add_test(UnitTest_${i} ${EXECUTABLE_OUTPUT_PATH}/${i}Bin)
endforeach(i)
