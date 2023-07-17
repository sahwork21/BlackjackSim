/**
 * @file IndividualTest.cpp
 * @author Sean Hinton (sahinto2)
 * Test files for individuals in the genetic algorithm
 * 
 *
 * 
 */

#include "Individual.h"

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
  if(i->getFitness() != 0){
    report(total, pass);
    delete i;
  }
  pass++;

  report(total, pass);
}