#include "LinkedList.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    // ������� ������ �� id
    ListNode* current = headById;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
    // ������� ������ �� ����
    current = headByYear;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
    // ������� ������ ������� �����
    current = inputOrderHead;
    while (current) {
        ListNode* next = current->next;
        delete current;
        current = next;
    }
}


void LinkedList::Insert(GoldenBallOwners& data) {
    // 1. �������� ������ ���� ��� ���� ��� �������
    ListNode* newNode = new ListNode(data);

    // 2. ���������� � ������ ������� ����� (� �����)
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

    // 3. ������� � ������, ������������� �� id (�� �����������)
    ListNode* currentId = headById;
    ListNode* prevId = nullptr;
    while (currentId != nullptr && currentId->data.id < data.id) {
        prevId = currentId;
        currentId = currentId->next;
    }
    if (prevId == nullptr) {
        newNode = new ListNode(data); // ������ ����� ���� ��� ������� ������
        newNode->next = headById;
        headById = newNode;
    }
    else {
        newNode = new ListNode(data); // ������ ����� ���� ��� ������� ������
        newNode->next = currentId;
        prevId->next = newNode;
    }

    // 4. ������� � ������, ������������� �� ���� (�� ��������)
    ListNode* currentYear = headByYear;
    ListNode* prevYear = nullptr;
    while (currentYear != nullptr && currentYear->data.year_of_getting_prize > data.year_of_getting_prize) {
        prevYear = currentYear;
        currentYear = currentYear->next;
    }
    if (prevYear == nullptr) {
        newNode = new ListNode(data); // ������ ����� ���� ��� ������� ������
        newNode->next = headByYear;
        headByYear = newNode;
    }
    else {
        newNode = new ListNode(data); // ������ ����� ���� ��� ������� ������
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
        return nullptr; // ������ ����, ������� �� ������
    }
    if (current->data.id == id) {
        return current; // ������� ������ (������ �� ������� � ������ �� id)
    }
    return recursiveSearchById(current->next, id); // ����������� ����� ��� ���������� ����
}


void LinkedList::searchByYear(unsigned int year) {
    ListNode* current = headByYear; // �������� ����� � ������, ������������� �� ���� (��������)
    bool found = false;

    while (current) {
        if (current->data.year_of_getting_prize == year) {
            if (!found) {
                cout << "������, ���������� ������� � " << year << " ����:" << endl;
                found = true;
            }
            cout << "�����: " << current->data.id << endl;
            cout << "���: " << current->data.firstname << " " << current->data.lastname << endl;
            cout << "���� ��������: " << current->data.date_of_birth << endl;
            cout << "������: " << current->data.country << endl;
            cout << "����: " << current->data.club << endl;
            cout << "------------------------" << endl;
        }
        current = current->next;
    }

    // �������� � ������ ������� �� ������ ����������������� (�����������, ��� �������)
    current = inputOrderHead;
    while (current) {
        if (current->data.year_of_getting_prize == year && !found) {
            cout << "������, ���������� ������� � " << year << " ���� (�� ������� �����):" << endl;
            found = true;
            cout << "ID: " << current->data.id << endl;
            cout << "���: " << current->data.firstname << " " << current->data.lastname << endl;
            cout << "���� ��������: " << current->data.date_of_birth << endl;
            cout << "������: " << current->data.country << endl;
            cout << "����: " << current->data.club << endl;
            cout << "------------------------" << endl;
        }
        current = current->next;
    }

    current = headById;
    while (current) {
        if (current->data.year_of_getting_prize == year && !found) {
            cout << "������, ���������� ������� � " << year << " ���� (�� ������� �� id):" << endl;
            found = true;
            cout << "ID: " << current->data.id << endl;
            cout << "���: " << current->data.firstname << " " << current->data.lastname << endl;
            cout << "���� ��������: " << current->data.date_of_birth << endl;
            cout << "������: " << current->data.country << endl;
            cout << "����: " << current->data.club << endl;
            cout << "------------------------" << endl;
        }
        current = current->next;
    }

    if (!found) {
        cout << "������ � ����� ��������� ������� " << year << " �� �������." << endl;
    }
}

bool LinkedList::deleteById(unsigned int id) {
    bool deleted = false;

    // �������� �� ������ ������� ����� (inputOrderHead)
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

    // �������� �� ������ �� id (headById)
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

    // �������� �� ������ �� ���� (headByYear)
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
        cout << "����� � ID " << id << " ������� ����� �� ���� �������." << endl;
        return true;
    }
    else {
        cout << "����� � ID " << id << " �� ������." << endl;
        return false;
    }
}


bool LinkedList::DeleteByYear(unsigned int year) {
    bool deleted = false;

    // �������� �� ������ ������� ����� (inputOrderHead)
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

    // �������� �� ������ �� id (headById)
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

    // �������� �� ������ �� ���� (headByYear)
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
        cout << "����� � ����� ��������� ������� " << year << " ������� ����� �� ���� �������." << endl;
        return true;
    }
    else {
        cout << "����� � ����� ��������� ������� " << year << " �� ������." << endl;
        return false;
    }
}

void LinkedList::readFromFile(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "�� ������� ������� ����: " << filename << endl;
        return;
    }

    string line;
    // ��������� ������ ������ � ���������� ����������� (���������� �, ���� �� �����)
    if (getline(file, line)) {
        // ����� �������� ��������� ����������, ���� �����, ��������:
        int playerCount = stoi(line);
    }

    // ��������� ������ ������� ����������
    while (getline(file, line)) {
        stringstream ss(line); // ���������� stringstream ��� �������� ������
        GoldenBallOwners player;
        string temp;

        // ������ ��� ������ �� ������
        ss >> player.id >> player.firstname >> player.lastname >> player.date_of_birth
            >> player.year_of_getting_prize >> player.country >> player.club;

        Insert(player); // ��������� ������ � ������
    }

    file.close();
}
void Input(GoldenBallOwners& player,int n) {
    string day, month, year;
    for (int i = 0; i < n; i++) {
        cout << "������� ������ ������ " << i + 1 << ":\n";
        cout << "����� ������: "<< endl;
        cin >> player.id;
        cin.ignore();

        cout << "������� ��� ������: "<< endl;
        getline(cin, player.firstname);
        cout << "������� ������� ������: "<< endl;
        getline(cin, player.lastname);
        cout << "������� ���� �������� ������ � ������� ��.��.����: "<< endl;
        cout << "����: ";
        getline(cin, day);
        cout << "����� � ������� ��: ";
        getline(cin, month);
        cout << "���: ";
        getline(cin, year);
        player.date_of_birth = day + "." + month + "." + year; // ��������� ���������� ����
        cout << "������� ��� ��������� �������� ����: " << endl;
        cin >> player.year_of_getting_prize;
        cin.ignore();
        cout << "������� ������ ����������: " << endl;
        getline(cin, player.country);
        cout << "������� ���� � ������� ��������� ������� �������: " << endl;
        getline(cin, player.club);
    }
}

