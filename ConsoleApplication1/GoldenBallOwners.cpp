#include "GoldenBallOwners.h"
#include <iostream>
#include <cstring>
#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>
using namespace std;

GoldenBallOwners::GoldenBallOwners() {
    id;
    firstname;
    lastname;
    date_of_birth;
    year_of_getting_prize;
    country;
    club;
    Additional_club_name;

};


void GoldenBallOwners::Show() const
{
    setlocale(LC_ALL, "ru");
    cout << "Номер игрока: " << id << endl;
    cout << "Имя: " << firstname << endl;
    cout << "Фамилия: " << lastname << endl;
    cout << "Дата рождения: " << date_of_birth << endl;
    cout << "Дата получения мяча: " << year_of_getting_prize << endl;
    cout << "Страна: " << country << endl;
    cout << "Клуб: " << club << endl;
};

void GoldenBallOwners::InputPlayers(GoldenBallOwners* ballers, int n) {
    for (int i = 0; i < n; i++)
    {
        string day;
        string month;
        string year;
        cout << "Введите данные игрока " << i + 1 << ":\n";
        cout << "Номер игрока:" << endl;
        cin >> ballers[i].id;
        cin.ignore();

        cout << "Введите имя игрока:" << endl;
        getline(cin, ballers[i].firstname);
        cout << "Введите фамилию игрока:" << endl;
        getline(cin, ballers[i].lastname);
        cout << "Введите дату рождения игрока в формате ДД.ММ.ГГГГ:" << endl;
        cout << "День: ";
        getline(cin, day);
        cout << "Месяц в формате ММ: ";
        getline(cin, month);
        cout << "Год: ";
        getline(cin, year);
        ballers[i].date_of_birth = day + "." + month + "." + year; // Сохраняем корректную дату
        cout << "Введите год получения золотого мяча:" << endl;
        cin >> ballers[i].year_of_getting_prize;
        cin.ignore();
        cout << "Введите страну футболиста:" << endl;
        getline(cin, ballers[i].country);
        cout << "Введите клуб в котором футболист получил награду:" << endl;
        getline(cin, ballers[i].club);
    }
};
void CreateIndex(const GoldenBallOwners* array, int n, int* indexId, int* indexYear) {
    for (int i = 0; i < n; ++i) {
        indexId[i] = i;
        indexYear[i] = i;
    }

    // Сортировка индексов по id пузырьком
    for (int i = 0; i < n - 1; ++i) {
        for (int j = 0; j < n - i - 1; ++j) {
            if (array[indexId[j]].id > array[indexId[j + 1]].id) {
                swap(indexId[j], indexId[j + 1]);
            }
        }
    }
    // Сортировка индексов по году получения приза методом вставок
    for (int i = 1; i < n; ++i) {
        int keyIndex = indexYear[i];
        int j = i - 1;

        // Перемещаем элементы, которые больше, чем текущий элемент, на одну позицию вперед
        while (j >= 0 && array[indexYear[j]].year_of_getting_prize < array[keyIndex].year_of_getting_prize) {
            indexYear[j + 1] = indexYear[j];
            j = j - 1;
        }
        indexYear[j + 1] = keyIndex;
    }
    
}

void PrintByIndex(const GoldenBallOwners* array, const int* index, int n) {
    for (int i = 0; i < n; ++i) {
        array[index[i]].Show();
        cout << "------------------------" << endl;
        cout << endl;
    }
}

int BinarySearchRecursive(const GoldenBallOwners* array, const int* index, int left, int right, int year) {
    if (right >= left) {
        int mid = left + (right - left) / 2;

        if (array[index[mid]].year_of_getting_prize == year) {
            return index[mid];
        }

        if (array[index[mid]].year_of_getting_prize < year) {
            return BinarySearchRecursive(array, index, left, mid - 1, year);
        }
        else {
            return BinarySearchRecursive(array, index, mid + 1, right, year);
        }
    }
    return -1;
    
    
    
    
 
}

int BinarySearchIterative(const GoldenBallOwners* array, const int* index, int n, int key, bool byYear) { //false Это поиск по id
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
        cout << "Введите новые данные для игрока " << id << endl;
        cout << "Номер игрока:" << endl;
        cin >> array[pos].id;
        cin.ignore();

        cout << "Введите имя игрока:" << endl;
        getline(cin, array[pos].firstname);
        cout << "Введите фамилию игрока:" << endl;
        getline(cin, array[pos].lastname);
        cout << "Введите дату рождения игрока в формате ДД.ММ.ГГГГ:" << endl;
        cout << "День: ";
        getline(cin, day);
        cout << "Месяц в формате ММ: ";
        getline(cin, month);
        cout << "Год: ";
        getline(cin, year);
        array[pos].date_of_birth = day + "." + month + "." + year; // Сохраняем корректную дату
        cout << "Введите год получения золотого мяча:" << endl;
        cin >> array[pos].year_of_getting_prize;
        cin.ignore();
        cout << "Введите страну футболиста:" << endl;
        getline(cin, array[pos].country);
        cout << "Введите клуб в котором футболист получил награду:" << endl;
        getline(cin, array[pos].club);

        // Пересортировка индексов после изменения
        CreateIndex(array, n, indexId, indexYear);
    }
    else {
        cout << "Запись не найдена." << endl;
    }
}

void DeleteRecord(GoldenBallOwners* array, int* indexId, int* indexYear, int& n, int id) {
    int pos = BinarySearchIterative(array, indexId, n, id, false);
    if (pos != -1) {
        for (int i = pos; i < n - 1; ++i) {
            array[i] = array[i + 1];
        }
        --n;

        // Пересортировка индексов после удаления
        CreateIndex(array, n, indexId, indexYear);
    }
    else {
        cout << "Запись не найдена." << endl;

    }
}



void inputGoldenBallOwnersFromFile(GoldenBallOwners* array) {
    //string ballers = "golden_ball_owners.txt"; // Устанавливаем имя файла по умолчанию
    ifstream file("golden_ball_owners1.txt");
    if (!file.is_open()) {
        cout << "Ошибка: Не удалось открыть файл " << endl;
        return;
    }

        //Считываем количество записей в файле
        int n;
        file >> n;
        std::cout << "Файл считан. Число записей: " << n << std::endl; // Отладочный вывод
        if (n <= 0) {
            std::cout << "Ошибка: Некорректное количество записей." << std::endl;
            file.close();
            return;
        }

        for (int i = 0; i < n; ++i) {
            if (!(file >> array[i].id >> array[i].firstname >> array[i].lastname >> array[i].date_of_birth
                >> array[i].year_of_getting_prize >> array[i].country >> array[i].club >> array[i].Additional_club_name)) {
                cout << "Ошибка: Не удалось загрузить данные для записи " << i + 1 << endl;
                break; // Прерываем цикл, если не удалось прочитать данные
            }
        }
        file.close();
    }


