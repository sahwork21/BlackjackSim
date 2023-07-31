/**
 * @file Generation.cpp
 * @author Sean Hinton
 * Definitions for our declarations of what a generation does
 * Create new individuals from our best to hoepefull arrive at an optimal blackjack strategy
 */

#include "Generation.h"



Generation::Generation(int populationSize, int selectedPercent, int crossoverPercent, int mutatePercent)
  :popDist(0, selectionCutoff - 1), probDist(1, 100), nums(std::random_device{})
{
  this->populationSize = populationSize;
  this->selectedPercent = selectedPercent;
  this->crossoverPercent = crossoverPercent;
  this->mutatePercent = mutatePercent;

  selectionCutoff = selectedPercent * populationSize / 100;
  newIndividuals = populationSize - selectionCutoff;

  //Now populate our population with randomness
  for(int i = 0; i < populationSize; i++){
    population.push_back(new Individual());
  }

  
}

Generation::~Generation(){}

int Generation::getGeneration() const
{
  return generation;
}

Individual* Generation::getFittest() const
{
  return population[0];
}

void Generation::simGeneration(int rounds)
{
  //Sim for all individuals
  //It will likely be slow because I can't figure out threads
  for(std::vector<Individual*>::iterator it = population.begin(); it != population.end(); it++){
    (*it)->playRounds(rounds);
  } 

}

void Generation::simAll(int generations, int rounds)
{
  //Sim rounds for all the indviduals
  //Then sort them by fitness and recombine them
  for(int i = 0; i < generations; i++){
    simGeneration(rounds);
    std::sort(population.begin(), population.end(), indSort);

    createNextGeneration();
  }

  

  
}

void Generation::createNextGeneration()
{
  generation++;
  
  //Create a new population from our cutoff
  //Consists of our best ones to transfer over
  vector<Individual*> nextGen;
  nextGen.reserve(populationSize);


  //Delete all the unneeded individuals
  Individual *temp;
  while(population.size() >= selectionCutoff){
    temp = population.back();
    population.pop_back();
    delete temp;
  }

  //Create the new individuals
  int a;
  int b;
  for(int i = 0; i < newIndividuals; i++){
    //Select random ones from 0 to our cutoff
    a = popDist(nums);
    b = popDist(nums);
    while(a == b){
      b = popDist(nums);
    }
    population.push_back(createChild(population[a], population[b]));

  }


  

  

  //Then combine them by randomly putting them together for our move squares





}



