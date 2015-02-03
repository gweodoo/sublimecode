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
#include <cerrno>
#include <cstring>
/**** MACROS *****/
#ifdef NDEBUG
#define scDebug(u)
#define scError(u) {std::cerr << "ERROR: " << u << std::endl; exit(1);} while(0)
#define scWarning(u) {std::cerr << "WARNING: "<< u <<std::endl;} while(0)
#else
#define scDebug(u) {std::cerr << u << " (" << __FILE__<<":"<<__LINE__<<")"<< std::endl; } while(0)
#define scError(u) {std::cerr << "ERROR: " << u << " (" << __FILE__<<":"<<__LINE__<<")"<< std::endl; exit(1);} while(0)
#define scWarning(u) {std::cerr << "WARNING: " << u << " (" << __FILE__<<":"<<__LINE__<<")"<< std::endl;} while(0)

#endif

/// Global macro to restart application
#define APPLICATION_REBOOT 12345789
#define UNUSED(u) (void)(u)
/**
 * check if a given command as string is in path
 * \param[in] command the command name to check
 * \param[in] required true if command is required to execute sublimeCode, false otherwise
 * \return true if command is found, false otherwise. If false, printing on standard output
 */
bool checkCommandExistency(std::string command, bool required = false);

/**
 * Split a given chain according to a pattern
 * \param[in] chain the chain to split
 * \param[in] split the pattern
 * \return the list of pieces split by the function, as a map (name of the field, n-th field)
 */
std::map<std::string, int> splitOn(std::string chain, char split);
#endif
