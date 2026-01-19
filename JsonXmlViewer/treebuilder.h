#ifndef TREEBUILDER_H
#define TREEBUILDER_H

#include <QStandardItem>

class TreeBuilder
{
protected:
    static QStandardItem* createItem(const QString& text);
};


#endif // TREEBUILDER_H
