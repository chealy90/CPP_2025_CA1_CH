#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <algorithm>
#include <iomanip>
#include <map>

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

// DATA DISPLAYING METHODS

void displayRow(const Book &book) {
    //id is 8 chars after space
    cout << "| " << book.bookID << setw(5- to_string(book.bookID).size());

    //title is 40 chars after space
    cout << "| " << book.title << setw(45 - book.title.size());

    //author
    cout << "| " << book.author << setw(26 - book.author.size());

    //genre
    if (book.genre.size() > 18) {
        cout << "| " << book.genre.substr(0, 18);
    } else {
        cout << "| " << book.genre << setw(20 - book.genre.size());

    }

    //year
    cout << "| " << book.release_year << setw(3);

    //rating
    //adapted from https://www.geeksforgeeks.org/rounding-floating-point-number-two-decimal-places-c-c/

    int ratingTemp = (int) book.rating * 100;
    //int ratingStringLen = to_string((float) ratingTemp / 100).size();

    cout << "| " << book.rating << setw(14 - to_string(book.rating).size());

    //copies sold
    cout << "| " << book.copies_sold << endl;


}

//overloaded methods to allow multiple data types to be displayed in table format
void displayTable(const vector<Book> &books) {

    //HEADERS
    //give headers lengths to match max expected data
    //total table width is 122 chars
    cout << string(119, '-') << endl;
    cout << "| ID | " << "Title" << setw(46) << "| Author" << setw(25) << "| Genre" << setw(35) << "| Year | Rating | Sold" << endl;
    cout << string(119, '-') << endl;

    //ROWS
    for (vector<Book>::const_iterator iter = books.cbegin() ; iter != books.cend() ; iter++) {
        displayRow(*iter);
    }


    //FINAL ROW LINE
    cout << string(119, '-') << endl;
}

void displayTable(const list<Book> &books) {
    //HEADERS
    //give headers lengths to match max expected data
    //total table width is 122 chars
    cout << string(119, '-') << endl;
    cout << "| ID | " << "Title" << setw(46) << "| Author" << setw(25) << "| Genre" << setw(35) << "| Year | Rating | Sold" << endl;
    cout << string(119, '-') << endl;

    //ROWS
    for (list<Book>::const_iterator iter = books.cbegin() ; iter != books.cend() ; iter++) {
        displayRow(*iter);
    }


    //FINAL ROW LINE
    cout << string(119, '-') << endl;
}

void displayTable(const Book &book) {
    //HEADERS
    cout << string(119, '-') << endl;
    cout << "| ID | " << "Title" << setw(46) << "| Author" << setw(25) << "| Genre" << setw(35) << "| Year | Rating | Sold" << endl;
    cout << string(119, '-') << endl;

    displayRow(book);

    //FINAL ROW LINE
    cout << string(119, '-') << endl;
}


map<string, int> countBooksByGenre(const vector<Book> &books) {
    //learned from https://cplusplus.com/reference/map/map/

    //find all genres
    const vector<string> genres = {"Classic","Historical Fiction","Fantasy","Children's Fiction","Thriller","Mystery","Magical Realism","Romance","Gothic Fiction","Adventure","Modernist Fiction","Dystopian","Existentialism","Psychological Fiction","Satire","War Fiction","Political Philosophy","Absurdist Fiction","Science Fiction","Contemporary Fiction","Poetry","Philosophical Fiction"};
    map<string, int> genreFreq;


    //table header
    for (string genre: genres) {
        //count total
        int cnt = 0;
        for (vector<Book>::const_iterator iter = books.cbegin(); iter != books.cend(); iter++ ) {
            Book book = *iter;
            if (book.genre == genre) {
                cnt++;
            }


        }
        genreFreq.insert(pair<string, int>(genre, cnt));
        //cout << genre << " " << cnt;
    }
    return genreFreq;


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



    return (int) avg; //casting avg to int as it avoids showing years as floating points.
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

void displayByRatingHighToLow(vector<Book> &books) {
    //lambda func structure taken from dermot logue's notes.
    sort(books.begin(), books.end(), [](Book book1, Book book2){return book1.rating > book2.rating;});
    cout << "Sorted Books (Rating: High to Low)" << endl;
    displayTable(books);
}




//MENU FUNCTIONS - FOR RUNNING AND DISPLAYING RESULTS OF MENU OPTIONS
void executeMenu(int &choice) {
    cin.clear();
    cout << "----MENU----" << endl;
    cout << "1) Display All Books. (Q1) " << endl;
    cout << "2) Find a book by name. (Q2)" << endl;
    cout << "3) Analyse occurance book genres. (Q3) " << endl;
    cout << "4) Filter books by genre. (Q4) " << endl;
    cout << "5) Find newest, oldest and average release year of books. (Q5)" << endl;
    cout << "6) Search for titles containing... (Q6)" << endl;
    cout << "7) Sort Books (highest to lowest rating) (Q7)" << endl;
    cout << "8) Exit" << endl;

    cout << "Your Choice:";
    cin >> choice;
    cin.ignore();



}


void findIndexByTitleStart(const vector<Book> &books) {
    string input;
    cout << "--Enter book title:";
    getline(cin, input);
    int index = findIndexByName(books, input);
    if (index == -1) {
        cout  << "--Book with title '" << input << "' not found." << endl;
    } else {
        cout << "--Book found!" << endl;
        displayTable(books[index]);
    }
}

void countBooksByGenreStart(const vector<Book> &books) {
    map<string, int> genreMap = countBooksByGenre(books);

    //results
    cout << string(62, '-') << endl;
    cout << "| Genre" << setw(35) << "| Quantity" << setw(13) << "|" << endl;
    cout << string(62, '-') << endl;


    //map iteration learned from https://cplusplus.com/reference/map/map/begin/
    for (map<string, int>::iterator iter = genreMap.begin(); iter != genreMap.end() ; ++iter) {
        cout << "| " << iter->first << setw(32 - iter->first.size()) << "| " << iter->second << setw(11- to_string(iter->second).size()) << "|" << endl;
    }

    cout << string(62, '-') << endl;
}

void filterByGenreStart(const vector<Book> books) {
    string genre;
    cout << "Enter genre:";
    getline(cin, genre);
    filterByGenre(books, genre);
}

void searchBooksByTitleStart(const vector<Book> books) {
    string searchQuery;
    cout << "Enter phrase to search for:";
    getline(cin, searchQuery);
    list<Book> results = searchBooksByTitle(books, searchQuery);
    displayTable(results);

}






int main() {
    vector<Book> books;
    loadBooks(books);
    int choice = 0;
    do {
        executeMenu(choice);
        switch (choice) {
            case 1:
                displayTable(books);
                break;
            case 2:
                findIndexByTitleStart(books);
                break;
            case 3:
                countBooksByGenreStart(books);
                break;
            case 4:
                filterByGenreStart(books);
                break;
            case 5: {
                //curly bracket needed to fix "jump to case label" error
                //converted to int to avoid having years expressed in floating points
                int avgYear = analyseReleaseYears(books);
                cout << "\n---Average Release Year: " << avgYear << "---\n" << endl;
                break;
            }
            case 6:
                searchBooksByTitleStart(books);
                break;
            case 7:
                displayByRatingHighToLow(books);
                break;
            case 8:
                cout << "---Thank you for using the application.---" << endl;
                break;
            default:
                cout << "---Invalid Input---" << endl;
                break;



        }
    } while (choice != 8);


    return 0;
}