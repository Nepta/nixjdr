#include "TokenMenu.h"
#include "ui_TokenMenu.h"

TokenMenu::TokenMenu(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::TokenMenu)
{
    ui->setupUi(this);
    m_tokenList = new TokenList();
    ui->verticalLayout->addWidget(m_tokenList);
}

TokenMenu::~TokenMenu()
{
    delete m_tokenList;
    delete ui;
}

Ui::TokenMenu *TokenMenu::getUi() {
    return ui;
}

TokenList *TokenMenu::getTokenList(){
    return m_tokenList;
}
