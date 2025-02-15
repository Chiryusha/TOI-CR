#include <iostream>;
#include <windows.h>
#include <string>
#include "Menu.h"
#include "GoldenBallOwners.h"
#include "LinkedList.h"
#include "TreeNode.h"

using namespace std;


int main()
{
    SetConsoleCP(1251);// Устанавливаем кодировку ввода консоли
    SetConsoleOutputCP(1251);
    setlocale(LC_ALL, "Russian");
    int choice;
    Menu menu;
    const int size = 10;
    GoldenBallOwners array[size];
    int IndexId[size];
    int IndexYear[size];
    TreeNode* rootById = nullptr; // Объявление здесь
    TreeNode* rootByYear = nullptr; // Объявление здесь

    bool Checking = true; // Переменная для проверки ввода
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
            /*int IndexId[size];
            int IndexYear[size];*/
            array[0].InputPlayers(array, n);
            CreateIndex(array, n, IndexId, IndexYear);
            cout << " " << endl;
            do {
                cout << "Выберите предложенную функцию" << endl;
                menu.Show_Second_Menu();
                cin >> ans;
                switch (ans)
                {
                case 1:
                    cout << "Сортировка по ID:" << endl;
                    PrintByIndex(array, IndexId, n);
                    cout << "------------------------" << endl;

                    cout << "Сортировка по году получения приза:" << endl;
                    PrintByIndex(array, IndexYear, n);
                    cout << "------------------------" << endl;
                    break;
                case 2:
                    int searchkey;
                    int result;
                    cout << "Введите год получения награды для поиска:";
                    cin >> searchkey;
                    //result = BinarySearchRecursive(array, IndexYear, left, right, searchkey, true);
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
                    // Редактирование записи
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

                    }
                    break;
                }
            } while (ans != 7);
            break;

        case 2:
            cout << "Сортировка с использованием бинарных деревьев" << endl;
            int p;
            cout << "Введите количество обладателей золотого мяча:" << endl;
            cin >> p;
            cout << "ХУЙ" << endl;
            array[0].InputPlayers(array, p);

            // Создание индексов в виде бинарного дерева
            rootById = CreateIndexTree(array, p, false);
            rootByYear = CreateIndexTree(array, p, true);

            // Вывод данных по возрастанию значений ключевого атрибута
            cout << "Сортировка по ID:" << endl;
            PrintByIndexTree(rootById, array);
            cout << "Сортировка по году получения приза:" << endl;
            PrintByIndexTree(rootByYear, array);

            // Поиск элемента по значению ключевого атрибута
            int searchKey1;
            cout << "Введите ID для поиска: ";
            cin >> searchKey1;
            SearchByKey(array, rootById, searchKey1);

            // Редактирование записи
            int updateId1;
            cout << "Введите ID для редактирования: ";
            cin >> updateId1;
            UpdateIndexByTree(array, rootById, rootByYear, p, updateId1);

            // Удаление записи
            int deleteId1;
            cout << "Введите ID для удаления: ";
            cin >> deleteId1;
            DeleteRecordByIndexTree(array, rootById, p, deleteId1);

            // Освобождение памяти, выделенной для бинарных деревьев
            // Здесь можно добавить функцию для
            break;
        case 3:
            LinkedList list;
            int k;
            cout << "Введите количество обладателей золотого мяча:" << endl;
            cin >> k;

            for (int i = 0; i < k; ++i) {
                GoldenBallOwners player;
                player.InputPlayers(&player, 1);
                list.Insert(player);
            }

            // Вывод записей из списка
            cout << "Записи из списка в порядке их ввода:" << endl;
            list.Print();

            // Вывод записей из списка в порядке возрастания ID
            cout << "Записи из списка в порядке возрастания ID:" << endl;
            list.PrintSortedById();
            break;
        }
    }while (choice != 4);
    return 0;
}
