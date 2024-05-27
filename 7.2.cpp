#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

class BookBase {
public:
    virtual ~BookBase() = default;
    virtual void display() const = 0;
    virtual int getUDK() const = 0;
    virtual int getCopies() const = 0;
    virtual void decreaseCopies() = 0;
    virtual void increaseCopies() = 0;
};

class Book : public BookBase {
private:
    int UDK;
    std::string author;
    std::string title;
    int year;
    int copies;

public:
    Book(int udk, const std::string& auth, const std::string& tit, int yr, int cpy)
        : UDK(udk), author(auth), title(tit), year(yr), copies(cpy) {}

    void display() const override {
        std::cout << "UDK: " << UDK << ", Author: " << author << ", Title: " << title
            << ", Year of publication: " << year << ",  Number of copies: " << copies << std::endl;
    }

    int getUDK() const override {
        return UDK;
    }

    int getCopies() const override {
        return copies;
    }

    void decreaseCopies() override {
        if (copies > 0) {
            copies--;
        }
    }

    void increaseCopies() override {
        copies++;
    }
};

class LibraryBase {
public:
    virtual ~LibraryBase() = default;
    virtual void addBook(BookBase* book) = 0;
    virtual void takeBook(int udk) = 0;
    virtual void returnBook(int udk) = 0;
    virtual void displayBooks() const = 0;
};

class Library : public LibraryBase {
private:
    std::vector<BookBase*> books;

public:
    ~Library() {
        for (BookBase* book : books) {
            delete book;
        }
    }

    void addBook(BookBase* book) override {
        books.push_back(book);
    }

    void takeBook(int udk) override {
        auto it = std::find_if(books.begin(), books.end(), [udk](BookBase* book) { return book->getUDK() == udk; });
        if (it != books.end()) {
            if ((*it)->getCopies() > 0) {
                (*it)->decreaseCopies();
                std::cout << "The book is taken. There are only a few copies left: " << (*it)->getCopies() << std::endl;
            }
            else {
                std::cout << "The required book is in hand.\n";
            }
        }
        else {
            std::cout << "The required book is not available in the library.\n";
        }
    }

    void returnBook(int udk) override {
        auto it = std::find_if(books.begin(), books.end(), [udk](BookBase* book) { return book->getUDK() == udk; });
        if (it != books.end()) {
            (*it)->increaseCopies();
            std::cout << "The book is back. There are only a few copies left: " << (*it)->getCopies() << std::endl;
        }
        else {
            std::cout << "The required book is not available in the library.\n";
        }
    }

    void displayBooks() const override {
        if (books.empty()) {
            std::cout << "The library is empty.\n";
        }
        else {
            for (const auto& book : books) {
                book->display();
            }
        }
    }
};

int main() {
    Library library;

    library.addBook(new Book(1, "George Orwell", "1984", 1949, 3));
    library.addBook(new Book(2, "J.K. Rowling", "Harry Potter and the Philosopher's Stone", 1997, 5));
    library.addBook(new Book(3, "Harper Lee", "To Kill a Mockingbird", 1960, 2));

    int choice;
    while (true) {
        std::cout << "\nMenu:\n";
        std::cout << "1. display all book\n";
        std::cout << "2. take book\n";
        std::cout << "3. return book\n";
        std::cout << "4. exit\n";
        std::cout << "your choice: ";
        std::cin >> choice;

        if (choice == 4) {
            break;
        }

        switch (choice) {
        case 1:
            library.displayBooks();
            break;
        case 2: {
            int udk;
            std::cout << "Enter the UDC number of the book: ";
            std::cin >> udk;
            library.takeBook(udk);
            break;
        }
        case 3: {
            int udk;
            std::cout << "Enter the UDC number of the book: ";
            std::cin >> udk;
            library.returnBook(udk);
            break;
        }
        default:
            std::cout << "Wrong choice. Please try again.\n";
            break;
        }
    }

    return 0;
}
