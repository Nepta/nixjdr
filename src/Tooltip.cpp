#include "Tooltip.h"
#include "ui_Tooltip.h"
#include "StyleSheet.h"
#include "Canvas/Sprite.h"

Tooltip::Tooltip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tooltip)
{
    ui->setupUi(this);
    setStyleSheet(StyleSheet::s_StyleSheet);
}

Tooltip::~Tooltip()
{
    delete ui;
}

/**
 * @brief pushInfo Push an info into m_InfoStack.
 * @param info
 */
void Tooltip::pushInfo(QString info) {
    m_InfoStack.push(info);
}

/**
 * @brief Tooltip::setTooltipText Sets the text and adjust the size of the tooltip accordingly.
 * @param text
 */
void Tooltip::setTooltipText(QString text) {
    ui->m_TooltipText->setText(text);
    adjustSize();
}

/**
 * @brief MapTooltip::showTooltip Overloaded from QWidget. Displays the tooltip with the information
 * stored in m_InfoStack at the specified position.
 * @param position
 */
void Tooltip::show(QPoint position) {
    QString tip;

    while (!m_InfoStack.isEmpty()) {
        tip.append(m_InfoStack.pop());

        if (!m_InfoStack.isEmpty()) {
            tip.append("\n");
        }
    }
    setTooltipText(tip);

    move(position);
    QWidget::show();
}

/**
 * @brief Tooltip::hideTooltip Reimplemented from QWidget.Clear the information stack before hiding
 * the tooltip.
 */
void Tooltip::hide() {
    m_InfoStack.clear();
    QWidget::hide();
}
