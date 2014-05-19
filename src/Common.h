#ifndef COMMON_H
#define COMMON_H

#include <QString>

/**
 * @brief The Common class holds general processing functions which could be applied anywhere in
 * the application.
 */
class Common
{
public:
    Common(){}

    /**
     * @brief extractFirstWord Finds the first word in a message, strips it from the message and
     * returns the stripped word
     * @param msg from which the first word should be extracted
     * @return First word of the message (msg).
     */
    static QString extractFirstWord(QString &msg);
};

#endif // COMMON_H
