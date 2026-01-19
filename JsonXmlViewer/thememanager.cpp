#include "thememanager.h"

QString ThemeManager::styleSheet(Theme theme)
{
    if (theme == Theme::Dark) {
        return R"(
        QMainWindow {
            background-color: #121212;
        }

        QTreeView {
            background-color: #1e1e1e;
            alternate-background-color: #252526;
            color: #e0e0e0;
            selection-background-color: #3d5afe;
            selection-color: #ffffff;
            border: 1px solid #333;
        }

        QHeaderView::section {
            background-color: #2d2d2d;
            color: #cccccc;
            padding: 4px;
            border: 1px solid #3a3a3a;
        }

        QLineEdit {
            background-color: #2b2b2b;
            color: #ffffff;
            border: 1px solid #444;
            padding: 4px;
            border-radius: 4px;
        }

        QMenuBar, QMenu, QToolBar {
            background-color: #1f1f1f;
            color: #dddddd;
        }

        QMenu::item:selected {
            background-color: #3949ab;
        }
        )";
    }

    // ---------- LIGHT THEME ----------
    return R"(
    QMainWindow {
        background-color: #f5f5f5;
    }

    QTreeView {
        background-color: #ffffff;
        alternate-background-color: #f0f0f0;
        color: #202020;
        selection-background-color: #bbdefb;
        selection-color: #000000;
        border: 1px solid #ccc;
    }

    QHeaderView::section {
        background-color: #eaeaea;
        color: #202020;
        padding: 4px;
        border: 1px solid #cccccc;
    }

    QLineEdit {
        background-color: #ffffff;
        color: #000000;
        border: 1px solid #bbbbbb;
        padding: 4px;
        border-radius: 4px;
    }

    QMenuBar, QMenu, QToolBar {
        background-color: #ededed;
        color: #000000;
    }

    QMenu::item:selected {
        background-color: #c5cae9;
    }
    )";
}
