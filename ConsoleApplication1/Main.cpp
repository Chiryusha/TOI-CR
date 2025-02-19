﻿#include <iostream>;
#include <windows.h>
#include <string>
#include "Menu.h"
#include "GoldenBallOwners.h"
#include "LinkedList.h"
#include "TreeNode.h"
#include <algorithm>


using namespace std;


int main()
{
    SetConsoleCP(1251);// Устанавливаем кодировку ввода консоли
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    int choice;
    Menu menu;
    const int size = 10;
    int n = size; // вспомогательная
    GoldenBallOwners array[size];
   
    int IndexId[size];
    int IndexYear[size];
    TreeNode* rootById = nullptr; // Объявление здесь
    TreeNode* rootByYear = nullptr; // Объявление здесь
    TreeNode* result = nullptr;

    int choice1;
    do {
        menu.Show_Choice();
        cin >> choice1;
        switch (choice1) {
        case 1:
            inputGoldenBallOwnersFromFile(array);
            do {
                menu.Show();
                cin >> choice;
                CreateIndex(array, n, IndexId, IndexYear);
                switch (choice) {
                case 1:
                    int ans;
                    do {
                        menu.Show_Second_Menu();
                        cin >> ans;
                        switch (ans)
                        {
                        case 1:
                            cout << "Сортировка по ID:" << endl;
                            cout << "------------------------" << endl;
                            PrintByIndex(array, IndexId, size);

                            cout << "Сортировка по году получения приза:" << endl;
                            cout << "------------------------" << endl;
                            PrintByIndex(array, IndexYear, size);
                            break;
                        case 2:
                            int searchkey;
                            int result;
                            cout << "Введите год получения награды для поиска: ";
                            cin >> searchkey;
                            result = BinarySearchRecursive(array, IndexYear, 0, size-1, searchkey);
                            if (result != -1) {
                                cout << "Найдено:" << endl;
                                array[result].Show();
                            }
                            else {
                                cout << "Не найдено." << endl;
                            }
                            break;
                        case 3:
                            int searchKey1;
                            int result1;
                            cout << "Введите ID для поиска: ";
                            cin >> searchKey1;
                            result1 = BinarySearchIterative(array, IndexId, size, searchKey1, false);//
                            if (result1 != -1) {
                                cout << "Найдено:" << endl;
                                array[result1].Show();
                            }
                            else {
                                cout << "Не найдено." << endl;
                            }
                            break;
                        case 4:
                            // Редактирование записи
                            int updateId;
                            cout << "Введите ID для редактирования: ";
                            cin >> updateId;
                            UpdateRecord(array, IndexId, IndexYear, size, updateId);
                            break;
                            case 5:
                                int deleteId;
                                cout << "Введите ID для удаления: ";
                                cin >> deleteId;
                                DeleteRecord(array, IndexId, IndexYear, n, deleteId);
                                break;
                        case 6:
                            for (int i = 0; i < n; i++) {
                                array[i].Show();
                                cout << "----------------------" << endl;

                            }
                            break;
                        }
                    } while (ans != 7);

                    break;

                case 2:
                    int point;
                    cout << "Сортировка и поиск данных в массивах с использованием бинарного дерева" << endl;
                    // Создание индексов в виде бинарного дерева
                    rootById = CreateIndexTree(array, n, false);
                    rootByYear = CreateIndexTree(array, n, true);
                    do {
                        menu.Show_Third_Menu();
                        cin >> point;
                        switch (point) {
                        case 1:
                            // Вывод данных по возрастанию значений ключевого атрибута
                            cout << "Сортировка по ID:" << endl;
                            cout << "-------------------" << endl;
                            PrintByIdTree(rootById, array);
                            cout << " " << endl;
                            cout << " " << endl;


                            cout << "Сортировка по году получения приза:" << endl;
                            cout << "-------------------" << endl;
                            PrintByYearTree(rootByYear, array);
                            break;
                        case 2:
                            // Поиск элемента по значению ключевого атрибута
                            int searchKey1;
                            cout << "Введите ID для поиска: ";
                            cin >> searchKey1;
                            result = SearchNodeRecursive(rootById, searchKey1); 
                            if (result != nullptr) {
                                array[result->index].Show();
                            }
                            else {
                                cout << "Запись не найдена." << endl;
                            }
                            break;
                        case 3:
                            // Ре
                            int SearchKey2;
                            cout << "Введите год получения награды: ";
                            cin >> SearchKey2;
                            result = SearchNodeIterative(rootByYear, SearchKey2);
                            if (result != nullptr) {
                                array[result->index].Show();
                            }
                            else {
                                cout << "Запись не найдена." << endl;
                            }
                            break;
                        case 4:
                            // Удаление записи
                            int deleteId1;
                            cout << "Введите ID для удаления: ";
                            cin >> deleteId1;
                            DeleteRecordByIndexTree(array, rootById, n, deleteId1);
                            break;
                        case 5:
                            for (int i = 0; i < n; i++) {
                                array[i].Show();
                                cout << "-----------------" << endl;;
                            }
                            break;
                        }
                    } while (point != 6);
                    break;
                }
            } while (choice != 4);

            break;
        case 2: // Ручной ввод
            do {
                menu.Show();
                cin >> choice;
                switch (choice) {
                case 1:
                    int n;
                    int ans;
                    std::cout << "Введите количество обладетелей золотого мяча:" << endl;
                    cin >> n;
                    if (n > 10) {
                        cout << "Превышено максимальное количество обладателей." << endl;
                        return 0;
                    }
                    InputPlayers(array, n);
                    CreateIndex(array, n, IndexId, IndexYear);
                    do {
                        menu.Show_Second_Menu();
                        cin >> ans;
                        switch (ans)
                        {
                        case 1:
                            cout << "Сортировка по ID:" << endl;
                            cout << "------------------------" << endl;
                            PrintByIndex(array, IndexId, n);

                            cout << "Сортировка по году получения приза:" << endl;
                            cout << "------------------------" << endl;
                            PrintByIndex(array, IndexYear, n);
                            break;
                        case 2:
                            int searchkey;
                            int result;
                            cout << "Введите год получения награды для поиска:";
                            cin >> searchkey;
                            result = BinarySearchRecursive(array, IndexYear, 0, n - 1, searchkey);
                            if (result != -1) {
                                cout << "Найдено:" << endl;
                                array[result].Show();
                            }
                            else {
                                cout << "Не найдено." << endl;
                            }
                            break;
                        case 3:
                            int searchKey1;
                            int result1;
                            cout << "Введите ID для поиска: ";
                            cin >> searchKey1;
                            result1 = BinarySearchIterative(array, IndexId, n, searchKey1, false);//
                            if (result1 != -1) {
                                cout << "Найдено:" << endl;
                                array[result1].Show();
                            }
                            else {
                                cout << "Не найдено." << endl;
                            }
                            break;
                        case 4:
                            int updateId;
                            cout << "Введите ID для редактирования: ";
                            cin >> updateId;
                            UpdateRecord(array, IndexId, IndexYear, n, updateId);
                            break;
                        case 5:
                            int deleteId;
                            cout << "Введите ID для удаления: ";
                            cin >> deleteId;
                            DeleteRecord(array, IndexId, IndexYear, n, deleteId);
                            break;
                        case 6:
                            for (int i = 0; i < n; i++) {
                                array[i].Show();
                                cout << "----------------------" << endl;

                            }
                            break;
                        }
                    } while (ans != 7);

                case 2:
                    int point;
                    cout << "Сортировка и поиск данных в массивах с использованием бинарного дерева" << endl;
                    int p;
                    cout << "Введите количество обладателей золотого мяча:" << endl;
                    cin >> p;
                    InputPlayers(array, p);

                    // Создание индексов в виде бинарного дерева
                    rootById = CreateIndexTree(array, p, false);
                    rootByYear = CreateIndexTree(array, p, true);
                    do {
                        menu.Show_Third_Menu();
                        cin >> point;
                        switch (point) {
                        case 1:
                            // Вывод данных по возрастанию значений ключевого атрибута
                            cout << "Сортировка по ID:" << endl;
                            cout << "-------------------" <<endl;
                            PrintByIdTree(rootById, array);
                            cout << " ";
                            cout << "Сортировка по году получения приза:" << endl;
                            cout << "-----------------" << endl;
                            PrintByYearTree(rootByYear, array);
                            break;
                        case 2:
                            // Поиск элемента по значению ключевого атрибута
                            int searchKey1;
                            cout << "Введите ID для поиска: ";
                            cin >> searchKey1;
                            result = SearchNodeRecursive(rootById, searchKey1);
                            if (result != nullptr) {
                                array[result->index].Show();
                            }
                            else {
                                cout << "Запись не найдена." << endl;
                            }
                            break;
                        case 3:

                            break;
                        case 4:
                            // Удаление записи
                            int deleteId1;
                            cout << "Введите ID для удаления: ";
                            cin >> deleteId1;
                            DeleteRecordByIndexTree(array, rootById, p, deleteId1);
                            break;
                        case 5:
                            for (int i = 0; i < p; i++) {
                                array[i].Show();
                                cout << "-----------------" << endl;;
                            }
                            break;
                        }

                    } while (point != 6);
                    break;
                case 3:
                    LinkedList list;
                    int k;
                    cout << "Введите количество обладателей золотого мяча:" << endl;
                    cin >> k;

                    for (int i = 0; i < k; ++i) {
                        GoldenBallOwners player;
                        InputPlayers(&player, 1);
                        list.Insert(player);
                    }

                    // Вывод записей из списка
                    cout << "Записи из списка в порядке их ввода:" << endl;
                    list.Print();

                    // Вывод записей из списка в порядке возрастания ID
                    cout << "Записи из списка в порядке возрастания ID:" << endl;
                    list.PrintSortedById();
                    break;
                    break;
                }
            } while (choice != 4);

            break;
        }

    } while (choice1 != 3);
    return 0;
}
