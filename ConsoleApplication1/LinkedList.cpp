#include "LinkedList.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    // Очистка списка по id
    ListNode* current = headById;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
    // Очистка списка по году
    current = headByYear;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
    // Очистка списка порядка ввода
    current = inputOrderHead;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}


void LinkedList::Insert(GoldenBallOwners& data) {
    // 1. Создание нового узла для всех трёх списков
    ListNode* newNode = new ListNode(data);

    // 2. Добавление в список порядка ввода (в конец)
    if (!inputOrderHead) {
        inputOrderHead = newNode;
    }
    else {
        ListNode* current = inputOrderHead;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }

    // 3. Вставка в список, упорядоченный по id (по возрастанию)
    ListNode* currentId = headById;
    ListNode* prevId = nullptr;
    while (currentId != nullptr && currentId->data.id < data.id) {
        prevId = currentId;
        currentId = currentId->next;
    }
    if (prevId == nullptr) {
        newNode = new ListNode(data); // Создаём новый узел для каждого списка
        newNode->next = headById;
        headById = newNode;
    }
    else {
        newNode = new ListNode(data); // Создаём новый узел для каждого списка
        newNode->next = currentId;
        prevId->next = newNode;
    }

    // 4. Вставка в список, упорядоченный по году (по убыванию)
    ListNode* currentYear = headByYear;
    ListNode* prevYear = nullptr;
    while (currentYear != nullptr && currentYear->data.year_of_getting_prize > data.year_of_getting_prize) {
        prevYear = currentYear;
        currentYear = currentYear->next;
    }
    if (prevYear == nullptr) {
        newNode = new ListNode(data); // Создаём новый узел для каждого списка
        newNode->next = headByYear;
        headByYear = newNode;
    }
    else {
        newNode = new ListNode(data); // Создаём новый узел для каждого списка
        newNode->next = currentYear;
        prevYear->next = newNode;
    }
}




void LinkedList::displayInInputOrder() {
    ListNode* current = inputOrderHead;
    while (current) {
        current->data.Show();
        cout << "-------------------" << endl;
        current = current->next;
    }
}


void LinkedList::displaySortedById() {
    ListNode* current = headById;
    while (current) {
        current->data.Show();
        cout << "-------------------" << endl;
        current = current->next;
    }
}

void LinkedList::displaySortedByYear() {
    ListNode* current = headByYear;
    while (current) {
        current->data.Show();
        cout << "-------------------" << endl;
        current = current->next;
    }
}


ListNode* LinkedList::recursiveSearchById(ListNode* current, unsigned int id) {
    if (current == nullptr) {
        return nullptr; // Список пуст, элемент не найден
    }
    if (current->data.id == id) {
        return current; // Элемент найден (первый по порядку в списке по id)
    }
    return recursiveSearchById(current->next, id); // Рекурсивный вызов для следующего узла
}


void LinkedList::searchByYear(unsigned int year) {
    ListNode* current = headByYear; // Начинаем поиск в списке, упорядоченном по году (убывание)
    bool found = false;

    while (current) {
        if (current->data.year_of_getting_prize == year) {
            if (!found) {
                cout << "Игроки, получившие награду в " << year << " году:" << endl;
                found = true;
            }
            cout << "Номер: " << current->data.id << endl;
            cout << "Имя: " << current->data.firstname << " " << current->data.lastname << endl;
            cout << "Дата рождения: " << current->data.date_of_birth << endl;
            cout << "Страна: " << current->data.country << endl;
            cout << "Клуб: " << current->data.club << endl;
            cout << "------------------------" << endl;
        }
        current = current->next;
    }

    // Проверка в других списках на случай несогласованности (опционально, для отладки)
    current = inputOrderHead;
    while (current) {
        if (current->data.year_of_getting_prize == year && !found) {
            cout << "Игроки, получившие награду в " << year << " году (из порядка ввода):" << endl;
            found = true;
            cout << "ID: " << current->data.id << endl;
            cout << "Имя: " << current->data.firstname << " " << current->data.lastname << endl;
            cout << "Дата рождения: " << current->data.date_of_birth << endl;
            cout << "Страна: " << current->data.country << endl;
            cout << "Клуб: " << current->data.club << endl;
            cout << "------------------------" << endl;
        }
        current = current->next;
    }

    current = headById;
    while (current) {
        if (current->data.year_of_getting_prize == year && !found) {
            cout << "Игроки, получившие награду в " << year << " году (из порядка по id):" << endl;
            found = true;
            cout << "ID: " << current->data.id << endl;
            cout << "Имя: " << current->data.firstname << " " << current->data.lastname << endl;
            cout << "Дата рождения: " << current->data.date_of_birth << endl;
            cout << "Страна: " << current->data.country << endl;
            cout << "Клуб: " << current->data.club << endl;
            cout << "------------------------" << endl;
        }
        current = current->next;
    }

    if (!found) {
        cout << "Игроки с годом получения награды " << year << " не найдены." << endl;
    }
}

bool LinkedList::deleteById(unsigned int id) {
    bool deleted = false;

    // Удаление из списка порядка ввода (inputOrderHead)
    ListNode* currentInput = inputOrderHead;
    ListNode* prevInput = nullptr;
    while (currentInput != nullptr && currentInput->data.id != id) {
        prevInput = currentInput;
        currentInput = currentInput->next;
    }
    if (currentInput != nullptr) {
        if (prevInput == nullptr) {
            inputOrderHead = currentInput->next;
            if (inputOrderHead) inputOrderHead->prev = nullptr;
        }
        else {
            prevInput->next = currentInput->next;
            if (currentInput->next) currentInput->next->prev = prevInput;
        }
        delete currentInput;
        deleted = true;
    }

    // Удаление из списка по id (headById)
    ListNode* currentId = headById;
    ListNode* prevId = nullptr;
    while (currentId != nullptr && currentId->data.id != id) {
        prevId = currentId;
        currentId = currentId->next;
    }
    if (currentId != nullptr) {
        if (prevId == nullptr) {
            headById = currentId->next;
            if (headById) headById->prev = nullptr;
        }
        else {
            prevId->next = currentId->next;
            if (currentId->next) currentId->next->prev = prevId;
        }
        delete currentId;
        deleted = true;
    }

    // Удаление из списка по году (headByYear)
    ListNode* currentYear = headByYear;
    ListNode* prevYear = nullptr;
    while (currentYear != nullptr && currentYear->data.id != id) {
        prevYear = currentYear;
        currentYear = currentYear->next;
    }
    if (currentYear != nullptr) {
        if (prevYear == nullptr) {
            headByYear = currentYear->next;
            if (headByYear) headByYear->prev = nullptr;
        }
        else {
            prevYear->next = currentYear->next;
            if (currentYear->next) currentYear->next->prev = prevYear;
        }
        delete currentYear;
        deleted = true;
    }

    if (deleted) {
        cout << "Игрок с ID " << id << " успешно удалён из всех списков." << endl;
        return true;
    }
    else {
        cout << "Игрок с ID " << id << " не найден." << endl;
        return false;
    }
}


bool LinkedList::DeleteByYear(unsigned int year) {
    bool deleted = false;

    // Удаление из списка порядка ввода (inputOrderHead)
    ListNode* currentInput = inputOrderHead;
    ListNode* prevInput = nullptr;
    while (currentInput != nullptr && currentInput->data.year_of_getting_prize != year) {
        prevInput = currentInput;
        currentInput = currentInput->next;
    }
    if (currentInput != nullptr) {
        if (prevInput == nullptr) {
            inputOrderHead = currentInput->next;
            if (inputOrderHead) inputOrderHead->prev = nullptr;
        }
        else {
            prevInput->next = currentInput->next;
            if (currentInput->next) currentInput->next->prev = prevInput;
        }
        delete currentInput;
        deleted = true;
    }

    // Удаление из списка по id (headById)
    ListNode* currentId = headById;
    ListNode* prevId = nullptr;
    while (currentId != nullptr && currentId->data.year_of_getting_prize != year) {
        prevId = currentId;
        currentId = currentId->next;
    }
    if (currentId != nullptr) {
        if (prevId == nullptr) {
            headById = currentId->next;
            if (headById) headById->prev = nullptr;
        }
        else {
            prevId->next = currentId->next;
            if (currentId->next) currentId->next->prev = prevId;
        }
        delete currentId;
        deleted = true;
    }

    // Удаление из списка по году (headByYear)
    ListNode* currentYear = headByYear;
    ListNode* prevYear = nullptr;
    while (currentYear != nullptr && currentYear->data.year_of_getting_prize != year) {
        prevYear = currentYear;
        currentYear = currentYear->next;
    }
    if (currentYear != nullptr) {
        if (prevYear == nullptr) {
            headByYear = currentYear->next;
            if (headByYear) headByYear->prev = nullptr;
        }
        else {
            prevYear->next = currentYear->next;
            if (currentYear->next) currentYear->next->prev = prevYear;
        }
        delete currentYear;
        deleted = true;
    }

    if (deleted) {
        cout << "Игрок с годом получения награды " << year << " успешно удалён из всех списков." << endl;
        return true;
    }
    else {
        cout << "Игрок с годом получения награды " << year << " не найден." << endl;
        return false;
    }
}

void LinkedList::readFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Не удалось открыть файл: " << filename << endl;
        return;
    }

    string line;
    // Считываем первую строку — количество футболистов (игнорируем её, если не нужно)
    if (getline(file, line)) {
        // Можно добавить обработку количества, если нужно, например:
        int playerCount = stoi(line);
    }

    // Считываем данные каждого футболиста
    while (getline(file, line)) {
        stringstream ss(line); // Используем stringstream для парсинга строки
        GoldenBallOwners player;
        string temp;

        // Читаем все токены из строки
        ss >> player.id >> player.firstname >> player.lastname >> player.date_of_birth
            >> player.year_of_getting_prize >> player.country >> player.club;

        Insert(player); // Добавляем игрока в список
    }

    file.close();
}
void Input(GoldenBallOwners& player,int n) {
    string day, month, year;
    for (int i = 0; i < n; i++) {
        cout << "Введите данные игрока " << i + 1 << ":\n";
        cout << "Номер игрока: "<< endl;
        cin >> player.id;
        cin.ignore();

        cout << "Введите имя игрока: "<< endl;
        getline(cin, player.firstname);
        cout << "Введите фамилию игрока: "<< endl;
        getline(cin, player.lastname);
        cout << "Введите дату рождения игрока в формате ДД.ММ.ГГГГ: "<< endl;
        cout << "День: ";
        getline(cin, day);
        cout << "Месяц в формате ММ: ";
        getline(cin, month);
        cout << "Год: ";
        getline(cin, year);
        player.date_of_birth = day + "." + month + "." + year; // Сохраняем корректную дату
        cout << "Введите год получения золотого мяча: " << endl;
        cin >> player.year_of_getting_prize;
        cin.ignore();
        cout << "Введите страну футболиста: " << endl;
        getline(cin, player.country);
        cout << "Введите клуб в котором футболист получил награду: " << endl;
        getline(cin, player.club);
    }
}

