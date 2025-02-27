#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>

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
    string genre;
    int release_year;
    float rating;
    float copies_sold;
};



void parseLine(const string &line, Book &newBook) {
    string temp;
    int bookID;
    string title;
    string author;
    string genre;
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

    //genre
    getline(ss, genre, ',');

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
    newBook.genre = genre;
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

    //genre
    cout << "| " << book.genre << string(20 - book.genre.size(), ' ');

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
    cout << "| Book ID | " << "Title" << string(35, ' ') << "| Author" << string(20, ' ') << "| Genre" << string(15, ' ') << "| Year Released | Rating | Copies Sold" << endl;
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
    cout << "| Book ID | " << "Title" << string(35, ' ') << "| Author" << string(20, ' ') << "| Genre" << string(15, ' ') << "| Year Released | Rating | Copies Sold" << endl;
    cout << string(119, '-') << endl;

    displayRow(book);

    //FINAL ROW LINE
    cout << string(119, '-') << endl;
}


void countBooksByGenre(const vector<Book> &books) {
    //find all genres
    const vector<string> genres = {"Classic","Historical Fiction","Fantasy","Children's Fiction","Thriller","Mystery","Magical Realism","Romance","Gothic Fiction","Adventure","Modernist Fiction","Dystopian","Existentialism","Psychological Fiction","Satire","War Fiction","Political Philosophy","Absurdist Fiction","Science Fiction","Contemporary Fiction","Poetry","Philosophical Fiction"};

    //table header
    cout << "| Genre" + string(30, ' ') << "| Number of books" << string(5, ' ') << "|";

    for (string genre: genres) {
        //count total
        int cnt = 0;
        for (vector<Book>::const_iterator iter = books.cbegin(); iter != books.cend(); iter++ ) {
            Book book = *iter;
            if (book.genre == genre) {
                cnt++;
            }
        }

        //display result:   -give 40 and 20 chars to columns respectively
        cout << "| " << genre << string(35 - genre.size(), ' ') << "| "  << cnt << string(20 - to_string(cnt).size(), ' ') << "|" << endl;
    }
}

void filterByGenre(const vector<Book> &books, const string &genre){
    vector<Book> filteredBooks;

    for (Book book: books){
        if (book.genre == genre){
            filteredBooks.push_back(book);
        }
    }

    displayTable(filteredBooks);
}

//part 5
int analyseReleaseYears(const vector<Book> &books){
    int newest = books[0].release_year;
    int newestIndex = 0;
    int oldest = books[0].release_year;
    int oldestIndex = 0;

    double sum = 0;
    double avg;

    for (int i=0;i<books.size();i++){
        //newest
        if (books[i].release_year > newest){
            newest = books[i].release_year;
            newestIndex = i;
        }

        if (books[i].release_year < oldest){
            oldest = books[i].release_year;
            oldestIndex = i;
        }

        sum += books[i].release_year;
    }

    avg = sum / books.size();
    cout << "avg" << avg << endl;
    cout << "*************************" << endl;
    cout << "*Oldest Book on Record: *" << endl;
    cout << "*************************" << endl;
    displayTable(books[oldestIndex]);

    cout << endl;
    cout << "*************************" << endl;
    cout << "*Newest Book on Record: *" << endl;
    cout << "*************************" << endl;
    displayTable(books[newestIndex]);



    return avg;
}

list<Book> searchBooksByTitle(const vector<Book> &books, const string &searchQuery) {
    list<Book> results;

    for (vector<Book>::const_iterator iter = books.begin() ; iter!=books.end();iter++) {
        Book book = *iter;
        if (book.title.find(searchQuery) != string::npos) {
            results.push_back(*iter);
        }
    }

    return results;

}

void displayRatingHighToLow(vector<Book> &books) {
    //lambda func structure taken from dermot logue's notes.
    sort(books.begin(), books.end(), [](Book book1, Book book2){return book1.rating > book2.rating;});
    cout << "Sorted Books (Rating: High to Low)" << endl;
    displayTable(books);
}





int main() {
    vector<Book> books;
    loadBooks(books);
    //displayTable(books);

    //countBooksByGenre(books);
    //filterByGenre(books, "Fantasy");
    //analyseReleaseYears(books);
    displayRatingHighToLow(books);
    /*
    int indexOf = findIndexByName(books, "Thot");
    if (indexOf == -1) {
        cout << "Book not found" << endl;
    } else {
        cout << "Book found at index " << indexOf << endl;
        displayTable(books[indexOf]);
    }
    */

    return 0;
}