#include <iostream>
#include "Exceptions.h"


KnapsackConstructorException::KnapsackConstructorException(std::string msg) : message(msg) {}

std::string KnapsackConstructorException::what()
{
	return "Knapsack Problem Constructor Exception: " + message;
}


GeneticAlgorithmConstructorException::GeneticAlgorithmConstructorException(std::string msg) : message(msg) {}

std::string GeneticAlgorithmConstructorException::what()
{
	return "Genetic Algorithm Constructor Exception: " + message;
}

