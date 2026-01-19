#ifndef XMLTREEBUILDER_H
#define XMLTREEBUILDER_H


#include "treebuilder.h"
#include <QStandardItemModel>
#include <QDomNode>
#include <QSet>

class XmlTreeBuilder : public TreeBuilder
{
public:
    static void build(QStandardItemModel* model,
                      const QByteArray& data,
                      const QString& xmlPath);

private:
    static void parseNode(const QDomNode& node,
                          QStandardItem* parent,
                          const QSet<QString>& knownElements,
                          const QSet<QString>& knownAttributes);
};


#endif // XMLTREEBUILDER_H
