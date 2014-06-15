#ifndef STYLESHEET_H
#define STYLESHEET_H

#include <QString>

class StyleSheet
{
public:
    static QString s_StyleSheet;

    static void setStyleSheet(QString styleSheet);
};

#endif // STYLESHEET_H
