#include "xmltreebuilder.h"

#include <QDomDocument>
#include <QFile>

static void loadSchema(const QString& path,
                       QSet<QString>& elements,
                       QSet<QString>& attributes)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly))
        return;

    QDomDocument doc;
    if (!doc.setContent(&file))
        return;

    auto nodes = doc.elementsByTagName("xs:element");
    for (int i = 0; i < nodes.count(); ++i)
        elements.insert(nodes.at(i).attributes().namedItem("name").nodeValue());

    nodes = doc.elementsByTagName("xs:attribute");
    for (int i = 0; i < nodes.count(); ++i)
        attributes.insert(nodes.at(i).attributes().namedItem("name").nodeValue());
}

void XmlTreeBuilder::build(QStandardItemModel* model,
                           const QByteArray& data,
                           const QString& xmlPath)
{
    QDomDocument doc;
    if (!doc.setContent(data))
        return;

    QSet<QString> elements, attributes;
    loadSchema(xmlPath + ".xsd", elements, attributes);

    parseNode(doc.documentElement(),
              model->invisibleRootItem(),
              elements,
              attributes);
}

void XmlTreeBuilder::parseNode(const QDomNode& node,
                               QStandardItem* parent,
                               const QSet<QString>& knownElements,
                               const QSet<QString>& knownAttributes)
{
    auto* keyItem = createItem(node.nodeName());
    auto* valItem = createItem("");

    if (!knownElements.isEmpty() && !knownElements.contains(node.nodeName()))
        keyItem->setForeground(Qt::red);

    parent->appendRow({keyItem, valItem});

    auto attrs = node.attributes();
    for (int i = 0; i < attrs.count(); ++i) {
        auto a = attrs.item(i);
        auto* k = createItem("@" + a.nodeName());
        auto* v = createItem(a.nodeValue());

        if (!knownAttributes.isEmpty() &&
            !knownAttributes.contains(a.nodeName()))
            k->setForeground(Qt::darkRed);

        keyItem->appendRow({k, v});
    }

    QDomNode child = node.firstChild();
    while (!child.isNull()) {
        if (child.isElement())
            parseNode(child, keyItem, knownElements, knownAttributes);
        child = child.nextSibling();
    }
}
