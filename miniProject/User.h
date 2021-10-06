#ifndef USER_H
#define USER_H

#endif // USER_H

#include<QString>

#include<QStringList>

#include<QDebug>

class User {
public:
    QString username, password;
    QSet < QString > ratedFilms;
};
