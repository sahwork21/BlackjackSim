/**
 * @file Generation.cpp
 * @author Sean Hinton
 * Definitions for our declarations of what a generation does
 * Create new individuals from our best to hoepefull arrive at an optimal blackjack strategy
 */

#include "Generation.h"





Generation::Generation(int populationSize, int selectedPercent, int crossoverPercent, int mutatePercent)
  :generation(0)
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
  std::random_device r;
  std::seed_seq s {r(), r(), r(), r(), r(), r(), r(), r()};
  nums.seed(s);
  probDist.param(std::uniform_int_distribution<int>::param_type(1, 100));
  //Select from our eligible parents that we want to continue on
  popDist.param(std::uniform_int_distribution<int>::param_type(0, selectionCutoff - 1));



  
}

Generation::~Generation()
{

  //If we are testing we want to be sure things are sorted properly
  #ifdef TEST
    for(int i = 0; i < populationSize; i++){
      std::cout << population[i]->getFitness() << ", ";
    }
    std::cout << std::endl;
  #endif

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
  for(int i = 0; i < populationSize; i++){
    population[i]->playRounds(rounds);
  } 

}

void Generation::simAll(int generations, int rounds)
{
  


  //Sim rounds for all the indviduals
  //Then sort them by fitness and recombine them
  for(int i = 0; i < generations; i++){
    //Reset all the fitnesses
    for(int j = 0; j < populationSize; j++){
      population[j]->resetFitness();
    }


    simGeneration(rounds);
    std::sort(population.begin(), population.end(), myfunction);
    
    createNextGeneration();
  }

  //std::sort(population.begin(), population.end(), myfunction);
  
  
}

void Generation::createNextGeneration()
{
  generation++;
  
  //Create a new population from our cutoff
  //Consists of our best ones to transfer over


  //Delete all the unneeded individuals
  Individual *temp;
  while(population.size() > selectionCutoff){
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
        if(mutatePercent >= probDist(nums)){
          hardHands[i][j] = y->moveCollection[probDist(nums) % 3];
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
        if(mutatePercent >= probDist(nums)){
          softHands[i][j] = y->moveCollection[probDist(nums) % 3];
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
        if(mutatePercent >= probDist(nums)){
          pairHands[i][j] = y->moveCollection[probDist(nums) % 4];
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

std::ostream& operator<<(std::ostream& strm, const Generation &g)
{
  //Print out our fittest individuals play chart

  
  Individual *f = g.population[0];
  strm.width(2);
  strm << "  Hard hands" << std::endl << "  | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| A ";

  int z = 20;
  //Print from highest score to lowest
  for(int i = 15; i >= 0; i--){
    if(z >= 10){
      strm << std::endl << z;
    }
    else{
      strm << std::endl << z << " ";
    }
      for(int j = 0; j < 10; j++){
        
        switch(f->getHardHands(i, j)){
          case Stand:
            strm << "| S ";
            break;

          case Hit:
            strm << "| H ";
            break;
          
          case DoubleDown:
            strm << "| D ";
            break;
          
          default:
            break;
          
         
        }
      }
    z--;
  }

  //Fill in softs then hards then pairs
  strm << std::endl << "Soft hands" << std::endl << "  | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| A ";

  z = 9; // 9 to 2
  for(int i = 7; i >= 0; i--){
    strm << std::endl << " " << z;
    for(int j = 0; j < 10; j++){
      switch(f->getSoftHands(i, j)){
          case Stand:
            strm << "| S ";
            break;

          case Hit:
            strm << "| H ";
            break;
          
          case DoubleDown:
            strm << "| D ";
            break;
          default:
            break;
          
        }
      
    }
    z--;
  }
  //Fill in softs then hards then pairs

  strm << std::endl << "Pair hands" << std::endl << "  | 2 | 3 | 4 | 5 | 6 | 7 | 8 | 9 | 10| A ";
  z = 11;
  for(int i = 9; i >= 0; i--){
    
    if(z == 11){
      strm << std::endl << " A";
    }
    else{
      strm << std::endl << " " << z;
    }
    for(int j = 0; j < 10; j++){
        
        switch(f->getPairHands(i, j)){
          case Stand:
            strm << "| S ";
            break;

          case Hit:
            strm << "| H ";
            break;
          
          case DoubleDown:
            strm << "| D ";
            break;
          
          case Split:
            strm << "| X ";
            break;
        }
    }
    z--;
  }

  strm << std::endl << std::endl;
  
  return strm;
}

