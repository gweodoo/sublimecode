/***************************************************************************/
/*                                                                        */
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

#ifndef CFileSystemModel_H
#define CFileSystemModel_H
#include <QDirModel>
#include <QFileSystemModel>
#include <QSet>
#include <QPersistentModelIndex>

/**
 * Handling sources tree to allows user the selection/deselection of paths parts
 * haven't a native way with Qt. This class manages QDir for well displaying in Dialog.
 */
class CFileSystemModel : public QDirModel
{
public:
	QSet<QPersistentModelIndex> checkedIndexes; ///< global list of selected paths

	/// default constructor
	CFileSystemModel();
	/**
	 * get current index state
	 * \param[in] index current index
	 * \param[in] role not really used here
	 * \return Qt::checked if index is checked
	 * \return Qt::unchecked if index is unchecked
	 */
	QVariant data(const QModelIndex &index, int role) const;
	/**
	 * change current index value data
	 * \param[in] index current index
	 * \param[in] value associated value
	 * \param[in] role not really used here
	 * \return Always true
	 */
	bool setData(const QModelIndex &index, const QVariant &value, int role);
	/**
	 * check all subpaths
	 * \param[in] mpath path to fullcheck
	 */
	void checkAllBoxes(QString mpath);
	/**
	 * uncheck all subpaths
	 * \param[in] mpath path to fulluncheck
	 */
	void uncheckAllBoxes(QString mpath);
	///default destructor
	virtual ~CFileSystemModel();
private:
	/**
	 * browse on subpaths
	 * \param[in] index current index
	 * \param[in] value associated value
	 * \return True all the time
	 */
	bool recursiveCheck(const QModelIndex &index, const QVariant &value);
};
#endif // CFileSystemModel_H
