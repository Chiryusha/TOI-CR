#include "LinkedList.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}


void LinkedList::Insert(GoldenBallOwners& data) {
    ListNode* newNode = new ListNode(data);
    if (!head) {
        head = newNode;
        return;
    }
    ListNode* current = head;
    while (current->next) {
        current = current->next;
    }
    current->next = newNode;
}


void LinkedList::display() {
    ListNode* current = head;
    while (current) {
        current->data.Show();
        current = current->next;
    }
}
ListNode* LinkedList::partitionById(ListNode* low, ListNode* high) {
    GoldenBallOwners pivot = high->data;
    ListNode* i = low->prev; // Указатель на предыдущий элемент (нужно для списка)

    for (ListNode* j = low; j != high; j = j->next) {
        if (j->data.id <= pivot.id) {
            i = (i == nullptr) ? low : i->next;
            swap(i->data, j->data);
        }
    }
    i = (i == nullptr) ? low : i->next;
    swap(i->data, high->data);
    return i;
}

void LinkedList::quickSortById(ListNode* low, ListNode* high) {
    if (low != nullptr && high != nullptr && low != high && low != high->next) {
        ListNode* pi = partitionById(low, high);
        quickSortById(low, pi->prev);
        quickSortById(pi->next, high);
    }
}

void LinkedList::bubbleSortByYear() {
    if (!head || !head->next) return;

    bool swapped;
    ListNode* last = nullptr;

    do {
        swapped = false;
        ListNode* current = head;

        while (current->next != last) {
            if (current->data.year_of_getting_prize < current->next->data.year_of_getting_prize) {
                swap(current->data, current->next->data);
                swapped = true;
            }
            current = current->next;
        }
        last = current;
    } while (swapped);
}

void LinkedList::setPrevPointers(ListNode* node, ListNode* prev) {
    while (node) {
        node->prev = prev;
        prev = node;
        node = node->next;
    }
}

void LinkedList:: sortByIdAscending() {
    if (!head || !head->next) return;

    // Устанавливаем prev указатели для работы с быстрой сортировкой
    setPrevPointers(head);
    GoldenBallOwners dummyData; // Пустой объект GoldenBallOwners
    ListNode dummy(dummyData); // Временный узел для начала
    dummy.next = head;
    head->prev = &dummy;
    quickSortById(head, getTail());
    head = dummy.next;
    head->prev = nullptr;
}

// Сортировка по убыванию года получения награды (сортировка пузырьком)
void LinkedList:: sortByYearDescending() {
    bubbleSortByYear();
}

// Вспомогательная функция для получения последнего узла
ListNode* LinkedList::getTail() {
    ListNode* current = head;
    while (current && current->next) {
        current = current->next;
    }
    return current;
}

// Вывод отсортированного списка по ID (по возрастанию)
void LinkedList::displaySortedById() {
    sortByIdAscending();
    ListNode* current = head;
    while (current) {
        cout << "ID: " << current->data.id << endl;
        cout << "Имя: " << current->data.firstname << " " << current->data.lastname << endl;
        cout << "Дата рождения: " << current->data.date_of_birth << endl;
        cout << "Год награды: " << current->data.year_of_getting_prize << endl;
        cout << "Страна: " << current->data.country << endl;
        cout << "Клуб: " << current->data.club << endl;
        cout << "------------------------" << endl;
        current = current->next;
    }
}

// Вывод отсортированного списка по году (по убыванию)
void LinkedList::displaySortedByYear() {
    sortByYearDescending();
    ListNode* current = head;
    while (current) {
        cout << "Год награды: " << current->data.year_of_getting_prize << endl;
        cout << "Имя: " << current->data.firstname << " " << current->data.lastname << endl;
        cout << "ID: " << current->data.id << endl;
        cout << "Дата рождения: " << current->data.date_of_birth << endl;
        cout << "Страна: " << current->data.country << endl;
        cout << "Клуб: " << current->data.club << endl;
        cout << "------------------------" << endl;
        current = current->next;
    }
}


ListNode* LinkedList::recursiveSearchById(ListNode*& current, unsigned int id) {
    if (current == nullptr) {
        return nullptr; // Элемент не найден
    }
    if (current->data.id == id) {
        return current; // Элемент найден
    }
    return recursiveSearchById(current->next, id); // Рекурсивный вызов для следующего узла
}


    void LinkedList::searchByYear(unsigned int year) {
        ListNode* current = head;
        bool found = false;

        while (current) {
            if (current->data.year_of_getting_prize == year) {
                if (!found) {
                    cout << "Игроки, получившие награду в " << year << " году:" << endl;
                    found = true;
                }
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
        ListNode* current = head;
        ListNode* prevNode = nullptr;

        // Ищем узел с заданным ID
        while (current != nullptr && current->data.id != id) {
            prevNode = current;
            current = current->next;
        }

        // Если узел не найден
        if (current == nullptr) {
            cout << "Игрок с ID " << id << " не найден." << endl;
            return false;
        }

        // Если удаляем head
        if (current == head) {
            head = current->next;
            if (head) {
                head->prev = nullptr;
            }
        }
        // Если удаляем не head
        else {
            prevNode->next = current->next;
            if (current->next) {
                current->next->prev = prevNode;
            }
        }

        delete current; // Освобождаем память
        cout << "Игрок с ID " << id << " успешно удалён." << endl;
        return true;
    }










/*bool LinkedList::SearchById(int id, GoldenBallOwners& result) const {
    ListNode* current = head;
    while (current != nullptr) {
        if (current->data.id == id) {
            result = current->data;
            return true;
        }
        current = current->next;
    }
    return false;
}


bool LinkedList::DeleteById(int id) {
    ListNode* current = head;
    ListNode* prev = nullptr;
    while (current != nullptr && current->data.id != id) {
        prev = current;
        current = current->next;
    }
    if (current == nullptr) {
        return false; ////
    }
    if (prev == nullptr) {
        head = current->next;
    }
    else {
        prev->next = current->next;
    }
    delete current;
    return true;
}

bool LinkedList::DeleteByYear(int year) {
    ListNode* current = head;
    ListNode* prev = nullptr;
    while (current != nullptr && current->data.year_of_getting_prize != year) {
        prev = current;
        current = current->next;
    }
    if (current == nullptr) {
        return false; // Запись не найдена
    }
    if (prev == nullptr) {
        head = current->next;
    }
    else {
        prev->next = current->next;
    }
    delete current;
    return true;
}

void LinkedList::SortById() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    ListNode* current = head;
    while (current != nullptr) {
        ListNode* nextNode = current->next;
        while (nextNode != nullptr) {
            if (current->data.id > nextNode->data.id) {
                std::swap(current->data, nextNode->data);
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }
}

void LinkedList::SortByYear() {
    if (head == nullptr || head->next == nullptr) {
        return;
    }

    ListNode* current = head;
    while (current != nullptr) {
        ListNode* nextNode = current->next;
        while (nextNode != nullptr) {
            if (current->data.year_of_getting_prize > nextNode->data.year_of_getting_prize) {
                std::swap(current->data, nextNode->data);
            }
            nextNode = nextNode->next;
        }
        current = current->next;
    }
}*/

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
void Input(GoldenBallOwners& player) {
    string day, month, year;
    cout << "Номер игрока:" << endl;
    cin >> player.id;
    cin.ignore();

    cout << "Введите имя игрока:" << endl;
    getline(cin, player.firstname);
    cout << "Введите фамилию игрока:" << endl;
    getline(cin, player.lastname);
    cout << "Введите дату рождения игрока в формате ДД.ММ.ГГГГ:" << endl;
    cout << "День: ";
    getline(cin, day);
    cout << "Месяц в формате ММ: ";
    getline(cin, month);
    cout << "Год: ";
    getline(cin, year);
    player.date_of_birth = day + "." + month + "." + year; // Сохраняем корректную дату
    cout << "Введите год получения золотого мяча:" << endl;
    cin >> player.year_of_getting_prize;
    cin.ignore();
    cout << "Введите страну футболиста:" << endl;
    getline(cin, player.country);
    cout << "Введите клуб в котором футболист получил награду:" << endl;
    getline(cin, player.club);
}

