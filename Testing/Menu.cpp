#include "Menu.h"

Menu::Menu(void)
{ 
	// ������������� ������� � ���������� ������, ���� ��� ����
	// � ����� ���������������� ���������, ���� �� ���
	Search(this->vTestNames);
}

// ������������ ����������� �����
void Menu::OutputWord(const size_t &i) const throw()
{
	//	1	����
	//	2-4 �����
	//	5+	������
	if (i == 1)
		std::cout << "������ " << i << " ����, ������� \"1\", ����� ��� ";
	else if (i >= 2 && i <= 4)
		std::cout << "������� " << i << " �����, �������� ���, ������� ������ ";
	else
		std::cout << "������� " << i << " ������, �������� ���, ������� ������ ";
}

// ����������� ������� ����
void Menu::Main(void) const throw()
{
	std::cout << "1. ������ ����" << std::endl;
	std::cout << "2. ������������� ����" << std::endl;
	std::cout << "3. �������� ������� �����" << std::endl;
	std::cout << "4. �����" << std::endl;
	std::cout << "��� ����� -> ";
}

// ����������� ������� ����
void Menu::Edit(void) const throw()
{
	std::cout << "1. �������� ����� ������" << std::endl;
	std::cout << "2. ������� ������������ ������" << std::endl;
	std::cout << "3. �����" << std::endl;
	std::cout << "��� ����� -> ";
}

// ����������� ������ ������
void Menu::TestList(void) const	throw()
{
	std::cout << "�������� ����" << std::endl;
	auto cit = this->vTestNames.cbegin();
	for (size_t i = 0; cit != this->vTestNames.cend(); ++cit, ++i)
		std::cout << i + 1 << ". "
		<< this->vTestNames[i].substr( 0, this->vTestNames[i].find(".test") ) // �������� ����� ��� ����������
		<< std::endl;
	
	std::cout << "��� ����� -> ";
}

// ���������������� ���� (����� ��������)
Menu::Choice Menu::MainChoice(void) const
{
	size_t choice = 0;
	std::string buf;

	do
	{
		// ����� ������� ����
		(*this).Main();

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

	} while (choice > 4 || choice < 1);

	// ������������ �� size_t � Choice
	return static_cast <Choice> (choice);
}

// ���������������� ���� (����� �����)
const std::string& Menu::TestChoice(void) const 
{
	size_t testNumber = 0;
	std::string buf;

	do
	{
		// ����� ������ ������
		(*this).TestList();

		std::getline(std::cin, buf);
		system("cls");

		try
		{
			// ����������� �� ������ � size_t
			testNumber = static_cast < size_t > (stoi(buf));
		}

		// ���������� stoi()
		catch (const std::invalid_argument &ia)
		{
			std::cout << ia.what() << std::endl;
		}

	} while (testNumber > this->vTestNames.size() || testNumber < 1);

	// ���������� ������� ������� (�������� �����)
	return this->vTestNames[testNumber - 1];
}