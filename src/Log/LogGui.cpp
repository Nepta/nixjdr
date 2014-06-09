#include "LogGui.h"
#include "ui_LogGui.h"

LogGui::LogGui(QWidget *parent) :
	QWidget(parent),
	ui(new Ui::LogGui)
{
	ui->setupUi(this);
}

LogGui::~LogGui()
{
	delete ui;
}
