

#include "GoldenBallOwners.h"

struct ListNode {
    GoldenBallOwners data;
    ListNode* next;
    ListNode* prev;

    ListNode(const GoldenBallOwners& d) : data(d), next(nullptr), prev(nullptr) {}
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void Insert(GoldenBallOwners& data);
    void readFromFile(const string& filename);
    void searchByYear(unsigned int year);
    ListNode* recursiveSearchById(ListNode* current,unsigned int id);
    ListNode* head;
    bool deleteById(unsigned int id);
    bool DeleteByYear(unsigned int year);
    ListNode* headById;                 // Список, упорядоченный по id (возрастание)
    ListNode* headByYear;               // Список, упорядоченный по году (убывание)
    ListNode* inputOrderHead;
    void displaySortedById();
    void displaySortedByYear();
    void displayInInputOrder();;
};

void Input(GoldenBallOwners& player,int n);



