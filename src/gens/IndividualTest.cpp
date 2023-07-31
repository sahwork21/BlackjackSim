/**
 * @file IndividualTest.cpp
 * @author Sean Hinton (sahinto2)
 * Test files for individuals in the genetic algorithm
 * 
 *
 * 
 */

#include "Individual.h"
#include <iostream>
#include <Windows.h>
#include <algorithm>

using std::cout;
using std::endl;
using std::cerr;

int pass;
int total;

//Reports how many of the cases are passes
static int report(int total, int pass)
{

  cout << "Individual: Passing " << pass << " of " << total << " tests" << endl;
  if(pass != total){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}

static bool myfunction (Individual* i, Individual* j) { return (i->getFitness() < j->getFitness()); }

/**
 * @brief Test functions for the Individual class
 * 
 * @return 0 if all tests pass, 1 if not including how many unit tests passed
 */
int main()
{
  //Check things like fitness and what not are set to default
  Individual *i = new Individual();
  total++;
  cout << "Fitness default val: "<< i->getFitness() << endl;
  if(i->getFitness() != 0){
    exit(report(total, pass));
    delete i;
  }
  pass++;

  


  //Let's just play one game and we can check if the fitness changed
  //If the fitness did not change we should just replay
  i->playRounds(1);

  total++;
  while(i->getFitness() == 0){
    Sleep(1000);
    i->playRounds(1);
  }
  pass++;


  //Play a bunch of rounds
  i->playRounds(10);


  delete i;
  //Now create a bunch of individuals and sort them

  total++;

  i = new Individual();
  i->setFitness(99);

  Individual *i2 = new Individual();
  Individual *i3 = new Individual();
  Individual *i4 = new Individual();
  Individual *i5 = new Individual();
  Individual *i6 = new Individual();

  i2->setFitness(5);
  i3->setFitness(8);
  i4->setFitness(1);
  i5->setFitness(87);
  i6->setFitness(8);

  std::vector<Individual*> sorted;
  sorted.push_back(i);
  sorted.push_back(i2);
  sorted.push_back(i3);
  sorted.push_back(i4);
  sorted.push_back(i5);
  sorted.push_back(i6);


  //Now sort it using std::sort using < operator defaultly
  sort(sorted.begin(), sorted.end(), myfunction);

  cout << "Sorted Fitnesses: ";
  for(std::vector<Individual*>::iterator it = sorted.begin(); it != sorted.end(); it++){
    cout << (*it)->getFitness() << ", ";
  }
  cout << endl;

  pass++;

  exit(report(total, pass));

}