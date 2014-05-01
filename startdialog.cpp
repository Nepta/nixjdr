#include "startdialog.h"

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

void StartDialog::resultExec() {
    if (exec() == QMessageBox::No) {
        // TODO
    } else {
        // TODO
    }
}
