#include <iostream>
#include <string>
#include <fstream>
#include <sstream>

using namespace std;
void parseLine();
void readFile();

struct Book
{
    int bookID;
    string title;
    string author;
    int release_year;
    float rating;
    float copies_sold;
};

void parseLine(const string &line, Book &newBook) {
    string temp;
    int bookID;
    string title;
    string author;
    int release_year;
    float rating;
    float copies_sold;

    stringstream ss(line);
    //id
    getline(ss, temp, ',');
    bookID = stoi(temp);

    //title
    getline(ss, title, ',');

    //author
    getline(ss, author, ',');

    //release year
    getline(ss, temp, ',');
    release_year = stoi(temp);

    //rating
    getline(ss, temp, ',');
    rating = stof(temp);

    //copies sold
    getline(ss, temp, ',');
    copies_sold = stof(temp);


    //fill struct
    newBook.bookID = bookID;
    newBook.title = title;
    newBook.author = author;
    newBook.release_year = release_year;
    newBook.rating = rating;
    newBook.copies_sold = copies_sold;
}

void readFile() {
    ifstream fin("books.csv");
    string nextline;

    if (fin) {
        while (!fin.eof()) {
            getline(fin, nextline);
            Book newBook;
            parseLine(nextline, newBook);
        }
    }
    fin.close();
}



int main() {
    readFile();
    return 0;
}