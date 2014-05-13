#ifndef CONNECTIONHELPER_H
#define CONNECTIONHELPER_H

#include <QDialog>

namespace Ui {
    class ConnectionHelper;
}

class ConnectionHelper : public QDialog
{
	Q_OBJECT

public:
    explicit ConnectionHelper(QWidget *parent = 0);
    ~ConnectionHelper();

public slots:
	void on_pushButton_clicked();

signals:
	void ipAddrSent(QString ipAddr);

private:
    Ui::ConnectionHelper *ui;
};

#endif // CONNECTIONHELPER_H
