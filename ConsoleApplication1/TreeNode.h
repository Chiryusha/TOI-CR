#pragma once
#include "iostream"
#include "string"
#include "GoldenBallOwners.h"

using namespace std;

struct TreeNode
{
public:
	int key; // �������� �������� (����� ������ ��� ��� ��������� �����)
	int index; // ������ � ������� array
	int height;// ������ ����
	TreeNode* left; // ����� �������
	TreeNode* right; // ������ �������
	TreeNode(int k, int i);
};
int getHeight(TreeNode* node);
int getBalanceFactor(TreeNode* node);
TreeNode* rotateRight(TreeNode* y);
TreeNode* rotateLeft(TreeNode* x);
	// ��������� ������� ��� ������ � �������� �������
	TreeNode* InsertNode(TreeNode* root, int key, int index);
	TreeNode* SearchNodeRecursive(TreeNode* root, int key);
	TreeNode* FindMin(TreeNode* node);
	TreeNode* DeleteNode(TreeNode* root, int key);
	TreeNode* CreateIndexTree(const GoldenBallOwners* array, int n, bool byYear);
	void InOrderTraversal(TreeNode* root, const GoldenBallOwners* array);
	void ReverseInOrderTraversal(TreeNode* root, const GoldenBallOwners* array);
	void PrintByIdTree(TreeNode* root, const GoldenBallOwners* array);
	void PrintByYearTree(TreeNode* root, const GoldenBallOwners* array);
	void SearchByKey(const GoldenBallOwners* array, TreeNode* root, int key);
	void UpdateIndexByTree(GoldenBallOwners* array, TreeNode*& rootById, TreeNode*& rootByYear, int& n, int year );
	void DeleteRecordByIndexTree(GoldenBallOwners* array, TreeNode*& root, int& n, int id);
	TreeNode* SearchNodeIterative(TreeNode* root, int year);