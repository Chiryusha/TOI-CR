#pragma once
#include "iostream"
#include "string"
#include "GoldenBallOwners.h"

using namespace std;

struct TreeNode
{
public:

	int key; // �������� �������� (id ��� ��� ��������� �����)
	int index; // ������ � ������� array
	TreeNode* left; // ����� �������
	TreeNode* right; // ������ �������

	TreeNode(int k, int i);
};

	// ��������� ������� ��� ������ � �������� �������
	TreeNode* InsertNode(TreeNode* root, int key, int index);
	TreeNode* SearchNode(TreeNode* root, int key);
	TreeNode* FindMin(TreeNode* node);
	TreeNode* DeleteNode(TreeNode* root, int key);
	TreeNode* CreateIndexTree(const GoldenBallOwners* array, int n, bool byYear);
	void InOrderTraversal(TreeNode* root, const GoldenBallOwners* array);
	void PrintByIndexTree(TreeNode* root, const GoldenBallOwners* array);
	void SearchByKey(const GoldenBallOwners* array, TreeNode* root, int key);
	void UpdateIndexByTree(GoldenBallOwners* array, TreeNode*& rootById, TreeNode*& rootByYear, int& n, int year );
	void DeleteRecordByIndexTree(GoldenBallOwners* array, TreeNode*& root, int& n, int id);