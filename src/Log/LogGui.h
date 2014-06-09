#ifndef LOGGUI_H
#define LOGGUI_H

#include <QWidget>

namespace Ui {
	class LogGui;
}

class LogGui : public QWidget
{
	Q_OBJECT

public:
	explicit LogGui(QWidget *parent = 0);
	~LogGui();

private:
	Ui::LogGui *ui;
};

#endif // LOGGUI_H
