#include "stdafx.h"                       
#include <iostream>
#include <ctime>
#include <locale>
#include <fstream>
#include <vector>

__int64 Factorial(int number)
{
	if ((number == 1) | (number == 0))
	{
		return 1;
	}
	return Factorial(number - 1) * number;
}

int _tmain(int argc, _TCHAR* argv[])
{
	setlocale(LC_CTYPE, "Russian");
	
	const bool LEFT = true;
	const bool RIGHT = false;

	int sizeSet;
	int sizePlacements;

	std::vector<bool> direction;
	std::vector<int> set;
	std::vector<std::vector<int>> placements;

	//Данные
	sizeSet = 4;
	sizePlacements = Factorial(sizeSet);
	for (int i = 0; i < sizeSet; i++)
	{
		set.push_back(i);
	}

	for (int i = 0; i < sizeSet; i++)
	{
		direction.push_back(LEFT);
	}

	//Генератор
	std::vector<int> temp;
	for (int i = 0; i < sizeSet; i++)
	{
		temp.push_back(i);
	}
	placements.push_back(temp);

	bool flag = false;
	do
	{
		// поиск максимального мобильного элемента
		std::pair<int, bool> pair(INT_MIN, false);
		int tempI = 0;
		flag = false;
		for (int i = 0; i < sizeSet; i++)
		{
			if ((direction[i] == LEFT) && (i != 0)
				&& (temp[i] > temp[i - 1]))
			{
				if (pair.first < temp[i])
				{
					pair.first = temp[i];
					pair.second = direction[i];
					tempI = i;
					flag = true;
				}
			}
			else if ((direction[i] == RIGHT) && (i != sizeSet - 1)
				&& (temp[i] > temp[i + 1]))
			{
				if (pair.first < temp[i])
				{
					pair.first = temp[i];
					pair.second = direction[i];
					tempI = i;
					flag = true;
				}
			}
		}

		// перемещение мобильного элемента и смена направлений
		if (flag == true)
		{
			if (direction[tempI] == LEFT)
			{
				std::swap(direction[tempI], direction[tempI - 1]);
				std::swap(temp[tempI], temp[tempI - 1]);
				tempI--;
			}
			else if (direction[tempI] == RIGHT)
			{
				std::swap(direction[tempI], direction[tempI + 1]);
				std::swap(temp[tempI], temp[tempI + 1]);
				tempI++;
			}
			placements.push_back(temp);

			for (int i = 0; i < sizeSet; i++)
			{
				if (temp[tempI] < temp[i])
				{
					if (direction[i] == true)
					{
						direction[i] = false;
					}
					else
					{
						direction[i] = true;
					}
				}
			}
		}
	} while (flag == true);

	//Вывод
	std::cout << "Перестановки:" << std::endl;
	for (int i = 0; i < sizePlacements; i++)
	{
		std::cout << "{ ";
		for (int j = 0; j < placements[i].size(); j++)
		{
			std::cout << char(97 + placements[i][j]) << " ";
		}
		std::cout << "}" << std::endl;
	}
	
	system("pause");
	return 0;
}

