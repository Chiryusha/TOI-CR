

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
    void display();
    void readFromFile(const string& filename);
    void sortByIdAscending();
    void sortByYearDescending();
    ListNode* getTail();
    void displaySortedById();
    void displaySortedByYear();
    void searchByYear(unsigned int year);
    ListNode* recursiveSearchById(ListNode*& current, unsigned int id);
    ListNode* head;
    bool deleteById(unsigned int id);

private:
    void setPrevPointers(ListNode* node, ListNode* prev = nullptr);
    ListNode* partitionById(ListNode* low, ListNode* high);
    void quickSortById(ListNode* low, ListNode* high);
    void bubbleSortByYear();
};

void Input(GoldenBallOwners& player);



