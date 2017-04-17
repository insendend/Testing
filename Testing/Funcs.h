#pragma once
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <memory>
#include <io.h>
#include "WrapFind.h"

// ����� ���� ������ � ����� � ��������
void Search(std::vector < std::string > &);

// ���������� ���������� ����� � �����
void ReadFrom(const std::string &, std::string &);

// ������ � ���� ���������� ������
void WriteTo(const std::string &, std::string &);