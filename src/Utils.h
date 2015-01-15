/***************************************************************************/
/*                                                                         */
/* This file is part of Sublime Code.                                      */
/*                                                                         */
/* Sublime Code is free software: you can redistribute it and/or modify    */
/* it under the terms of the GNU General Public License as published by    */
/* the Free Software Foundation, either version 3 of the License, or       */
/* (at your option) any later version.                                     */
/*                                                                         */
/* Sublime Code is distributed in the hope that it will be useful,         */
/* but WITHOUT ANY WARRANTY; without even the implied warranty of          */
/* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           */
/* GNU General Public License for more details.                            */
/*                                                                         */
/* You should have received a copy of the GNU General Public License       */
/* along with Sublime Code.  If not, see <http://www.gnu.org/licenses/>.   */
/*                                                                         */
/***************************************************************************/

#ifndef UTILS_H
#define UTILS_H

/******* COMMON *******/
#include<cstdlib>
#include<unistd.h>
#include<iostream>
#include<iomanip>
#include<fstream>
#include<map>
#include<vector>
#include<typeinfo>
#include<cassert>
#include<functional>
#include<string>
#include<sstream>
/**** MACROS *****/
#ifdef NDEBUG
#define scDebug(u)
#define scError(u) {std::cerr << "ERROR: " << u << std::endl; exit(1);} while(0)
#define scWarning(u) {std::cerr << "WARNING: "<< u <<std::endl; exit(1);} while(0)

#else
#define scDebug(u) {std::cerr << u << " (" << __FILE__<<":"<<__LINE__<<")"<< std::endl; } while(0)
#define scError(u) {std::cerr << "ERROR: " << u << " (" << __FILE__<<":"<<__LINE__<<")"<< std::endl; exit(1);} while(0)
#define scWarning(u) {std::cerr << "WARNING: " << u << " (" << __FILE__<<":"<<__LINE__<<")"<< std::endl; exit(1);} while(0)

#endif

void checkNeededExecutable();
void checkCommandExistency(std::string command, bool required = false);

#endif
