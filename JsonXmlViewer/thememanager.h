#ifndef THEMEMANAGER_H
#define THEMEMANAGER_H


#include <QString>

class ThemeManager
{
public:
    enum class Theme {
        Light,
        Dark
    };

    static QString styleSheet(Theme theme);
};


#endif // THEMEMANAGER_H
