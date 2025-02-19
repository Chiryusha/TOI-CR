#include "TreeNode.h"
#include <iostream>
#include "GoldenBallOwners.h"
#include <string>

TreeNode::TreeNode(int k, int i) : key(k), index(i), height(1), left(nullptr), right(nullptr) {}
TreeNode* RootById = nullptr;
TreeNode* RootByYear = nullptr;



int getHeight(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return node->height;
}


int getBalanceFactor(TreeNode* node) {
    if (node == nullptr) {
        return 0;
    }
    return getHeight(node->left) - getHeight(node->right);
}

TreeNode* rotateLeft(TreeNode* z) {
    TreeNode* y = z->right;
    TreeNode* T2 = y->left;

    y->left = z;
    z->right = T2;

    z->height = 1 + std::max(getHeight(z->left), getHeight(z->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y;
}


TreeNode* rotateRight(TreeNode* z) {
    TreeNode* y = z->left;
    TreeNode* T3 = y->right;

    y->right = z;
    z->left = T3;

    z->height = 1 + std::max(getHeight(z->left), getHeight(z->right));
    y->height = 1 + std::max(getHeight(y->left), getHeight(y->right));

    return y;
}

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
    else {
        return root; // Дубликат ключа не добавляется
    }

    root->height = 1 + std::max(getHeight(root->left), getHeight(root->right));

    int balance = getBalanceFactor(root);

    // Левый левый случай
    if (balance > 1 && key < root->left->key) {
        return rotateRight(root);
    }

    // Правый правый случай
    if (balance < -1 && key > root->right->key) {
        return rotateLeft(root);
    }

    // Левый правый случай
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // Правый левый случай
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}
/// <summary>
/// Рекурсивный поиск
/// </summary>
/// <param name="root"></param>
/// <param name="key"></param>
/// <returns></returns>
TreeNode* SearchNodeRecursive(TreeNode* root, int key) {
    if (root == nullptr || root->key == key) {
        return root;
    }

    if (key < root->key) {
        return SearchNodeRecursive(root->left, key);
    }
    else {
        return SearchNodeRecursive(root->right, key);
    }
}

TreeNode* SearchNodeIterative(TreeNode* root, int year) {
    while (root != nullptr) {
        if (root->key == year) {
            return root;
        }
        else if (year < root->key) {
            root = root->left;
        }
        else {
            root = root->right;
        }
    }
    return nullptr; // Запись не найдена

}

TreeNode* FindMin(TreeNode* node) {
    while (node->left != nullptr) {
        node = node->left;
    }
    return node;
}

/*TreeNode* DeleteNode(TreeNode* root, int key) {
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
}*/



TreeNode* DeleteNode(TreeNode* root, int key) {
    if (root == nullptr) return root;

    if (key < root->key)
        root->left = DeleteNode(root->left, key);
    else if (key > root->key)
        root->right = DeleteNode(root->right, key);
    else {
        if ((root->left == nullptr) || (root->right == nullptr)) {
            TreeNode* temp = root->left ? root->left : root->right;

            if (temp == nullptr) {
                temp = root;
                root = nullptr;
            }
            else
                *root = *temp;
            delete temp;
        }
        else {
            TreeNode* temp = FindMin(root->right);
            root->key = temp->key;
            root->right = DeleteNode(root->right, temp->key);
        }
    }

    if (root == nullptr) return root;

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalanceFactor(root);

    if (balance > 1 && getBalanceFactor(root->left) >= 0)
        return rotateRight(root);

    if (balance > 1 && getBalanceFactor(root->left) < 0) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    if (balance < -1 && getBalanceFactor(root->right) <= 0)
        return rotateLeft(root);

    if (balance < -1 && getBalanceFactor(root->right) > 0) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
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
        cout << "-------------------";
        cout << endl;
        InOrderTraversal(root->right, array);
    }
}


void ReverseInOrderTraversal(TreeNode* root, const GoldenBallOwners* array) {
    if (root != nullptr) {
        ReverseInOrderTraversal(root->right, array);
        array[root->index].Show();
        cout << "-------------------";
        cout << endl;
        ReverseInOrderTraversal(root->left, array);
    }
}

void PrintByIdTree(TreeNode* root, const GoldenBallOwners* array) {
    InOrderTraversal(root, array);
}
void PrintByYearTree(TreeNode* root, const GoldenBallOwners* array) {
    ReverseInOrderTraversal(root, array);
}

void SearchByKey(const GoldenBallOwners* array, TreeNode* root, int key) {
    TreeNode* result = SearchNodeRecursive(root, key);
    if (result != nullptr) {
        array[result->index].Show();
    }
    else {
        cout << "Запись не найдена." << endl;
    }
}
void PrintTree(TreeNode* root, const GoldenBallOwners* array, int& n) {
    for (int i = 0; i < n; i++) {
        int index = i;
        array[root->index].Show();
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

        //Пересортировка индексов после удаления
        //CreateIndex(array, n, IndexId, IndexYear);
    }
    else {
        cout << "Запись не найдена." << endl;
    }
}
void UpdateIndexByTree(GoldenBallOwners* array, TreeNode*& rootById, TreeNode*& rootByYear, int& n, int id) {
    // Поиск позиции записи по ID
    TreeNode* node = SearchNodeRecursive(rootById, id);
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