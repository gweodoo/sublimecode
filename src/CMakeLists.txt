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

file(GLOB_RECURSE SRC *.cpp)
file(GLOB_RECURSE HDR *.h)
file(GLOB_RECURSE UI *.ui)
file(GLOB_RECURSE RES *.qrc)

find_package(Qt4 REQUIRED QtGui QtXml QtXmlPatterns)
set(QT_USE_QTWEBKIT TRUE)

INCLUDE(${QT_USE_FILE})

QT4_WRAP_CPP(HDR_MOC ${HDR})
QT4_WRAP_UI(UI_HDR ${UI})
QT4_ADD_RESOURCES(RES_RCC ${RES})
INCLUDE_DIRECTORIES(${CMAKE_BINARY_DIR})
add_executable(sublimeCode ${SRC} ${HDR_MOC} ${UI_HDR} ${RES_RCC})

TARGET_LINK_LIBRARIES(sublimeCode ${QT_LIBRARIES} Qt4::QtGui Qt4::QtXml)

