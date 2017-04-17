#pragma once
#include "Test.h"

class Question
{
	std::string strTextQuestion;			// ����� �������
	std::vector <std::string> vecAnswers;	// �������� �������
	std::string strRightAnswer;				// ���������� �����

	// �������� ��� ���������� ������ �������
	struct Pred
	{
		Pred(void)
		{
			srand( static_cast < unsigned int > ( time(nullptr) ) );
		}
		int operator()(const int &i) const throw()
		{
			return rand() % i;
		}
	};
public:
	// ����������� � ���������� (������������� ����� �������)
	Question(std::string &);

	// ����� ������� �� �����
	friend std::ostream & operator << (std::ostream &, const Question &);

	// ������
	const std::string & GetTextQustion(void) const throw();

	// ���������� �����
	const std::string & GetRightAnswer(void) const throw();
	
	// ������ ���� ��������� �������
	const std::vector<std::string> & GetVecAnswers(void) const throw();

private:

	// ������������� ����������� ������
	void InitRightAnswer(std::string &);

	// ������������� ������ �������
	void InitTextQuestion(std::string &);

	// ������������� ������� ���� ��������� �������
	void InitAnswers(std::string &);
};