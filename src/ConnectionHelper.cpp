#include "ConnectionHelper.h"
#include "ui_ConnectionHelper.h"
#include <QIntValidator>
#include <QDebug>

ConnectionHelper::ConnectionHelper(QWidget *parent) : QDialog(parent),	ui(new Ui::ConnectionHelper){
	ui->setupUi(this);
	QValidator *ipRange = new QIntValidator(0,255);
    ui->ipA->setValidator(ipRange);
    ui->ipB->setValidator(ipRange);
    ui->ipC->setValidator(ipRange);
    ui->ipD->setValidator(ipRange);
}

ConnectionHelper::~ConnectionHelper(){
	delete ui;
}

void ConnectionHelper::on_pushButton_clicked(){
	emit ipAddrSent(QString(
							 ui->ipA->text() + "." +
							 ui->ipB->text() + "." +
							 ui->ipC->text() + "." +
							 ui->ipD->text()
						));
	close();
}
