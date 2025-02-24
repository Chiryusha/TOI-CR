#pragma once
#include <iostream>
using namespace std;

struct GoldenBallOwners
{public:
    unsigned int id;
    string firstname;
    string lastname;
    string date_of_birth;
    unsigned int year_of_getting_prize;
    string country;
    string club;//f

    GoldenBallOwners();
    void Show() const;
};
void InputPlayers(GoldenBallOwners* ballers, int n);
void CreateIndex(const GoldenBallOwners* array, int n, int* indexid, int* IndexYear);
void PrintByIndex(const GoldenBallOwners* array, const int* index, int n);
int BinarySearchRecursive(const GoldenBallOwners* array, const int* index, int left, int right, int key);
int BinarySearchIterative(const GoldenBallOwners* array, const int* index, int n, int key, bool byYear);
void UpdateRecord(GoldenBallOwners* array, int* indexId, int* indexYear, int n, int id);
void UpdateRecordYear(GoldenBallOwners* array, int* indexId, int* indexYear, int n, int id);
void DeleteRecord(GoldenBallOwners* array, int* indexId, int* indexYear, int& n, int id);
void DeleteRecordYear(GoldenBallOwners* array, int* indexId, int* indexYear, int& n, int year);
void inputGoldenBallOwnersFromFile(GoldenBallOwners* array);






