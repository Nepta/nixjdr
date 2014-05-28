#include "ConnectionHelper.h"
#include "ui_ConnectionHelper.h"
#include <QIntValidator>
#include <QRegExpValidator>

ConnectionHelper::ConnectionHelper(User *user, QWidget *parent) :
    QDialog(parent), ui(new Ui::ConnectionHelper)
{
	ui->setupUi(this);
    setWindowFlags(Qt::CustomizeWindowHint | Qt::WindowTitleHint | Qt::WindowMinMaxButtonsHint);

	QValidator *ipRange = new QIntValidator(0,255);
    ui->ipA->setValidator(ipRange);
    ui->ipB->setValidator(ipRange);
    ui->ipC->setValidator(ipRange);
    ui->ipD->setValidator(ipRange);

    // Only nicknames which do not contain whitespaces are valid
    QValidator *nicknameValidator = new QRegExpValidator(QRegExp("[\\S]+"));
    ui->nickname->setValidator(nicknameValidator);

    m_User = user;
}

ConnectionHelper::~ConnectionHelper(){
	delete ui;
}

void ConnectionHelper::on_playerButton_clicked() {
    m_User->setRole(Role::ROLE_PLAYER);

    // next page
    ui->stackedWidget->setCurrentWidget(ui->pageConnection);
}

void ConnectionHelper::on_mjButton_clicked() {
    m_User->setRole(Role::ROLE_MJ);

    // hide IpAddress row
    ui->ipAddress->hide();
    ui->ipAddressLabel->hide();

    // next page
    ui->stackedWidget->setCurrentWidget(ui->pageConnection);
}

void ConnectionHelper::on_endButton_clicked() {
    if (m_User->getRole() == Role::ROLE_PLAYER) {
        QString ipAddress = QString("%1.%2.%3.%4")
                .arg(ui->ipA->text())
                .arg(ui->ipB->text())
                .arg(ui->ipC->text())
                .arg(ui->ipD->text());

        m_User->setServerIpAddress(ipAddress);
    }
    else {
        m_User->setServerIpAddress("127.0.0.1");
    }

    m_User->setNickname(QString("guest"));
    m_User->setPendingNickname(ui->nickname->text());

    accept();
}

void ConnectionHelper::closeEvent(QCloseEvent * event) {
    event->ignore();
}

void ConnectionHelper::keyPressEvent(QKeyEvent *event){
    if(event->key() == Qt::Key_Escape){
        ui->stackedWidget->setCurrentWidget(ui->pageRole);
        ui->ipAddress->show();
        ui->ipAddressLabel->show();
    }
}
