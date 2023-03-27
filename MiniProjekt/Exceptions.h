#pragma once
#include <iostream>

class KnapsackConstructorException : public std::exception
{
public:
	KnapsackConstructorException(std::string message);
	std::string what();

private:
	std::string message;
};

class GeneticAlgorithmConstructorException : public std::exception
{
public:
	GeneticAlgorithmConstructorException(std::string message);
	std::string what();

private:
	std::string message;
};
