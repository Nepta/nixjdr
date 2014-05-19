#ifndef CmdNickname_H
#define CmdNickname_H

#include "AbstractCmd.h"

class CmdNickname : public AbstractCmd
{
public:
    CmdNickname();

    void execute(Header &header, QString &arg);
    void executeOnUser(User *newUser, QString currentNickname, QString oldNickname, bool isNew);
    QString getHelp();
    QString verifyAndGetNickname(QString nickname);
};

#endif // CmdNickname_H
