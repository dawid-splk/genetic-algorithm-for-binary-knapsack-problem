#pragma once
#include <iostream>
#include <vector>
#include "Individual.h"
#include "KnapsackProblem.h"

class GeneticAlgorithm {

public:
	GeneticAlgorithm(KnapsackProblem& prob, int popSize, float cProb, float mProb, int stop);
	void simulate(); 
	std::vector<bool> returnBestSolution() const;	

private:
	KnapsackProblem& problem;
	int populationSize;
	std::vector<Individual> population;		
	float crossProb;
	float mutProb;
	int stopTime;
	std::vector<bool> bestSolution;
	int bestSolutionValue;
	
};