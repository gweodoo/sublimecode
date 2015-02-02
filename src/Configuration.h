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

#ifndef CONFIGURATION_H
#define CONFIGURATION_H

#include "Utils.h"

/**
 * Global configuration is shared through the application. It contains main user
 * informations : sources project path, destination path where artefacts will be
 * stored, and root_path (installation path) in order to find sublimeCode resources
 * (XSL, JS...)
 */
class Configuration {
private:
	std::string sourcesDir; ///< global position for sources path, given by user
	std::string destDir;    ///< global position for sublimeCode build folder
	std::string scRootPath; ///< sublimeCode resources folder
public:
	/// default constructor (\deprecated)
	explicit Configuration();
	/**
	 * Main constructor
	 * \param[in] sources the sources path
	 * \param[in] dest the build path
	 */
	Configuration(std::string sources, std::string dest);
	/**
	 * sources path getter
	 * \return a string containing the path
	 */
	std::string getSourcesDir() const;
	/**
	 * build path getter
	 * \return the build path as a string
	 */
	std::string getDestDir() const;
	/**
	 * root path getter
	 * \return resources folder as a string
	 */
	std::string getRootPath() const;
	/**
	 * Sometimes sources project path can change. This method allows to update
	 * sources path
	 * \param[in] newConfiguration new source path
	 */
	void setSourceDir(std::string newConfiguration);
	/// default destructor
	~Configuration();
};

#endif // CONFIGURATION_H
