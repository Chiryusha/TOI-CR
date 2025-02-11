#include "TreeNode.h"
#include <iostream>
#include "GoldenBallOwners.h"
#include <string>

TreeNode::TreeNode(int k, int i) : key(k), index(i), left(nullptr), right(nullptr) {}
TreeNode* RootById = nullptr;
TreeNode* RootByYear = nullptr;

TreeNode* InsertNode(TreeNode* root, int key, int index) {
    if (root == nullptr) {
        return new TreeNode(key, index);
    }

    if (key < root->key) {
        root->left = InsertNode(root->left, key, index);
    }
    else if (key > root->key) {
        root->right = InsertNode(root->right, key, index);
    }
    return root;
}

TreeNode* SearchNode(TreeNode* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return SearchNode(root->left, key);
    }
    else {
        return SearchNode(root->right, key);
    }
}

TreeNode* FindMin(TreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

TreeNode* DeleteNode(TreeNode* root, int key) {
    if (root == nullptr) {
        return root;
    }

    if (key < root->key) {
        root->left = DeleteNode(root->left, key);
    }
    else if (key > root->key) {
        root->right = DeleteNode(root->right, key);
    }
    else {
        if (root->left == nullptr) {
            TreeNode* temp = root->right;
            delete root;
            return temp;
        }
        else if (root->right == nullptr) {
            TreeNode* temp = root->left;
            delete root;
            return temp;
        }

        TreeNode* temp = FindMin(root->right);
        root->key = temp->key;
        root->index = temp->index;
        root->right = DeleteNode(root->right, temp->key);
    }
    return root;
}

TreeNode* CreateIndexTree(const GoldenBallOwners* array, int n, bool byYear) {
    TreeNode* root = nullptr;
    for (int i = 0; i < n; ++i) {
        int key = byYear ? array[i].year_of_getting_prize : array[i].id;
        root = InsertNode(root, key, i);
    }
    return root;
}

void InOrderTraversal(TreeNode* root, const GoldenBallOwners* array) {
    if (root != nullptr) {
        InOrderTraversal(root->left, array);
        array[root->index].Show();
        cout << endl;
        InOrderTraversal(root->right, array);
    }
}

void PrintByIndexTree(TreeNode* root, const GoldenBallOwners* array) {
    InOrderTraversal(root, array);
}

void SearchByKey(const GoldenBallOwners* array, TreeNode* root, int key) {
    TreeNode* result = SearchNode(root, key);
    if (result != nullptr) {
        array[result->index].Show();
    }
    else {
        cout << "Запись не найдена." << endl;
    }
}

void DeleteRecordByIndexTree(GoldenBallOwners* array, TreeNode*& root, int& n, int id) {
    int pos = -1;
    for (int i = 0; i < n; ++i) {
        if (array[i].id == id) {
            pos = i;
            break;
        }
    }

    if (pos != -1) {
        for (int i = pos; i < n - 1; ++i) {
            array[i] = array[i + 1];
        }
        --n;

        root = DeleteNode(root, id);

        // Пересортировка индексов после удаления
        //CreateIndex(array, n, IndexId, IndexYear);
    }
    else {
        cout << "Запись не найдена." << endl;
    }
}
void UpdateIndexByTree(GoldenBallOwners* array, TreeNode*& rootById, TreeNode*& rootByYear, int& n, int id) {
    // Поиск позиции записи по ID
    TreeNode* node = SearchNode(rootById, id);
    if (node != nullptr) {
        int pos = node->index;
        cout << "Введите новые данные:" << endl;
        cout << "Новое имя: ";
        cin.ignore();
        getline(cin, array[pos].firstname);
        cout << "Новый год получения приза: ";
        cin >> array[pos].year_of_getting_prize;

        // Удаление старых узлов из деревьев
        rootById = DeleteNode(rootById, id);
        rootByYear = DeleteNode(rootByYear, array[pos].year_of_getting_prize);

        // Вставка новых узлов в деревья
        rootById = InsertNode(rootById, array[pos].id, pos);
        rootByYear = InsertNode(rootByYear, array[pos].year_of_getting_prize, pos);
    }
    else {
        cout << "Запись не найдена." << endl;
    }
}