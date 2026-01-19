#include "treebuilder.h"

QStandardItem* TreeBuilder::createItem(const QString& text)
{
    auto* item = new QStandardItem(text);
    item->setEditable(false);
    return item;
}
