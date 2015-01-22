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

#include "CFileSystemModel.h"
#include "Utils.h"
#include <QDebug>

CFileSystemModel::CFileSystemModel()
{
}

Qt::ItemFlags CFileSystemModel::flags(const QModelIndex &index) const
{
    return QDirModel::flags(index) | Qt::ItemIsUserCheckable;
}
QVariant CFileSystemModel::data(const QModelIndex &index, int role) const
{
    if(role == Qt::CheckStateRole)
    {
        return checkedIndexes.contains(index) ? Qt::Checked : Qt::Unchecked;
    }
    else
    {
        return QDirModel::data(index, role);
    }
}
bool CFileSystemModel::setData(const QModelIndex &index, const QVariant &value, int role)
{
    if(role == Qt::CheckStateRole)
    {
        if(value == Qt::Checked)
        {
            checkedIndexes.insert(index);
            if(hasChildren(index) == true)
            {
                recursiveCheck(index, value);
            }
        }
        else
        {
            checkedIndexes.remove(index);
            if(hasChildren(index) == true)
            {
                recursiveCheck(index, value);
            }
        }
        emit dataChanged(index, index);
        return true;
    }
    return QDirModel::setData(index, value, role);
}
bool CFileSystemModel::recursiveCheck(const QModelIndex &index, const QVariant &value)
{
    if(hasChildren(index))
    {
        int i;
        int childrenCount = rowCount(index);
        QModelIndex child;
        for(i=0; i<childrenCount; i++)
	{
	    child = QDirModel::index(i, 0, index);
            setData(child, value, Qt::CheckStateRole);
        }
    }

    return true;
}

void CFileSystemModel::checkAllBoxes(QString mpath)
{
    QModelIndex parent;
    parent = this->index(mpath, 0);
    QModelIndex child;
    int i;
    int childrenCount = rowCount(parent);
    for(i=0; i<childrenCount; i++)
    {
	child = QDirModel::index(i, 0, parent);
        setData(child, 2, Qt::CheckStateRole);
    }
}
 
void CFileSystemModel::uncheckAllBoxes(QString mpath)
{
    QModelIndex parent;
    parent = this->index(mpath, 0);
    QModelIndex child;
    int i;
    int childrenCount = rowCount(parent);
    for(i=0; i<childrenCount; i++)
    {
	child = QDirModel::index(i, 0, parent);
	setData(child, 0, Qt::CheckStateRole);
    }
}



