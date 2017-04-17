#pragma once
#include <iostream>
#include <vector>
#include <string>
#include "Funcs.h"

class Menu
{
	// ������, ��� �������� �������� ������
	std::vector < std::string > vTestNames;

public:
	// ������ ����
	enum Choice { PASS = 1, EDIT, SHOW, EXIT };

	// ����������� �� ���������, ������������� ������� ����������
	Menu(void);
	
	// ���������������� ���� � ������� ����
	Choice MainChoice(void) const;

	// ���������������� ���� (����� �����)
	const std::string& TestChoice(void) const;
	
	// ����������� ������� ����
	void Edit(void) const throw();

private:
	
	// ����� �� ����� ������� �������� ����
	void Main(void) const throw();

	// ����� �� ����� ������� ����������� ����
	void TestList(void) const throw();
	
	// ��������� ����� "����" �� �������, � ����������� �� ���-�� ������	
	void OutputWord(const size_t &i) const throw();
};