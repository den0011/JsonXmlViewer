#include "searchproxymodel.h"

SearchProxyModel::SearchProxyModel(QObject* parent)
    : QSortFilterProxyModel(parent)
{
    setRecursiveFilteringEnabled(true);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

bool SearchProxyModel::filterAcceptsRow(int row,
                                       const QModelIndex& parent) const
{
    QModelIndex keyIndex   = sourceModel()->index(row, 0, parent);
    QModelIndex valueIndex = sourceModel()->index(row, 1, parent);

    if (keyIndex.data().toString().contains(filterRegularExpression()))
        return true;

    if (valueIndex.data().toString().contains(filterRegularExpression()))
        return true;

    const int childCount = sourceModel()->rowCount(keyIndex);
    for (int i = 0; i < childCount; ++i) {
        if (filterAcceptsRow(i, keyIndex))
            return true;
    }

    return false;
}
