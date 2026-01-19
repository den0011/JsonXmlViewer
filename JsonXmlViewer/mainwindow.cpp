#include "mainwindow.h"
#include "jsontreebuilder.h"
#include "xmltreebuilder.h"

#include <QMenuBar>
#include <QFileDialog>
#include <QFile>
#include <QMessageBox>
#include <QToolBar>
#include <QMimeData>
#include <QApplication>
#include <QDragEnterEvent>

MainWindow::MainWindow(QWidget* parent)
    : QMainWindow(parent),
      treeView(new QTreeView(this)),
      model(new QStandardItemModel(this)),
      proxy(new SearchProxyModel(this)),
      currentTheme(ThemeManager::Theme::Light)
{
    setupUi();
    setAcceptDrops(true);
    applyTheme(currentTheme);
}

void MainWindow::setupUi()
{
    setWindowTitle("JSON / XML Viewer");
    resize(1000, 650);

    model->setHorizontalHeaderLabels({"Key", "Value"});
    proxy->setSourceModel(model);

    treeView->setModel(proxy);
    treeView->setAlternatingRowColors(true);
    treeView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    setCentralWidget(treeView);

    // ---------- MENU ----------
    auto* fileMenu = menuBar()->addMenu("File");
    fileMenu->addAction("Open...", this, [this]() {
        const QString path = QFileDialog::getOpenFileName(
            this, "Open", {}, "JSON (*.json);;XML (*.xml)");
        if (!path.isEmpty())
            loadFile(path);
    });
    fileMenu->addSeparator();
    fileMenu->addAction("Exit", this, &QWidget::close);

    auto* viewMenu = menuBar()->addMenu("View");
    auto* lightTheme = viewMenu->addAction("Light Theme");
    auto* darkTheme  = viewMenu->addAction("Dark Theme");

    connect(lightTheme, &QAction::triggered, this, [this]() {
        applyTheme(ThemeManager::Theme::Light);
    });
    connect(darkTheme, &QAction::triggered, this, [this]() {
        applyTheme(ThemeManager::Theme::Dark);
    });

    // ---------- TOOLBAR ----------
    auto* toolbar = addToolBar("Search");
    searchEdit = new QLineEdit(this);
    searchEdit->setPlaceholderText("Search...");
    toolbar->addWidget(searchEdit);

    connect(searchEdit, &QLineEdit::textChanged,
            proxy, &SearchProxyModel::setFilterFixedString);
}

void MainWindow::applyTheme(ThemeManager::Theme theme)
{
    currentTheme = theme;
    qApp->setStyleSheet(ThemeManager::styleSheet(theme));
}

void MainWindow::loadFile(const QString& path)
{
    QFile file(path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(this, "Error", "Cannot open file");
        return;
    }

    QByteArray data = file.readAll();
    file.close();

    model->clear();
    model->setHorizontalHeaderLabels({"Key", "Value"});

    if (path.endsWith(".json", Qt::CaseInsensitive))
        JsonTreeBuilder::build(model, data);
    else if (path.endsWith(".xml", Qt::CaseInsensitive))
        XmlTreeBuilder::build(model, data, path);

    treeView->expandAll();
}

void MainWindow::dragEnterEvent(QDragEnterEvent* event)
{
    if (event->mimeData()->hasUrls())
        event->acceptProposedAction();
}

void MainWindow::dropEvent(QDropEvent* event)
{
    const auto urls = event->mimeData()->urls();
    if (!urls.isEmpty())
        loadFile(urls.first().toLocalFile());
}
