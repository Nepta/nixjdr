#include "connexionHelper.h"
#include "ui_connexionHelper.h"

ConnexionHelper::ConnexionHelper(QWidget *parent) : QDialog(parent),	ui(new Ui::ConnexionHelper){
	ui->setupUi(this);
}

ConnexionHelper::~ConnexionHelper(){
	delete ui;
}

void ConnexionHelper::on_pushButton_pressed(){
}
