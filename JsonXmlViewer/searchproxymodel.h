#ifndef SEARCHPROXYMODEL_H
#define SEARCHPROXYMODEL_H

#include <QSortFilterProxyModel>

class SearchProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT
public:
    explicit SearchProxyModel(QObject* parent = nullptr);

protected:
    bool filterAcceptsRow(int sourceRow,
                          const QModelIndex& sourceParent) const override;
};


#endif // SEARCHPROXYMODEL_H
