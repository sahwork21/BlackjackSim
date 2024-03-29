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
  Individual *i = new Individual();
  if(i->moveCollection[3] != Split){
    return 1;
  }
  int pass = 0;
  int total = 0;

  //Make an object and make sure they have the right population size
  Generation *g = new Generation(100, 15, 50, 10);

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
  

  //Now do a generation of simming
  total++;
  g->simAll(1, 50);
  

  cout << "Fittest in first gen "<< g->getFittest()->getFitness() << endl;

  if(g->getGeneration() != 1){
    cerr << "generation should be 1 now" << endl;
    return report(total, pass);
  }
  pass++;



  //Do multiple generations
  total++;
  g->simAll(5, 50);

  cout << "Fittest in sixth gen " << g->getFittest()->getFitness() << endl;
  if(g->getGeneration() != 6){
    cerr << "generation should be 6 now" << endl;
    return report(total, pass);
  }

  pass++;




  delete g;




  //Now do some tests that will take many generations
  //We have 100 individuals per generation, 15 top are picked, 50 percent crossovr, 10 percent mutations
  g = new Generation(100, 15, 50, 5);

  

  g->simAll(500, 200);

  cout << *g;


  delete g;

  //Let's print out the best every 100 generations
  

  return report(total, pass);
  
}