#include "StyleSheet.h"

QString StyleSheet::s_StyleSheet;

void StyleSheet::setStyleSheet(QString styleSheet) {
    s_StyleSheet = styleSheet;
}
