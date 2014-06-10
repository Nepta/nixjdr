#include "LogGui.h"
#include "ui_LogGui.h"

LogGui::LogGui(QWidget *parent) : QWidget(parent), ui(new Ui::LogGui){
	ui->setupUi(this);
}

LogGui::~LogGui(){
	delete ui;
}

void LogGui::pushLog(QString log){
	ui->listWidget_->insertItem(0,log);
}

QString LogGui::popLog(){
	QString lastItem = ui->listWidget_->takeItem(0)->text();
	return lastItem;
}
