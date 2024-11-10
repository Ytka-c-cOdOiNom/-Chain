#include <iostream>
#include <windows.h>
using namespace std;

// Абстрактний клас обробника запитів
class Handler {
protected:
    Handler* nextHandler;  // Наступний обробник у ланцюзі

public:
    Handler() : nextHandler(nullptr) {}

    void setNextHandler(Handler* handler) {
        nextHandler = handler;
    }

    virtual void handleRequest(const string& request) = 0;  // Абстрактний метод для обробки запиту
};

// Початковий рівень обробки (підтримка)
class Level1Handler : public Handler {
public:
    void handleRequest(const string& request) override {
        if (request == "simple") {
            cout << "Обробка на початковому рівні: запит вирішено!" << endl;
        }
        else if (nextHandler) {
            nextHandler->handleRequest(request);  // Передаємо запит далі
        }
    }
};

// Середній рівень обробки (підтримка)
class Level2Handler : public Handler {
public:
    void handleRequest(const string& request) override {
        if (request == "intermediate") {
            cout << "Обробка на середньому рівні: запит вирішено!" << endl;
        }
        else if (nextHandler) {
            nextHandler->handleRequest(request);  // Передаємо запит далі
        }
    }
};

// Вищий рівень обробки (підтримка)
class Level3Handler : public Handler {
public:
    void handleRequest(const string& request) override {
        if (request == "complex") {
            cout << "Обробка на вищому рівні: запит вирішено!" << endl;
        }
        else {
            cout << "Запит не може бути оброблений." << endl;
        }
    }
};


int main() {

    SetConsoleCP(1251);
    SetConsoleOutputCP(1251);

    // Створюємо обробників
    Level1Handler* level1 = new Level1Handler();
    Level2Handler* level2 = new Level2Handler();
    Level3Handler* level3 = new Level3Handler();

    // Створюємо ланцюг обробників
    level1->setNextHandler(level2);
    level2->setNextHandler(level3);

    // Імітація запитів від клієнтів
    string request1 = "1";     // Запит на початковий рівень
    string request2 = "2";  // Запит на середній рівень
    string request3 = "3";    // Запит на вищий рівень
    string request4 = "?";    // Невідомий запит

    // Обробка запитів
    cout << "Обробка запиту: " << request1 << endl;
    level1->handleRequest(request1);

    cout << "\nОбробка запиту: " << request2 << endl;
    level1->handleRequest(request2);

    cout << "\nОбробка запиту: " << request3 << endl;
    level1->handleRequest(request3);

    cout << "\nОбробка запиту: " << request4 << endl;
    level1->handleRequest(request4);


    delete level1;
    delete level2;
    delete level3;


}
