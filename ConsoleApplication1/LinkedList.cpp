#include "LinkedList.h"
#include <iostream>

LinkedList::LinkedList() : head(nullptr) {}

LinkedList::~LinkedList() {
    while (head != nullptr) {
        ListNode* temp = head;
        head = head->next;
        delete temp;
    }
}

void LinkedList::Insert(const GoldenBallOwners& data) {
    ListNode* newNode = new ListNode(data);
    newNode->next = head;
    head = newNode;
    SortById(); // Сортируем список после вставки
}

void LinkedList::Print() const {
    ListNode* current = head;
    while (current != nullptr) {
        current->data.Show();
        std::cout << std::endl;
        current = current->next;
    }
}

void LinkedList::PrintSortedById() const {
    ListNode* sortedList = nullptr;
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* nextNode = current->next;
        current->next = sortedList;
        sortedList = current;
        current = nextNode;
    }
    current = sortedList;
    while (current != nullptr) {
        current->data.Show();
        std::cout << std::endl;
        current = current->next;
    }
}

void LinkedList::PrintSortedByYear() const {
    ListNode* sortedList = nullptr;
    ListNode* current = head;
    while (current != nullptr) {
        ListNode* nextNode = current->next;
        current->next = sortedList;
        sortedList = current;
        current = nextNode;
    }
    current = sortedList;
    while (current != nullptr) {
        current->data.Show();
        std::cout << std::endl;
        current = current->next;
    }
}

bool LinkedList::SearchById(int id, GoldenBallOwners& result) const {
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

bool LinkedList::SearchByYear(int year, GoldenBallOwners& result) const {
    ListNode* current = head;
    while (current != nullptr) {
        if (current->data.year_of_getting_prize == year) {
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
        return false;
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
}
