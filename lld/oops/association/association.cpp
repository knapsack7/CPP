#include <iostream>
#include <vector>
#include <string>
#include <memory>
using namespace std;

class Library;

class Book {
private:
    string title;
    shared_ptr<Library> library;
public:
    Book(string title,  shared_ptr<Library> library);
    void showLibrary();
    string getTitle() { return title; }
};

class Library {
private:
    string name;
    vector<shared_ptr<Book>> books;
public:
    Library(string name) : name(name) {}
    void addBook(shared_ptr<Book> book) { books.push_back(book); }
    string getName() { return name; }
    void showBooks();
};

Book::Book(string title, shared_ptr<Library> library) : title(title), library(library) {}

void Book::showLibrary() {
    cout << title << " is in " << library->getName() << endl;
}

void Library::showBooks() {
    cout << "Books in " << name << ":" << endl;
    for (auto &  book : books) {
        cout << " - " << book->getTitle() << endl;
    }
}

int main() {
    shared_ptr<Library> library = make_shared<Library>("City Library");
    shared_ptr<Book>  book1= make_unique<Book>("1984", library);
    shared_ptr<Book> book2 = make_unique<Book>("Brave New World", library);
    
    library->addBook(book1);
    library->addBook(book2);
    
    library->showBooks();
    book1->showLibrary();
    book2->showLibrary();
    
    return 0;
}