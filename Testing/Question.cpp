#include "Question.h"

// ����������� � ����������
Question::Question(std::string &buf)
{
	// ������������� ������ �������
	InitTextQuestion(buf);

	// ������������� ����������� ������
	InitRightAnswer(buf);

	// ������������� ������� ���� ��������� �������
	InitAnswers(buf);
}

// ������������� ������ �������
void Question::InitTextQuestion(std::string &buf)
{
	const std::string leksem = std::string("\n");
	
	// ����� ����� �������
	const int posEnd = buf.find(leksem);
	
	// ������������� ������ �������
	this->strTextQuestion = buf.substr(0, posEnd);
	
	// ������� ����� �������
	buf.erase( 0, this->strTextQuestion.length() + 1);
}

void Question::InitRightAnswer(std::string &buf)
{
	// ����� ������ ����������� ������ � ������������������� �������
	const std::string mark = std::string(" (�����)");

	// ���� �����
	const int posMark = buf.find(mark);

	// ������ ������ � �������
	const int posStart = buf.rfind('\n', posMark) + sizeof('\n');

	// ������������� ����������� ������
	this->strRightAnswer = buf.substr(posStart, posMark - posStart);

	// ������� �����
	buf.erase( posMark, mark.length() );
}

void Question::InitAnswers(std::string &buf)
{
	const std::string leksem = std::string("\n");

	// ����� ����� �������� ������
	int posEnd = buf.find(leksem);

	while (posEnd != std::string::npos)
	{
		const std::string answer = buf.substr(0, posEnd);
		this->vecAnswers.push_back(answer);
		buf.erase( 0, answer.length() + 1);
		posEnd = buf.find(leksem);
	}
	if ( buf.size() )
		this->vecAnswers.push_back(buf);

	// ����������� ������� ��������� �������
	std::random_shuffle(this->vecAnswers.begin(), this->vecAnswers.end(), Question::Pred());
}

// ���������� ��������� ������
std::ostream & operator << (std::ostream &os, const Question &q)
{
	static int iCountQuest = 1;
	int iCountAnswer = 1;
	
	// ������ � ����� �������
	os << iCountQuest++ <<". " << q.strTextQuestion << std::endl;

	// ������ � ����� ��������� ������
	for (const auto &i : q.vecAnswers)
		os << "   " << iCountAnswer++ << ". " << i << std::endl;

	// ���������� �����
	return os;
}

// ������ �������
const std::string & Question::GetTextQustion(void) const throw()
{
	return this->strTextQuestion;
}

// ������ ������� ������
const std::string & Question::GetRightAnswer(void) const throw()
{
	return this->strRightAnswer;
}

// ������ � ���������� �������
const std::vector<std::string> & Question::GetVecAnswers(void) const throw()
{
	return this->vecAnswers;
}