#pragma once
#include <iostream>
#include <vector>


class KnapsackProblem {

public:
	KnapsackProblem(std::string& filePath);	
	KnapsackProblem(float capacityInt, const std::vector<std::pair<float, float>>& weightsAndValuesVector);
	KnapsackProblem(const KnapsackProblem& other);
	KnapsackProblem(KnapsackProblem&& other);
	~KnapsackProblem();
	void operator=(const KnapsackProblem& other);
	void operator=(KnapsackProblem&& other);

	int calculateFitness(const std::vector<bool>& genotype) const;	

	int getQuantity();
	float getCapacity();

private:
	int quantity;
	float capacity;
	std::vector<std::pair<float, float>> weightsAndValues;
};

