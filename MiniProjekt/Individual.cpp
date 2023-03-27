#include <iostream>
#include <vector>
#include <random>
#include <algorithm>
#include "Individual.h"


Individual::Individual(int howManyItems)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_int_distribution<> distrib(0, 1);

	for (int i = 0; i < howManyItems; i++)
	{
		genotype.push_back(distrib(gen));
	}
}

Individual::Individual(const Individual& other) : genotype(other.genotype)
{}

Individual::Individual(Individual&& other)
{
	genotype.swap(other.genotype);
}



Individual::~Individual()
{}

void Individual::operator=(const Individual& other)
{
	genotype = other.genotype;
}

void Individual::operator=(Individual&& other)
{
	genotype.swap(other.genotype);
}


int Individual::getFitness(const KnapsackProblem& problem)
{
	return problem.calculateFitness(this->genotype);
}


void Individual::mutate(float mutProb)
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib(0, 1);

	for (int i = 0; i < genotype.size(); i++)
	{
		if (distrib(gen) < mutProb)
		{
			genotype[i] = !genotype[i];
		}
	}
}


std::pair<Individual, Individual> Individual::cross(const Individual& other, float crossProb) const	
{
	std::random_device rd;
	std::mt19937 gen(rd());
	std::uniform_real_distribution<> distrib1(0, 1);
	std::uniform_int_distribution<> distrib2(1, genotype.size());


	if (distrib1(gen) < crossProb)
	{
		Individual child1(*this);
		Individual child2(other);
		int border = distrib2(gen);
		child1.genotype.erase(child1.genotype.begin() + border, child1.genotype.end());
		child2.genotype.erase(child2.genotype.begin() + border, child2.genotype.end());

		std::copy(other.genotype.begin() + border, other.genotype.end(), std::back_inserter(child1.genotype));
		std::copy(this->genotype.begin() + border, this->genotype.end(), std::back_inserter(child2.genotype));

		return std::make_pair(child1, child2);
	}
	else
	{
		return std::make_pair(other, *this);
	}
}

std::vector<bool> Individual::getGenotype() const
{
	return genotype;
}
