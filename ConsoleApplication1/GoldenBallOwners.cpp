#include "GoldenBallOwners.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
using namespace std;

GoldenBallOwners::GoldenBallOwners() {
    id;
    firstname;
    lastname;
    date_of_birth;
    year_of_getting_prize;
    country;
    club;
};


void GoldenBallOwners::Show() const
{
    setlocale(LC_ALL, "ru");
    cout << "����� ������: " << id << endl;
    cout << "���: " << firstname << endl;
    cout << "�������: " << lastname << endl;
    cout << "���� ��������: " << date_of_birth << endl;
    cout << "���� ��������� ����: " << year_of_getting_prize << endl;
    cout << "������: " << country << endl;
    cout << "����: " << club << endl;
};

void GoldenBallOwners::InputPlayers(GoldenBallOwners* ballers, int n) {
    for (int i = 0; i < n; i++)
    {
        string day;
        string month;
        string year;
        cout << "������� ������ ������ " << i + 1 << ":\n";
        cout << "����� ������:" << endl;
        cin >> ballers[i].id;
        cin.ignore();

        cout << "������� ��� ������:" << endl;
        getline(cin, ballers[i].firstname);
        cout << "������� ������� ������:" << endl;
        getline(cin, ballers[i].lastname);
        cout << "������� ���� �������� ������ � ������� ��.��.����:" << endl;
        cout << "����: ";
        getline(cin, day);
        cout << "����� � ������� ��: ";
        getline(cin, month);
        cout << "���: ";
        getline(cin, year);
        ballers[i].date_of_birth = day + "." + month + "." + year; // ��������� ���������� ����
        cout << "������� ��� ��������� �������� ����:" << endl;
        cin >> ballers[i].year_of_getting_prize;
        cin.ignore();
        cout << "������� ������ ����������:" << endl;
        getline(cin, ballers[i].country);
        cout << "������� ���� � ������� ��������� ������� �������:" << endl;
        getline(cin, ballers[i].club);
    }
};
void CreateIndex(const GoldenBallOwners* array, int n, int* indexId, int* indexYear) {
    for (int i = 0; i < n; ++i) {
        indexId[i] = i;
        indexYear[i] = i;
    }

    // ���������� �������� �� id
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (array[indexId[j]].id > array[indexId[j + 1]].id) {
                swap(indexId[j], indexId[j + 1]);
            }
        }
    }
    // ���������� �������� �� ���� ��������� ����� ������� �������
    for (int i = 1; i < n; ++i) {
        int keyIndex = indexYear[i];
        int j = i - 1;

        // ���������� ��������, ������� ������, ��� ������� �������, �� ���� ������� ������
        while (j >= 0 && array[indexYear[j]].year_of_getting_prize < array[keyIndex].year_of_getting_prize) {
            indexYear[j + 1] = indexYear[j];
            j = j - 1;
        }
        indexYear[j + 1] = keyIndex;
    }
    
    
    
    
    
    
    /*���������� �������� �� ���� ��������� �����
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (array[indexYear[j]].year_of_getting_prize < array[indexYear[j + 1]].year_of_getting_prize) {
                swap(indexYear[j], indexYear[j + 1]);
            }
        }
    }*/
}

void PrintByIndex(const GoldenBallOwners* array, const int* index, int n) {
    for (int i = 0; i < n; ++i) {
        array[index[i]].Show();
        cout << endl;
    }
}

int BinarySearchRecursive(const GoldenBallOwners* array, const int* index, int left, int right, int key, bool byYear) {
    if (right >= left) {
        int mid = left + (right - left) / 2;
        if (byYear ? array[index[mid]].year_of_getting_prize == key : array[index[mid]].id == key) {
            return index[mid];
        }
        if (byYear ? array[index[mid]].year_of_getting_prize > key : array[index[mid]].id > key) {
            return BinarySearchRecursive(array, index, left, mid - 1, key, byYear);
        }
        return BinarySearchRecursive(array, index, mid + 1, right, key, byYear);
    }
    return -1;
}

int BinarySearchIterative(const GoldenBallOwners* array, const int* index, int n, int key, bool byYear) { //false ��� ����� �� id
    int left = 0;
    int right = n - 1;
    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (byYear ? array[index[mid]].year_of_getting_prize == key : array[index[mid]].id == key) {
            return index[mid];
        }
        if (byYear ? array[index[mid]].year_of_getting_prize > key : array[index[mid]].id > key) {
            right = mid - 1;
        }
        else {
            left = mid + 1;
        }
    }
    return -1;
}

void UpdateRecord(GoldenBallOwners* array, int* indexId, int* indexYear, int n, int id) {
    int pos = BinarySearchIterative(array, indexId, n, id, false);
    if (pos != -1) {
        string day;
        string month;
        string year;
        cout << "������� ����� ������ ��� ������ " << id << endl;
        cout << "����� ������:" << endl;
        cin >> array[pos].id;
        cin.ignore();

        cout << "������� ��� ������:" << endl;
        getline(cin, array[pos].firstname);
        cout << "������� ������� ������:" << endl;
        getline(cin, array[pos].lastname);
        cout << "������� ���� �������� ������ � ������� ��.��.����:" << endl;
        cout << "����: ";
        getline(cin, day);
        cout << "����� � ������� ��: ";
        getline(cin, month);
        cout << "���: ";
        getline(cin, year);
        array[pos].date_of_birth = day + "." + month + "." + year; // ��������� ���������� ����
        cout << "������� ��� ��������� �������� ����:" << endl;
        cin >> array[pos].year_of_getting_prize;
        cin.ignore();
        cout << "������� ������ ����������:" << endl;
        getline(cin, array[pos].country);
        cout << "������� ���� � ������� ��������� ������� �������:" << endl;
        getline(cin, array[pos].club);

        // �������������� �������� ����� ���������
        CreateIndex(array, n, indexId, indexYear);
    }
    else {
        cout << "������ �� �������." << endl;
    }
}

void DeleteRecord(GoldenBallOwners* array, int* indexId, int* indexYear, int& n, int id) {
    int pos = BinarySearchIterative(array, indexId, n, id, false);
    if (pos != -1) {
        for (int i = pos; i < n - 1; ++i) {
            array[i] = array[i + 1];
        }
        --n;

        // �������������� �������� ����� ��������
        CreateIndex(array, n, indexId, indexYear);
    }
    else {
        cout << "������ �� �������." << endl;

    }
}


    void inputGoldenBallOwnersFromFile(GoldenBallOwners * array, int& n) {
        const char* filename = "golden_ball_owners.txt"; // ������������� ��� ����� �� ���������
        std::ifstream file(filename);
        if (!file.is_open()) {
            std::cout << "������: �� ������� ������� ���� " << filename << std::endl;
            return;
        }

        // ��������� ���������� ������� � �����
        file >> n;
        std::cout << "����� �������: " << n << std::endl; // ���������� ����
        if (n <= 0) {
            std::cout << "������: ������������ ���������� �������." << std::endl;
            file.close();
            return;
        }

        for (int i = 0; i < n; ++i) {
            if (!(file >> array[i].id >> array[i].firstname >> array[i].lastname >> array[i].date_of_birth
                >> array[i].year_of_getting_prize >> array[i].country >> array[i].club)) {
                std::cout << "������: �� ������� ��������� ������ ��� ������ " << i + 1 << std::endl;
                break; // ��������� ����, ���� �� ������� ��������� ������
            }
        }
        file.close();
    }


