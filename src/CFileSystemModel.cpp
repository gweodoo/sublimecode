#include "CFileSystemModel.h"
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
}



