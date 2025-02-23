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
    TreeNode* o = y->left;

    y->left = z;
    z->right = o;

    z->height = 1 + max(getHeight(z->left), getHeight(z->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

    return y;
}


TreeNode* rotateRight(TreeNode* z) {
    TreeNode* y = z->left;
    TreeNode* p = y->right;

    y->right = z;
    z->left = p;

    z->height = 1 + max(getHeight(z->left), getHeight(z->right));
    y->height = 1 + max(getHeight(y->left), getHeight(y->right));

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
        return root; // �������� ����� �� �����������
    }

    root->height = 1 + max(getHeight(root->left), getHeight(root->right));

    int balance = getBalanceFactor(root);

    // ����� ����� ������
    if (balance > 1 && key < root->left->key) {
        return rotateRight(root);
    }

    // ������ ������ ������
    if (balance < -1 && key > root->right->key) {
        return rotateLeft(root);
    }

    // ����� ������ ������
    if (balance > 1 && key > root->left->key) {
        root->left = rotateLeft(root->left);
        return rotateRight(root);
    }

    // ������ ����� ������
    if (balance < -1 && key < root->right->key) {
        root->right = rotateRight(root->right);
        return rotateLeft(root);
    }

    return root;
}
/// <summary>
/// ����������� �����
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
    return nullptr; // ������ �� �������

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
        cout << "������ �� �������." << endl;
    }
}
void PrintTree(TreeNode* root, const GoldenBallOwners* array, int& n) {
    for (int i = 0; i < n; i++) {
        int index = i;
        array[root->index].Show();
    }
}

void DeleteRecordByIndexTree(GoldenBallOwners* array, TreeNode*& rootById, int& n, int id, TreeNode*& rootByYear) {
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

        rootById = DeleteNode(rootById, id);

        //�������������� �������� ����� ��������
        rootById = CreateIndexTree(array, n, false);    // ������ �� id
        rootByYear = CreateIndexTree(array, n, true);   // ������ �� ����
    }
    else {
        cout << "������ �� �������." << endl;
    }
}
void UpdateIndexByTree(GoldenBallOwners* array, TreeNode*& rootById, TreeNode*& rootByYear, int& n, int id) {
    // ����� ������� ������ �� ID
    TreeNode* node = SearchNodeRecursive(rootById, id);
    if (node != nullptr) {
        int pos = node->index;
        cout << "������� ����� ������:" << endl;
        cout << "����� ���: ";
        cin.ignore();
        getline(cin, array[pos].firstname);
        cout << "����� ��� ��������� �����: ";
        cin >> array[pos].year_of_getting_prize;

        // �������� ������ ����� �� ��������
        rootById = DeleteNode(rootById, id);
        rootByYear = DeleteNode(rootByYear, array[pos].year_of_getting_prize);

        // ������� ����� ����� � �������
        rootById = InsertNode(rootById, array[pos].id, pos);
        rootByYear = InsertNode(rootByYear, array[pos].year_of_getting_prize, pos);
    }
    else {
        cout << "������ �� �������." << endl;
    }
}