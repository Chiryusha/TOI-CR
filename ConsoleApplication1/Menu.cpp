#include "Menu.h"
#include <iostream>

using namespace std;

void Menu::Show() {
    cout << "�������� ����� ����:" << endl;
    cout << "1) ������� 1" << endl;
    cout << "2) ������� 2" << endl;
    cout << "3) ������� 3" << endl;
    cout << "4) �����" << endl;
}

void Menu::Show_Second_Menu() {
    cout << "�������� ������������ �������" << endl;
    cout << "1) ����� ��������������� ������ �� �������� �����" << endl;
    cout << "2) ����� ��������� �� ��������� �������� ��������� � �������������� ��������� ������ (����������� ��������)" << endl;
    cout << "3) ����� ��������� �� ��������� �������� ��������� � �������������� ��������� ������ (������������ ��������)" << endl;
    cout << "4) �������������� ������� � �������" << endl;
    cout << "5) �������� ������ �������" << endl;
    cout << "6) ����� ������� ��/����� ��������������" << endl;
    cout << "7) �����" << endl;
}

void Menu::Show_Third_Menu() {
    cout << "�������� ������������ �������" << endl;
    cout << "1) ����� ��������������� ������ �� �������� �����" << endl;
    cout << "2) ������ ��������� �� ��������� ��������� �������� � �������������� ��������� ������(�����������)"<<endl;
    cout << "3) ����� ��������� �� ��������� ��������� �������� � �������������� ��������� ������(������������)"<<endl;
    cout << "4) �������� ������ � �������� ��������� ��������� �������� �� ������� �"
        << "��������������� ���������� �������(��������� ������)" << endl;
    cout << "5) ����� ������� ����� ���������" << endl;
    cout << "6) �����" << endl;
}

void Menu::Show_Fourth_Menu()
{
    cout << "�������� ������������ �������" << endl;
    cout << "1) ����� ����� ������� " << endl;
    cout << "2) �������� (�����) ������� �� ��������� ������ � ������� �� �����" << endl;
    cout << "3) �������� (�����) ������� �� ��������� ������ � ������� �����������/��������"
        << "�������� ��������� ��� ���������� ���������" << endl;
    cout << "4) ����� � ����� ������/������� � �������� ��������� ��������, �� �������� ���������"
        << "����������" << endl;
    cout << "5) �������� ������" << endl;
    cout << "6) �����" << endl;
}
void Menu::Show_Choice()
{
    cout << "�������� ������ ��������� ������ �� ����������� �������� ����: " << endl;;
    cout << "1) ������� ������ �� �����" << endl;;
    cout << "2) ���� ������ �������" << endl;;
    cout << "3) �����" << endl;;
}
