#include "Test.h"
#include <conio.h>

// ����������� � ����������
Test::Test(const std::string &testName) : points(0), testName(testName)
{
	// ����� ��� ������ ����� �����
	std::string buf;

	// ���������� �� ����� � �����
	ReadFrom(this->testName, buf);

	// �������� ������ �� ��������� ����� (������, ������, ���������� �����)
	// � ������������� ���������� ������
	InitAll(buf);

	// ����������� ������� ��������
	std::random_shuffle(this->questions.begin(), this->questions.end(), Test::Pred());
}

// ���������� ������ �� �������
void Test::InitAll(std::string &buf)
{
	// �����������
	const std::string leksemes = std::string("\n\n");

	// ������� ������ � ����� ������� �������
	int posStart = 0;
	int posEnd = buf.find(leksemes, posStart);

	// ���� ������� �������, ���������� � ���� ������
	while (posStart != std::string::npos)
	{
		// ������������������� ������
		std::string tmp = buf.substr(posStart, posEnd - posStart);

		// ����������� ������, �������� ��: ������, ������ ����� � �������� �������
		Question q(tmp);
		
		// ��������� � ������ ��������
		questions.push_back(q);

		// ���� �������� ��������� �����
		posStart = buf.find_first_not_of(leksemes, posEnd);
		posEnd = buf.find(leksemes, posStart);
	}
}

// ������ �����
void Test::Start(void)
{
	for (const auto &i : this->questions)
	{		
		// ����� ������� � ���������� ������
		std::cout << i;
		
		// ����� ������������ ����� ���� ��������� �������
		size_t posInVector = this->UserInputAnswer( i.GetVecAnswers().size() );

		// ��������� ���������� �������� ������ � ����������
		if ( i.GetVecAnswers()[posInVector] == i.GetRightAnswer() )
			this->points++;
	}
}

// �������������� �����
Test::ForEdit Test::EditChoice(void)
{
	size_t choice = 0;
	std::string buf;
	Menu m;

	do
	{
		// ����� ������� ���� ��������������
		m.Edit();

		std::getline(std::cin, buf);
		system("cls");

		try
		{
			// ����������� �� ������ � size_t
			choice = static_cast < size_t > (stoi(buf));
		}

		// ���������� stoi()
		catch (const std::invalid_argument &ia)
		{
			std::cout << ia.what() << std::endl;
		}

	} while (choice > 3 || choice < 1);

	return static_cast <ForEdit> (choice);
}

// ����������� �������� �����
void Test::Show(void) const throw()
{
	// ���������� ����� �������
	size_t iCount = 1;
	
	// ����� ��������
	for (const auto &i : this->questions)
		std::cout << iCount++ <<". " << i.GetTextQustion() << std::endl;
}

// �������� ��� ������
void Test::Do(const Menu::Choice &ch)
{
	switch (ch)
	{
	
	// ����������� �����
	case Menu::Choice::PASS:
		this->Start();
		std::cout << "U got " << this->GetPoints() << "/" << this->questions.size() << " points" << std::endl;
		this->Saving();
		break;
	
	// �������������� �����
	case Menu::Choice::EDIT:
		this->Edit( this->EditChoice() );
		break;
	
	// ����������� �������� �����
	case Menu::Choice::SHOW:
		this->Show();
		break;
	
	// ����� �� ���������
	case Menu::Choice::EXIT:
		exit(0);
	
	default:
		throw (std::exception("Main Switch Default"));
	}
}

// ���� ������ �� ������������
size_t Test::UserInputAnswer(const size_t &index)
{
	size_t choice = 1;
	std::string buf;

	do
	{
		std::cout << "��� ����� -> ";
		std::getline(std::cin, buf);
		system("cls");

		try
		{
			// ����������� �� ������ � size_t
			choice = static_cast < size_t > (stoi(buf));
		}

		// ���������� stoi()
		catch (const std::invalid_argument &ia)
		{
			std::cout << ia.what() << std::endl;
		}

	} while (choice > index || choice < 1);

	// ������� �������� ������ � ������� �������
	return --choice;
}

// ���������� ����������� �����
const size_t &Test::GetPoints()
{
	return this->points;
}

// ���������� �������������� �����
void Test::Edit(const Test::ForEdit &ch)
{
	switch (ch)
	{
	
	// ���������� �������� �����
	case Test::ForEdit::ADD:
		this->AddQuestion();
		break;
	
	// �������� ������� �� ����� ������������
	case Test::ForEdit::DELETE:
		this->DeleteQuestion();
		break;
	
	// �����
	case Test::ForEdit::EXIT:
		exit(0);
		break;
	
	default:
		throw (std::exception("Edit Switch Default"));
	}
}

// ���������� �������
void Test::AddQuestion(void)
{
	// ��������� ����� ������� � �����
	std::cout << "������� ����� �������:" << std::endl;
	std::string buf;
	std::getline(std::cin, buf);
	buf.push_back('\n');

	// ���� �� ��������� ���������� ������� ������ � ������
	std::cout << "������� ���������� �����:" << std::endl;
	std::string tmp;
	std::getline(std::cin, tmp);
	buf += tmp;
	buf += std::string(" (�����)");
	buf.push_back('\n');
	tmp.clear();

	// ��������� ������ ������� ������
	std::cout << "�������� ��� ���� �� ���� �������:" << std::endl;
	std::getline(std::cin, tmp);
	buf += tmp;
	buf.push_back('\n');
	tmp.clear();
	
	// ��������� ����������� ������� �� ������� ������������
	char c;
	do
	{
		std::cout << "�������� ��� �������?(y - ��, n - ���) -> ";
		c = _getche();
		std::cout << std::endl;
		if (c == 'y')
		{
			std::cout << "������� ��������� ������� ������:" << std::endl;
			std::getline(std::cin, tmp);
			buf += tmp;
			buf.push_back('\n');
			tmp.clear();
		}
	} while (c != 'n');
	
	// ���������� ������ ������� � ����
	WriteTo(testName, buf);
	
	// ���������� ������� � ������ � ������
	this->questions.push_back(Question(buf));

	// ��������� ���� ��, ���� ����� �������� ��� ������
	do
	{
		system("cls");
		std::cout << "������ �������� ��� ������?(y - ��, n - ���) -> ";
		c = _getche();

		system("cls");

		if (c == 'y')
			this->AddQuestion();

	} while (c != 'n');
}

// �������� ������� �� ����� ������������
void Test::DeleteQuestion(void)
{
	// ������� ������ ��������
	std::cout << "����� �� ������ ������� �������?" << std::endl;
	this->Show();
	
	std::string tmp;
	size_t questNumber = 0;	// ���������� ����� ������� � ������
	
	do
	{
		std::cout << "��� ����� -> ";
		std::getline(std::cin, tmp);
		system("cls");

		try
		{
			// ����������� �� ������ � size_t
			questNumber = static_cast < size_t > (stoi(tmp));
		}

		// ���������� stoi()
		catch (const std::invalid_argument &ia)
		{
			std::cout << ia.what() << std::endl;
		}

	} while (questNumber > this->questions.size() || questNumber < 1);

	// ���������� ����� ������� � ������� ��������
	questNumber--;
	 
	// ������� ������ �� �����
	Delete( this->questions[questNumber] );	

	// ������� ������ �� ������� � ������
	this->questions.erase(this->questions.cbegin() + questNumber);
}

// �������� �� ����� ������� �� ����������
void Test::Delete(const Question &q)
{
	// ��������� � ����� �� �����
	std::string buf;
	ReadFrom(this->testName, buf);

	// ������� ������ � ����� ���������� ������� � ��������
	int posStart = buf.find(q.GetTextQustion());
	int posEnd = buf.find("\n\n", posStart);

	// ������� ��� �� ������
	buf.erase(posStart, posEnd);

	// �������� ����� � ������ ��� ����������
	std::ofstream ofs(this->testName, std::ios::trunc);

	if (!ofs.is_open())
		throw std::exception("Can't open file with test");
	
	// ���������� ������� � ����
	ofs.write(&buf[0], buf.length());
}

// ���������� ����������� ����������� �����
void Test::Saving(void)
{
	std::cout << "������ ��������� ���������?(y - ��) -> ";
	char c = _getche();
	std::cout << std::endl;
	if (c == 'y')
	{
		std::cout << "���� ���? ";
		std::string name;
		std::getline(std::cin, name);

		std::ofstream ofs("result.txt", std::ios::app);
		
		if (!ofs.is_open())
			throw std::exception("Can't open file with results");

		// ���������� � ����
		ofs << name 
			<< '\t' 
			<< this->testName 
			<< '\t' 
			<< static_cast <double> (this->points)  / static_cast <double> (this->questions.size()) * 100
			<< "%" 
			<< std::endl;
	}
}