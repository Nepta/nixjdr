#include "startdialog.h"
#include "mainwindow.h"

StartDialog::StartDialog(QWidget *parent) :
    QMessageBox(parent)
{
    setIcon(QMessageBox::Question);
    setWindowTitle("Choix rôle");
    setText("Comment voulez-vous utiliser l'application?");
    setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    setButtonText(QMessageBox::Yes, "MJ");
    setButtonText(QMessageBox::No, "Joueur");
}

bool StartDialog::resultExec() {
    if (exec() == QMessageBox::No) {
        return MainWindow::ROLE_PLAYER;
    } else {
        return MainWindow::ROLE_MJ;
    }
}
