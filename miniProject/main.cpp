#include<iostream>

#include<conio.h>

#include<QFile>

#include<QTextStream>

#include<Movie.h>

using namespace std;

int readFiles();

vector < Movie > movies;

int main() {
    if (!readFiles()) { //Read The Information From "title.akas.txt" And "title.rating.txt" When Program Starts
        return 0;
    }

    for(auto x : movies) x.print();//---Test-->Printing Movies When The Program Runs
}

int readFiles() {

    QFile file("../title.akas.txt");
    QTextStream in ( & file);
    QTextStream out( & file);

    QFile file2("../title.ratings.txt");
    QTextStream in2( & file2);
    QTextStream out2( & file2);

    if (!file.exists() || !file2.exists()) {

        cout << "\n\n\nPlease Add "
                "title.ratings.txt"
                " & "
                "title.akas.txt"
                " Into The Build Directory:(\n\n\n";
        return 0;
    } else {
        file.open(QFile::ReadWrite | QFile::Text);
        file2.open(QFile::ReadWrite | QFile::Text);

        in .readLine();
        in2.readLine();

        Movie * tempMovie;
        QString tempString;
        QStringList tempSList, tempSList2;

        while (true) {
            tempMovie = new Movie;
            tempString = in .readLine();
            if (tempString.isNull()) break;
            tempSList = tempString.split("\t");

            tempString = in2.readLine();
            tempSList2 = tempString.split("\t");
            tempSList.push_back(tempSList2[1]);
            tempSList.push_back(tempSList2[2]);
            tempMovie -> addInfo(tempSList);
            movies.push_back( * tempMovie);
        }
        file.close();
        file2.close();

    }

    return 1;

}
