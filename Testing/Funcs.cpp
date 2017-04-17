#include "Funcs.h"

// ����� ���� ������ � ����� � ��������
void Search(std::vector < std::string > &v)
{
	std::string path = std::string("*.test");	// ����� ������ � ����� �����������
	_finddata_t fd = { 0 };
	std::unique_ptr<Wrap> up;

	// ��������� �����
	up.reset(new Wrap(_findfirst(&path[0], &fd)));

	// ��������
	if (!*up)
	{
		std::cout << "�� ������� �� ������ �����, �������� ���� �� ���� � ����� � ��������..." << std::endl;
		exit(1);
	}

	do
	{
		std::string name(std::string(fd.name));

		// ���� ��� �����-�� ������� ���������� (*.test)
		if (fd.attrib & _A_SUBDIR)
			continue;

		// ���� ����
		else
			// ��������� ��� ����� � ������
			v.push_back( name );

	} while (!_findnext(*up, &fd));
}

// ���������� ���������� ����� � �����
void ReadFrom(const std::string &from, std::string &buf)
{
	buf.resize(4096);

	// �������� ����� � ������
	std::ifstream ifs(from);

	if (!ifs.is_open())
		throw std::exception("Can't open file with test");

	// ������ ����������� � �����
	while (!ifs.eof())
	{
		ifs.read(&buf[0], buf.size());

		size_t sizeRead = static_cast <size_t> (ifs.gcount());
		if (!sizeRead)
			throw std::exception("file is empty");

		buf.resize(sizeRead);
	}
}

// ������ � ����
void WriteTo(const std::string &dest, std::string &buf)
{
	// �������� ����� � ������
	std::ofstream ofs(dest, std::ios::app);

	if (!ofs.is_open())
		throw std::exception("Can't open file with test");
	
	// ������ ������ � ����
	ofs << '\n';
	ofs.write(&buf[0], buf.length());
}