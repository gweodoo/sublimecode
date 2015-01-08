#ifndef CFileSystemModel_H
#define CFileSystemModel_H
#include <QDirModel>
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
private:
    bool recursiveCheck(const QModelIndex &index, const QVariant &value);
};
#endif // CFileSystemModel_H