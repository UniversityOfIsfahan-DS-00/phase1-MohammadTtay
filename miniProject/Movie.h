#ifndef MOVIE_H
#define MOVIE_H

#endif // MOVIE_H
#include<iostream>

#include<QString>

#include<QStringList>

#include<QDebug>

using namespace std;
class Movie {
public:
    QString titleID;
    int ordering;
    QString title;
    QString region;
    QString language;
    QString types;
    QString attributes;
    int isOriginalTitle;
    double averageRating;
    int numVotes;

    Movie(QString titleID, int ordering, QString title, QString region, QString language, QString types, QString attributes, int isOriginalTitle, double averageRating, int numVotes) {
        this->titleID=titleID;
        this->ordering=ordering;
        this->title=title;
        this->region=region;
        this->language=language;
        this->types=types;
        this->attributes=attributes;
        this->isOriginalTitle=isOriginalTitle;
        this->averageRating=averageRating;
        this->numVotes=numVotes;

    }
    Movie() {}

    void addInfo(QStringList data) {

        this -> titleID = data[0];
        this -> ordering = data[1].toInt();
        this -> title = data[2];
        this -> region = data[3];
        this -> language = data[4];
        this -> types = data[5];
        this -> attributes = data[6];
        this -> isOriginalTitle = data[7].toInt();
        this -> averageRating = data[8].toDouble();
        this -> numVotes = data[9].toInt();

    }

    void print() {

        cout << "||\tTitleID : " << this -> titleID.toStdString() << endl;
        cout << "||\t||ordering : " << this -> ordering << endl;
        cout << "||\ttitle : " << this -> title.toStdString() << endl;
        cout << "||\tregion : " << this -> region.toStdString() << endl;
        cout << "||\tlanguage : " << this -> language.toStdString() << endl;
        cout << "||\ttypes : " << this -> types.toStdString() << endl;
        cout << "||\tattributes : " << this -> attributes.toStdString() << endl;
        cout << "||\tisOriginalTitle : " << this -> isOriginalTitle << endl;
        cout << "||\taverageRating : " << this -> averageRating << endl;
        cout << "||\tnumVotes : " << this -> numVotes << endl;
        cout << "=============================================================\n";

    }
};
