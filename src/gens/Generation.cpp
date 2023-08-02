/**
 * @file Generation.cpp
 * @author Sean Hinton
 * Definitions for our declarations of what a generation does
 * Create new individuals from our best to hoepefull arrive at an optimal blackjack strategy
 */

#include "Generation.h"


//Engine for a random numbers
static std::mt19937 nums;
  //population distribution selector
static std::uniform_int_distribution<int> popDist;
  //Generate a random digit 1 - 100 to get probabilitess
static std::uniform_int_distribution<int> probDist;
Generation::Generation(int populationSize, int selectedPercent, int crossoverPercent, int mutatePercent)
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

  //Initialize our rng
  std::random_device *s = new std::random_device();
  



  
}

Generation::~Generation()
{
  population.clear();
}

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
  Individual *y;
  Individual *z;
  //Rows are your score columns is the dealer card
  Move hardHands[16][10];
  //Rows are ace plus the other 9 card types
  Move softHands[8][10];
  //Rows are the pair type
  Move pairHands[10][10];

  

  for(int i = 0; i < newIndividuals; i++){
    //Select random ones from 0 to our cutoff
    a = popDist(nums);
    b = popDist(nums);
    while(a == b){
      b = popDist(nums);
    }

    y = population[a];
    z = population[b];


    //Now fill out our table with the moves we need
    for(int i = 0; i < 16; i++){
      for(int j = 0; j < 10; j++){
        if(mutatePercent <= probDist(nums)){
          hardHands[i][j] = moveCollection[probDist(nums) % 3];
        }
        else if(crossoverPercent <= probDist(nums)){
          hardHands[i][j] = y->getHardHands(i, j);
        }
        else{
          hardHands[i][j] = z->getHardHands(i, j);
        }
      }
    }

    //Fill in softs then hards then pairs
    for(int i = 0; i < 8; i++){
      for(int j = 0; j < 10; j++){
        if(mutatePercent <= probDist(nums)){
          softHands[i][j] = moveCollection[probDist(nums) % 3];
        }
        else if(crossoverPercent <= probDist(nums)){
          softHands[i][j] = y->getSoftHands(i, j);
        }
        else{
          softHands[i][j] = z->getSoftHands(i, j);
        }
      }
    }
    //Fill in softs then hards then pairs
    for(int i = 0; i < 10; i++){
      for(int j = 0; j < 10; j++){
        if(mutatePercent <= probDist(nums)){
          pairHands[i][j] = moveCollection[probDist(nums) % 4];
        }
        else if(crossoverPercent <= probDist(nums)){
          pairHands[i][j] = y->getPairHands(i, j);
        }
        else{
          pairHands[i][j] = z->getPairHands(i, j);
        }
      }
    }

    //Now produce a new individual and add them to the population
    population.push_back(new Individual(hardHands, softHands, pairHands));

  }

  //We have created a new generation now



}



