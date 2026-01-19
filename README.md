## JSON / XML Viewer (Qt C++)

Приложение на Qt Widgets (C++) для просмотра и анализа файлов JSON и XML в виде древовидной структуры.

### Вид

![]()


### Основные возможности:

* Загрузка JSON и XML файлов (через меню или Drag & Drop)
* Древовидная визуализация данных (QTreeView)
* Подсветка типов JSON (string, number, bool, null)
* Масштабируемый поиск по ключам и значениям
* Сворачивание больших JSON-массивов
* XML подсветка с учётом XSD-схемы (если доступна)
* Белая и тёмная тема (QSS, переключение на лету)


### Технологии:

* Qt 5.15+
* Qt Widgets
* QJson / QDom (XML)
* QSortFilterProxyModel
* QSS (встроенные темы)


### Структура:

```
JsonXmlViewer/
│
├── JsonXmlViewer.pro
│
├── main.cpp
│
├── MainWindow.h
├── MainWindow.cpp
│
├── ThemeManager.h
├── ThemeManager.cpp
│
├── SearchProxyModel.h
├── SearchProxyModel.cpp
│
├── TreeBuilder.h
├── TreeBuilder.cpp
│
├── JsonTreeBuilder.h
├── JsonTreeBuilder.cpp
│
├── XmlTreeBuilder.h
├── XmlTreeBuilder.cpp
```

### Назначение файлов:

main.cpp
Точка входа, инициализация QApplication.

MainWindow.*
Главное окно: UI, меню, поиск, drag & drop, переключение тем.

ThemeManager.*
Встроенные QSS темы (Light / Dark).

SearchProxyModel.*
Масштабируемый поиск по дереву (QSortFilterProxyModel).

TreeBuilder.*
Общие вспомогательные методы для построения дерева.

JsonTreeBuilder.*
Парсинг и визуализация JSON, подсветка типов, сворачивание массивов.

XmlTreeBuilder.*
Парсинг XML и schema-aware подсветка на основе XSD.

JsonXmlViewer.pro
qmake-конфигурация проекта.

