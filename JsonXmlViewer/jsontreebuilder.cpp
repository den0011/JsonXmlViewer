#include "jsontreebuilder.h"

#include <QJsonDocument>
#include <QJsonObject>
#include <QJsonArray>
#include <QColor>

static void applyColor(QStandardItem* item, const QJsonValue& value)
{
    QColor c;
    switch (value.type()) {
    case QJsonValue::String: c = "#2e7d32"; break;
    case QJsonValue::Double: c = "#1565c0"; break;
    case QJsonValue::Bool:   c = "#6a1b9a"; break;
    case QJsonValue::Null:   c = "#9e9e9e"; break;
    default: return;
    }
    item->setForeground(c);
}

void JsonTreeBuilder::build(QStandardItemModel* model,
                            const QByteArray& data)
{
    auto doc = QJsonDocument::fromJson(data);
    if (!doc.isObject())
        return;

    for (auto it = doc.object().begin(); it != doc.object().end(); ++it)
        parseValue(it.key(), it.value(), model->invisibleRootItem());
}

void JsonTreeBuilder::parseValue(const QString& key,
                                 const QJsonValue& value,
                                 QStandardItem* parent)
{
    auto* keyItem = createItem(key);
    auto* valItem = createItem("");

    parent->appendRow({keyItem, valItem});

    if (value.isArray()) {
        auto arr = value.toArray();

        if (arr.size() > COLLAPSE_LIMIT) {
            keyItem->setText(
                QString("%1 [%2 items] (collapsed)")
                .arg(key)
                .arg(arr.size()));
        }

        int i = 0;
        for (const auto& v : arr) {
            parseValue(QString("[%1]").arg(i++), v, keyItem);
        }
    }
    else if (value.isObject()) {
        for (auto it = value.toObject().begin(); it != value.toObject().end(); ++it)
            parseValue(it.key(), it.value(), keyItem);
    }
    else {
        valItem->setText(value.toVariant().toString());
        applyColor(valItem, value);
    }
}
