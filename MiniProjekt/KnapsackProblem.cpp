#include <iostream>
#include <vector>
#include <stdexcept>
#include <fstream>
#include <string>
#include <sstream>
#include "KnapsackProblem.h"
#include "Exceptions.h"
#include "ExceptionPrompts.h"


KnapsackProblem::KnapsackProblem(std::string& filePath)			
{

	std::ifstream file(filePath);
	std::string line;
	float weight, value;

	std::getline(file, line);
	std::stringstream weightsStream(line);
	std::getline(file, line);
	std::stringstream valuesStream(line);
	std::string token;
	while (std::getline(weightsStream, token, ' ')) {
		try {
			weight = std::stof(token);
			if (std::getline(valuesStream, token, ' '))
			{
				value = std::stof(token); 
			}
			else
			{
				throw KnapsackConstructorException(pWeightsAndValuesMismatch);
			}
			if (weight < 0)
			{
				throw KnapsackConstructorException(pNegativeWeight + " Weight = " + std::to_string(weight));
			}
			if (value < 0)
			{
				throw KnapsackConstructorException(pNegativeValue + " Value = " + std::to_string(value));
			}
		}
		catch (std::invalid_argument& e) 
		{
			throw KnapsackConstructorException(pInvalidInput);
		}
		weightsAndValues.push_back(std::make_pair(weight, value));
	}

	if (std::getline(valuesStream, token, ' '))
	{
		try
		{
			value = std::stof(token);
			throw KnapsackConstructorException(pWeightsAndValuesMismatch);
		}
		catch(std::invalid_argument& e)
		{
			throw KnapsackConstructorException(pInvalidInput);
		}
	}


	getline(file, line);
	try
	{
		capacity = std::stof(line);
	}
	catch (std::invalid_argument& e) {
		throw KnapsackConstructorException(pInvalidCapacityInput);
	}

	if (capacity < 0)
	{
		throw KnapsackConstructorException(pNegativeCapacity + " Capacity = " + std::to_string(capacity));
	}

	quantity = weightsAndValues.size();
}


KnapsackProblem::KnapsackProblem(float capacityInt, const std::vector<std::pair<float, float>>& weightsAndValuesVector) :
	capacity(capacityInt), weightsAndValues(weightsAndValuesVector), quantity(weightsAndValuesVector.size())
{	
	if (capacity < 0)
	{
		throw KnapsackConstructorException(pNegativeCapacity + " Capacity = " + std::to_string(capacity));
	}

	if (weightsAndValues.empty())
	{
		throw KnapsackConstructorException(pNoItems);
	}
}

KnapsackProblem::KnapsackProblem(const KnapsackProblem& other) :
	quantity(other.quantity), capacity(other.capacity), weightsAndValues(other.weightsAndValues) 
{}


KnapsackProblem::KnapsackProblem(KnapsackProblem&& other) :
	quantity(other.quantity), capacity(other.capacity)
{
	weightsAndValues.swap(other.weightsAndValues);
}

KnapsackProblem::~KnapsackProblem()
{}

void KnapsackProblem::operator=(const KnapsackProblem& other)
{
	quantity = other.quantity; 
	capacity = other.capacity; 
	weightsAndValues = other.weightsAndValues;
}

void KnapsackProblem::operator=(KnapsackProblem&& other)
{
	quantity = other.quantity;
	capacity = other.capacity;
	weightsAndValues.swap(other.weightsAndValues);
}


int KnapsackProblem::calculateFitness(const std::vector<bool>& genotype) const	
{
	int weight = 0;
	int value = 0;
	for (int i = 0; i < genotype.size(); i++)
	{
		if (genotype[i])
		{
			weight += weightsAndValues[i].first;
			value += weightsAndValues[i].second;
		}
	}

	if (weight > capacity)
	{
		return 0;
	}
	else
	{
		return value;
	}
}


int KnapsackProblem::getQuantity()
{
	return quantity;
}

float KnapsackProblem::getCapacity()
{
	return capacity;
}



//std::string line;
//std::ifstream file(filePath);
//float weight, value;

//getline(file, line);
//std::istringstream weightsLine(line);
//getline(file, line);
//std::istringstream valuesLine(line);
//while (weightsLine >> weight) {
//	valuesLine >> value;	//if no more data, default value 0.0f is assigned to item
//	if (weight < 0)
//	{
//		throw KnapsackConstructorException(pNegativeWeight + " Weight = " + std::to_string(weight));
//	}
//	if (value < 0)
//	{
//		throw KnapsackConstructorException(pNegativeValue + " Value = " + std::to_string(value));
//	}
//	weightsAndValues.push_back(std::make_pair(weight, value));
//}