#include <iostream>
#include <vector>
#include <chrono>
#include <random>
#include "GeneticAlgorithm.h"
#include "KnapsackProblem.h"
#include "Exceptions.h"
#include "ExceptionPrompts.h"

GeneticAlgorithm::GeneticAlgorithm(KnapsackProblem& prob, int popSize, float cProb, float mProb, int stop): 
	problem(prob), populationSize(popSize), crossProb(cProb), mutProb(mProb), stopTime(stop), bestSolutionValue(0)
{
	if (populationSize < 2)
	{
		throw GeneticAlgorithmConstructorException(pInvalidPopulationSize + " Population size = " + std::to_string(populationSize));
	}
	if (crossProb < 0 || crossProb > 1)
	{
		throw GeneticAlgorithmConstructorException(pInvalidCrossProb + " Crossing probability = " + std::to_string(crossProb));
	}
	if (mutProb < 0 || mutProb > 1)
	{
		throw GeneticAlgorithmConstructorException(pInvalidMutProb + " Mutation probability = " + std::to_string(mutProb));
	}
	if (stopTime <= 0)
	{
		throw GeneticAlgorithmConstructorException(pInvalidStopTime + " Time = " + std::to_string(stopTime));
	}
}


void GeneticAlgorithm::simulate() 
{
	for (int i = 0; i < populationSize; i++)
	{
		population.push_back(Individual(problem.getQuantity()));

		int testValue;

		if (i == 0)
		{
			bestSolution = population[0].getGenotype();
			bestSolutionValue = population[0].getFitness(problem);
		}
		else
		{
			if (bestSolutionValue < (testValue = population[i].getFitness(problem)))
			{	
				bestSolution = population[i].getGenotype();
				bestSolutionValue = testValue;
			}
		}
	}

	auto end = std::chrono::high_resolution_clock::now() + std::chrono::milliseconds(stopTime);

	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, populationSize - 1);


	while (std::chrono::high_resolution_clock::now() < end)
	{
		std::vector<Individual> newPopulation;

		for (int i = 0; i < (populationSize / 2); i++)		//crossing
		{
			int first = distrib(gen);
			int second = distrib(gen);
			

			if (first != second)
			{
				std::pair<Individual, Individual> children = population[first].cross(population[second], crossProb);
				newPopulation.push_back(children.first);
				newPopulation.push_back(children.second);
			}
			else
			{
				std::pair<Individual, Individual> children = population[first].cross(population[(first + 1) % populationSize], crossProb);
				newPopulation.push_back(children.first);
				newPopulation.push_back(children.second);
			}
		
		}

		if (populationSize % 2 == 1)
		{
			newPopulation.push_back(population[distrib(gen)]);
		}


		population = newPopulation;		//new population


		for (int i = 0; i < populationSize; i++)	//mutation and new potential best solution
		{
			population[i].mutate(mutProb);

			
			int testValue;
			if (bestSolutionValue < (testValue = population[i].getFitness(problem)))
			{	
				bestSolution = population[i].getGenotype();
				bestSolutionValue = testValue;
			}
		}
	}
}


std::vector<bool> GeneticAlgorithm::returnBestSolution() const
{
	return bestSolution;
}