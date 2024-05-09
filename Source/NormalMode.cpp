#include "NormalMode.h"
#include "Menus.h"

#include "List.hpp"

#include <iostream>

#include "memtrace.h"


void ZaPe::NormalMode::Run()
{
	Menus::ClearConsole();
	Menus::PrintNormalModMenu();
	
	List<int> szamok;


	// Szamok beolvasasa
	std::string input;
	while (true)
	{
		bool hibasInput = false;
		std::getline(std::cin, input);
		if (input == "q")
			break;

		if (input.size() == 0) continue;

		for (size_t i = 0; i < input.size(); i++)
		{
			if (i == 0 && input[0] == '-') continue;

			if (!isdigit(input.c_str()[i]))
			{
				std::cerr << "Hibas input" << std::endl;
				hibasInput = true;
			}
		}

		if (hibasInput) continue;

		int tmp = atoi(input.c_str());

		szamok.push_back(tmp);
	}

	const char* szamokPath = "szamok.txt";
	std::ofstream ofile(szamokPath);

	// Szamok fajlba kiirasa
	if (ofile.is_open())
	{
		for (List<int>::Iterator iter = szamok.begin(); iter != szamok.end(); iter++)
		{
			ofile << *iter << "\n";
		}
	
		ofile.close();
	}

	// szamok fajlbol beolvasasa
	List<int> beolvasott_szamok;
	std::ifstream ifile(szamokPath);
	if (ifile.is_open())
	{
		int data;

		ifile >> data;


		while (!ifile.eof())
		{
			beolvasott_szamok.push_back(data);
			ifile >> data;
		}

		ifile.close();
	}

	// Szamok kiirasa
	std::cout << "Beolvasott szamok: ";
	for (List<int>::Iterator iter = beolvasott_szamok.begin(); iter != beolvasott_szamok.end(); iter++)
	{
		std::cout << *iter;
		if (iter != beolvasott_szamok.end())
		{
			std::cout << ", ";
		}
	}
	std::cout << std::endl;


	std::cout << "Nyomj [ENTER]-t a hogy visszalepj a fomenube" << std::endl;
	std::getline(std::cin, input);
}