

#include "GoldenBallOwners.h"

struct ListNode {
    GoldenBallOwners data;
    ListNode* next;

    ListNode(const GoldenBallOwners& d) : data(d), next(nullptr) {}
};

class LinkedList {
public:
    LinkedList();
    ~LinkedList();

    void Insert(const GoldenBallOwners& data);
    void Print() const;
    void PrintSortedById() const;
    void PrintSortedByYear() const;
    bool SearchById(int id, GoldenBallOwners& result) const;
    bool SearchByYear(int year, GoldenBallOwners& result) const;
    bool DeleteById(int id);
    bool DeleteByYear(int year);

private:
    ListNode* head;
    void SortById();
    void SortByYear();
};
void inputGoldenBallOwnersFromFileToList(ListNode*& head);


