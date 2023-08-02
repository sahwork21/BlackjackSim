/**
 * @file GenerationTest.cpp
 * @author Sean Hinton
 * Test file for the generation class
 */
#include "Generation.h"
#include <iostream>
using std::cout;
using std::endl;
using std::cerr;



//Reports how many of the cases are passes
static int report(int total, int pass)
{

  cout << "Generation: Passing " << pass << " of " << total << " tests" << endl;
  if(pass != total){
    return EXIT_FAILURE;
  }
  return EXIT_SUCCESS;
}
int main()
{
  int pass = 0;
  int total = 0;

  //Make an object and make sure they have the right population size
  Generation *g = new Generation(100, 50, 15, 10);

  total++;
  if(g->getGeneration() != 0){
    cerr << "Generation is not at 0 on default" << endl;
    return report(total, pass);
  }
  

  if(g->getFittest()->getFitness() != 0){
    cerr << "First object should have a default fitness" << endl;
    return report(total, pass);
  }
  pass++;
  


  return report(total, pass);
  
}