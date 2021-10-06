#include<iostream>

#include<conio.h>

#include<QFile>

#include<QTextStream>

#include<Movie.h>

#include<User.h>

using namespace std;

int readFiles();
void slPage();
void votingPage(string);
void updateFile();
void topTen();

vector < Movie > movies;
vector < User > users;

bool comp(Movie first, Movie second)
{
    return (first.averageRating > second.averageRating);
}

int main() {
    if (!readFiles()) { //Read The Information From "title.akas.txt" And "title.rating.txt" When Program Starts
        return 0;
    }

    while (true) {
        system("cls");
        int firstPage;

        cout << ":::[ IMDB Rating ]:::\n\n" <<
            "<1> Login/Signup\n" <<
            "<2> Top Ten\n" <<
            "<3> Exit\n\n" <<
            "Please Enter A Number: ";
        cin >> firstPage;

        switch (firstPage) {
        case 1:
            slPage();
            break;
        case 2:
            topTen();
            break;
        case 3:
            exit(0);
            break;
        default:
            cout << "Please Enter A Valid Number";
            cout << "\n\nPress Any Key to Continue...";
            getch();
            system("cls");
            continue;
        }

    }
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

void slPage() {/////////////////////////////Signup And Login Page
    system("cls");
    string username,
        password;
    bool flag;
    User * tempUser = new User;
    cout << ":::[ IMDB Rating ]:::\n\n";
    cout << "\nEnter Your Username: ";
    cin >> username;
    flag = false;

    for (auto x: users) {
        if (x.username == username.c_str()) {
            flag = true;
            cout << "\nEnter Your Password: ";
            cin >> password;
            if (x.password == password.c_str()) {
                cout << "\n---------------------You Have Successfully Logged In---------------------";
                cout << "\n\nPress Any Key to Continue...";
                getch();
                votingPage(username);
            } else {
                cout << "---------------------Password Is Incorrect . Please Try Again---------------------\n";
                cout << "\n\nPress Any Key to Continue...";
                getch();
                slPage();
            }
        }
    }
    if (flag == false) { //User Doesn't Exists
        tempUser = new User;
        cout << "\nEnter Your Password: ";
        cin >> password;

        tempUser -> username = username.c_str();
        tempUser -> password = password.c_str();

        users.push_back( * tempUser);

        cout << "\n---------------------You Have Successfully Signed Up---------------------";
        cout << "\n\nPress Any Key to Continue...";
        getch();
        votingPage(username);
    }
}

void votingPage(string username) {/////////////////////////////Voting Page
    system("cls");
    cout << "::[ IMDB Rating ]::\t\t\t\t\t\t\t\t\tWelcome " << username << "\n\n";
    cout << "=============================================================\n";
    for (auto x: movies) {
        x.print();
    }

    string titleID;
    int vote;
    bool titleFound = false;
    bool userVoted = false;
    cout << "\n\n\nPlease Enter The Title Id Of The Movie That You Want To Vote :";
    cin >> titleID;

    for (auto & x: movies) {

        if (titleID.c_str() == x.titleID) titleFound = true;
    }

    for (auto y: users) {
        if (y.username == username.c_str()) {

            if (y.ratedFilms.contains(titleID.c_str())) userVoted = true;
        }

        if (titleFound == false) { //////////////////////////////////////////////////If The Title ID Was Valid...
            cout << "\n---------------------Please Enter A Valid Title ID---------------------";
            cout << "\n\nPress Any Key to Continue...";
            getch();
            votingPage(username);
        }

        if (titleFound == true && userVoted == true) { //////////////////////////////The User Have Voted This Movie Before
            cout << "\n\n\n---------------------You Have Rated This Movie Before . Please Rate Another Movie---------------------";
            cout << "\n\n\n\nPress Any Key to Continue...";
            getch();
            votingPage(username);

        }

        if (titleFound == true && userVoted == false) { //////////////////////////////Everything Is Ready For Rate A Movie :)

            do {
                cout << "\nPlease Rate this movie (between 0 to 10):";
                cin >> vote;
                if (vote < 0 || vote > 10) cout << "...Unvalid...\n";
            } while (vote < 0 || vote > 10);

            for (auto y: users) {
                if (y.username == username.c_str()) y.ratedFilms.insert(titleID.c_str());
            }

            for (auto & x: movies) {

                if (titleID.c_str() == x.titleID) {

                    x.averageRating = (vote + (x.numVotes * x.averageRating)) / (x.numVotes + 1);
                    x.numVotes++;

                    for (auto & y: users) { ////////////////////////////////////Add The Movie In The User Rated Films List
                        if (username.c_str() == y.username) {
                            y.ratedFilms.insert(x.titleID);
                        }
                    }
                    updateFile();//Update "title.ratings.txt" File After Voting

                    cout << "\n\n---------------------Thank You For Voting :)---------------------\n\n\n\n";
                    cout << "Do You Want To Rate Another Movie? ('Y' Or 'N')\n";
                    char temp;
                    do {
                        temp = getch();
                    } while (temp != 'y' && temp != 'Y' && temp != 'n' && temp != 'N');
                    if (temp == 'Y' || temp == 'y') {
                        votingPage(username);
                    } else {
                        return;
                    }
                }
            }

        }
    }
}

void updateFile() {

    QFile file("../title.ratings.txt");
    QTextStream out( & file);
    file.open(QIODevice::WriteOnly | QIODevice::Text);
    out << "tconst\taverageRating\tnumVotes\n";
    for (auto x: movies) {
        out << x.titleID << "\t" << x.averageRating << "\t" << x.numVotes << "\n";
    }
    file.close();

}

void topTen() {

    system("cls");
    cout << "::[ IMDB Rating ]::\n\n";
    cout << "+Top 10 as rated by IMDb Users+\n\n";

    cout << "=============================================================\n";
    vector < Movie > sortedMovies;
    sortedMovies=movies;
    sort(sortedMovies.begin(),sortedMovies.end(),comp);
    int count=0;
    for(auto x : sortedMovies){
        count++;
        if(count>10) break;
        x.print();
    }
    cout << "\n\n\n\nPress Any Key to Go Back...";
    getch();
    return;

}
