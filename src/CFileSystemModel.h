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
class CFileSystemModel : public QDirModel
{
public:
    CFileSystemModel();
    QSet<QPersistentModelIndex> checkedIndexes;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    QVariant data(const QModelIndex &index, int role) const;
    bool setData(const QModelIndex &index, const QVariant &value, int role);
    void checkAllBoxes(QString mpath);
    void uncheckAllBoxes(QString mpath);
private:
    bool recursiveCheck(const QModelIndex &index, const QVariant &value);
};
#endif // CFileSystemModel_H