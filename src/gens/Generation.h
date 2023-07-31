/**
 * @file Generation.h
 * @author Sean Hinton
 * Header file for a generation which is a collection of Individuals
 * It will run rounds of simulations and put together our next generations of individuals
 * We will combine the best players table of moves and mutate somewhat to achieve an ideal strategy
 */

#ifndef GENERATION_H
#define GENERATION_H

#include "Individual.h"
#include <algorithm>
#include <random>


class Generation
{
private:

  //Sorting method that puts the fittest individuals first
  bool indSort(Individual *i, Individual *j)
  {
    return !(i->getFitness() < j->getFitness());
  }

  vector<Individual*> population;
  int generation; 
  int populationSize; 
  int selectedPercent; //Top percentage that get to create new generations. Randomly selected from first to X percentile
  int crossoverPercent; //Likelihood to get a crossover from parent 1. Probably should be 50
                        //Since this is a 50 percent sort of thing it should be even over all the moves we have
  int mutatePercent; //Probability of a mutation
  int selectionCutoff; //Really just the cutoff for selecting new individuals

  int newIndividuals; //The number of new individuals we make per round
  


  //Engine for a random numbers
  std::mt19937 nums;
  //population distribution selector
  std::uniform_int_distribution<int> popDist;
  //Generate a random digit 1 - 100 to get probabilites
  std::uniform_int_distribution<int> probDist;
  //Create our next vector of individuals using our fields
  void createNextGeneration(); //Create the next generation of individuals from our info given to us
  Individual* createChild(Individual* i1, Individual* i2);
public:
  Generation(int populationSize, int selectedPercent, int crossoverPercent, int mutatePercent);
  ~Generation();
  //Get what generation we are on
  int getGeneration() const;
  //Return the individual with the highest fitness
  Individual* getFittest() const; //Return the fittest individual

  //Sim one generation
  void simGeneration(int rounds);

  //Total sim which makes x generations and recombines them using a private method
  void simAll(int generations, int rounds);

};





#endif