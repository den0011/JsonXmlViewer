#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QTreeView>
#include <QStandardItemModel>
#include <QLineEdit>

#include "searchproxymodel.h"
#include "thememanager.h"

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget* parent = nullptr);

protected:
    void dragEnterEvent(QDragEnterEvent* event) override;
    void dropEvent(QDropEvent* event) override;

private:
    void setupUi();
    void loadFile(const QString& path);
    void applyTheme(ThemeManager::Theme theme);

    QTreeView* treeView;
    QStandardItemModel* model;
    SearchProxyModel* proxy;
    QLineEdit* searchEdit;

    ThemeManager::Theme currentTheme;
};



#endif // MAINWINDOW_H
