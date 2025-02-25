#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>

using namespace std;
struct Book;
void parseLine();
void loadBooks();
void displayRow();
void displayByName();

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

void loadBooks(vector<Book> &books) {
    ifstream fin("books.csv");
    string nextline;

    if (fin) {
        while (!fin.eof()) {
            getline(fin, nextline);
            Book newBook;
            parseLine(nextline, newBook);

            books.push_back(newBook);
        }
    }
    fin.close();
}

int findIndexByName(const vector<Book> &books, string searchName) {
    int index = -1;
    for (int i=0;i<books.size();i++) {
        Book book = books[i];
        //learned from: https://cppscripts.com/cpp-string-contains
        if (book.title.find(searchName) != string::npos) {
            index = i;
        }
    }

    return index;
}



void displayRow(const Book &book) {
    //id is 8 chars after space
    cout << "| " << book.bookID << string(8 - to_string(book.bookID).size() , ' ');

    //title is 40 chars after space
    cout << "| " << book.title << string(40 - book.title.size(), ' ');

    //author
    cout << "| " << book.author << string(26 - book.author.size(), ' ');

    //year
    cout << "| " << book.release_year << string(10, ' ');

    //rating
    //adapted from https://www.geeksforgeeks.org/rounding-floating-point-number-two-decimal-places-c-c/
    int ratingTemp = (int) book.rating * 100;
    int ratingStringLen = to_string((float) ratingTemp / 100).size();

    cout << "| " << book.rating << string(4, ' ');

    //copies sold
    cout << "| " << book.copies_sold << string(7, ' ') << "|" << endl;


}

void displayTable(const vector<Book> &books) {
    /*
    float num = 9.7;
    float ratingTemp = num * 100;
    int ratingStringLen = to_string((float) ratingTemp / 100).size();
    cout << ratingStringLen << endl;
    */


    //HEADERS
    //give headers lengths to match max expected data
    //total table width is 122 chars
    cout << string(119, '-') << endl;
    cout << "| Book ID | " << "Title" << string(35, ' ') << "| Author" << string(20, ' ') << "| Year Released | Rating | Copies Sold" << endl;
    cout << string(119, '-') << endl;

    //ROWS
    for (vector<Book>::const_iterator iter = books.cbegin() ; iter != books.cend() ; iter++) {
        displayRow(*iter);
    }


    //FINAL ROW LINE
    cout << string(119, '-') << endl;
}

void displayTable(const Book &book) {
    //HEADERS
    cout << string(119, '-') << endl;
    cout << "| Book ID | " << "Title" << string(35, ' ') << "| Author" << string(20, ' ') << "| Year Released | Rating | Copies Sold" << endl;
    cout << string(119, '-') << endl;

    displayRow(book);

    //FINAL ROW LINE
    cout << string(119, '-') << endl;


}




int main() {
    vector<Book> books;
    loadBooks(books);

    int indexOf = findIndexByName(books, "Thot");
    if (indexOf == -1) {
        cout << "Book not found" << endl;
    } else {
        cout << "Book found at index " << indexOf << endl;
        displayTable(books[indexOf]);
    }

    return 0;
}