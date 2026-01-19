#ifndef JSONTREEBUILDER_H
#define JSONTREEBUILDER_H


#include "treebuilder.h"
#include <QStandardItemModel>
#include <QJsonValue>

class JsonTreeBuilder : public TreeBuilder
{
public:
    static constexpr int COLLAPSE_LIMIT = 20;

    static void build(QStandardItemModel* model,
                      const QByteArray& data);

private:
    static void parseValue(const QString& key,
                           const QJsonValue& value,
                           QStandardItem* parent);
};


#endif // JSONTREEBUILDER_H
