#include <iostream>
#include <string>
#include "KnapsackProblem.h"
#include "GeneticAlgorithm.h"
#include "Exceptions.h"

void printBestSolution(const std::vector<bool>& bestSolution)
{
	std::cout << "\nBest solution: ";
	for (int i = 0; i < bestSolution.size(); i++)
	{
		std::cout << bestSolution[i] << " ";
	}
	std::cout << "\n";
}

int main()
{
	try {
		std::string fileName = "data.txt";

		KnapsackProblem problem(fileName);

		GeneticAlgorithm algorithm(problem, 4, 0.6, 0.1, 15);

		algorithm.simulate();

		printBestSolution(algorithm.returnBestSolution());
	}
	catch (KnapsackConstructorException& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (GeneticAlgorithmConstructorException& e)
	{
		std::cout << e.what() << std::endl;
	}
	catch (std::exception& e)	
	{
		std::cout << e.what() << std::endl;
	}

}
