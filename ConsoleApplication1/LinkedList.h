

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

    void PrintSortedById() const;
    void PrintSortedByYear() const;
    bool SearchById(int id, GoldenBallOwners& result) const;
    bool SearchByYear(int year, GoldenBallOwners& result) const;
    bool DeleteById(int id);
    bool DeleteByYear(int year);
    void display();
    void readFromFile(const string& filename);
    void sortByIdAscending();
    void sortByYearDescending();
    ListNode* getTail();
    void displaySortedById();
    void displaySortedByYear();

private:
    ListNode* head;
    void setPrevPointers(ListNode* node, ListNode* prev = nullptr);
    void SortById();
    void SortByYear();
    ListNode* partitionById(ListNode* low, ListNode* high);
    void quickSortById(ListNode* low, ListNode* high);
    void bubbleSortByYear();
};

void Input(GoldenBallOwners& player);



