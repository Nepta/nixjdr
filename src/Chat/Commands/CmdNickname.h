#ifndef CmdNickname_H
#define CmdNickname_H

#include "AbstractCmd.h"

class CmdNickname : public AbstractCmd
{
    Q_OBJECT

public:
    CmdNickname();

    void execute(Header &header, QString &arg);
    void executeOnUser(User *newUser, QString currentNickname, QString oldNickname, bool isNew);
    QString getHelp();

    /**
     * @brief sendConnectionMessage Send a message to all users to notify them that a new user has
     * joined the chat.
     * @param nickname New user nickname.
     */
    void sendConnectionMessage(QString nickname);

    /**
     * @brief checkDuplicateNickname Check if the given nickname is already taken and appends "_" at
     * the end if it is the case.
     * @param nickname Nickname to verify.
     * @return Checked nickname (nickname + "_" if it already exists in the users list)
     */
    QString checkDuplicateNickname(QString nickname);

    /**
     * @brief checkValidNickname Verifies if the nickname contains whitespaces or is empty, if
     * that's the case send an an error message to the user.
     * @param oldNickname User's old nickname.
     * @param nickname User's asked nickname which will be verified.
     * @return true if the nickname is valid, false otherwise.
     */
    bool checkValidNickname(QString oldNickname, QString nickname);

    /**
     * @brief updateClientsUsersList Update the user's list on all clients (isOwner = false) or on the
     * owner client (isOwner = true).
     * @param oldNickname User's old nickname.
     * @param checkedNickname User's new nickname.
     * @param isOwner
     * @param isNew
     */
    void updateClientsUsersList(QString oldNickname, QString checkedNickname, bool isOwner, bool isNew);

signals:
    /**
     * @brief addPlayerToInterface signals that a new player, whose nickname does not start by "guest",
     * is to be added to the interface (e.g. in turnMenu & tokenMenu)
     */
    void addPlayerToInterface(QString);
};

#endif // CmdNickname_H
