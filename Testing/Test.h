#pragma once
#include <ctime>
#include <vector>
#include <algorithm>
#include "Question.h"
#include "Menu.h"
#include "Funcs.h"

class Question;

class Test
{
	// ������ �������� � ��������
	std::vector < Question > questions;

	// ��� ���������� �����
	std::string testName;

	// �������� ��� ������� ��������
	struct Pred
	{
		Pred(void)
		{
			srand(static_cast < unsigned int > ( time(nullptr) ) );
		}
		int operator()(const int &i) const throw()
		{
			return rand() % i;
		}
	};

	// ������ ���� ��� �������������� �����
	enum ForEdit { ADD = 1, DELETE, EXIT };

	// ��������� ����������� �����
	size_t points;

public:

	// ����������� �� ���������
	Test() = delete;

	// ����������� � ���������� ��� ������������� 
	Test(const std::string &);
	
	// �������� ��� ������
	void Do(const Menu::Choice &);

	// ��������� ������ ������
private:

	// �������� ������ �� �������
	void InitAll(std::string &);

	// ������ �����
	void Start(void);

	// ����� �������� ��������������
	ForEdit EditChoice(void);

	// ���������� ��������������
	void Edit(const ForEdit &);

	// ����������� �����
	void Show(void) const throw();

	// ����� �� ������������ �� ������ �����
	size_t UserInputAnswer(const size_t &);

	// ���������� ���-�� ���������� �������
	const size_t &GetPoints();

	// ���������� �������
	void AddQuestion(void);

	// ����� ������������� ������� ��� ��������
	void DeleteQuestion(void);

	// �������� ������� �� ������� � ����������
	void Delete(const Question &);

	// ���������� ����������� � �����
	void Saving(void);

};