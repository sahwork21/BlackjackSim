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
    i->playRounds(1);
  }
  pass++;


  exit(report(total, pass));

}