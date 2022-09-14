#pragma once
#include <iostream>
#include <vector>
template<class T>
void Print(const std::vector<T>& v)
{
	for (auto& c : v)
	{
		std::cout << c << " ";
	}
	std::cout << "\n";
}
template<class T>
void Print(const std::valarray<T>& v)
{
	for (auto& c : v)
	{
		std::cout << c << " ";
	}
	std::cout << "\n";
}
template<class T> 
void Print(const std::vector<std::vector<T>>& v)
{
	for (auto& c1 : v) {
		Print(c1);
	}
}
template<class T>
void Print(const std::vector<std::valarray<T>>& v)
{
	for (auto& c1 : v) {
		Print(c1);
	}
}