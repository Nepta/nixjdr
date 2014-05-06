#ifndef STARTDIALOG_H
#define STARTDIALOG_H

#include <QMessageBox>

class StartDialog : public QMessageBox
{
    Q_OBJECT
public:
    explicit StartDialog(QWidget *parent = 0);
    bool resultExec();

signals:

public slots:

};

#endif // STARTDIALOG_H
