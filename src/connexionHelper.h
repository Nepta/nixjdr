#ifndef CONNEXIONHELPER_H
#define CONNEXIONHELPER_H

#include <QDialog>

namespace Ui {
	class ConnexionHelper;
}

class ConnexionHelper : public QDialog
{
	Q_OBJECT

public:
	explicit ConnexionHelper(QWidget *parent = 0);
	~ConnexionHelper();

public slots:
	void on_pushButton_clicked();

signals:
	void ipAddrSent(QString ipAddr);

private:
	Ui::ConnexionHelper *ui;
};

#endif // CONNEXIONHELPER_H
