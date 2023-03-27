#pragma once
#include <iostream>
#include <vector>
#include "KnapsackProblem.h"

class Individual {
public:
	Individual(int howManyItems);
	Individual(const Individual& other);
	Individual(Individual&& other);
	~Individual();
	void operator=(const Individual& other);
	void operator=(Individual&& other);

	int getFitness(const KnapsackProblem& problem);
	void mutate(float mutProb);
	std::pair<Individual, Individual> cross(const Individual& other, float crossProb) const;

	std::vector<bool> getGenotype() const;

private:
	std::vector<bool> genotype;
};