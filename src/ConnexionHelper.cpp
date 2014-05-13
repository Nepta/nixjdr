#include "ConnexionHelper.h"
#include "ui_connexionHelper.h"
#include <QIntValidator>
#include <QDebug>

ConnexionHelper::ConnexionHelper(QWidget *parent) : QDialog(parent),	ui(new Ui::ConnexionHelper){
	ui->setupUi(this);
	QValidator *ipRange = new QIntValidator(0,255);
	ui->ipA->setValidator(ipRange);
	ui->ipB->setValidator(ipRange);
	ui->ipC->setValidator(ipRange);
	ui->ipD->setValidator(ipRange);
}

ConnexionHelper::~ConnexionHelper(){
	delete ui;
}

void ConnexionHelper::on_pushButton_clicked(){
	emit ipAddrSent(QString(
							 ui->ipA->text() + "." +
							 ui->ipB->text() + "." +
							 ui->ipC->text() + "." +
							 ui->ipD->text()
						));
	close();
}
