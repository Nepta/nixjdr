#include "Tooltip.h"
#include "ui_Tooltip.h"
#include "Canvas/Sprite.h"

Tooltip::Tooltip(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::Tooltip)
{
    ui->setupUi(this);
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
 * @brief MapTooltip::showTooltip Displays the tooltip with the information stored in m_InfoStack
 * at the specified position.
 * @param position
 */
void Tooltip::showTooltip(QPoint position) {
    QString tip;

    while (!m_InfoStack.isEmpty()) {
        tip.append(m_InfoStack.pop());

        if (!m_InfoStack.isEmpty()) {
            tip.append("\n");
        }
    }
    setTooltipText(tip);

    move(position);
    show();
}

/**
 * @brief Tooltip::hideTooltip Clear the information stack before hiding the tooltip.
 */
void Tooltip::hideTooltip() {
    m_InfoStack.clear();
    hide();
}
