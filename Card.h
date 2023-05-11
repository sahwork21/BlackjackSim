/**
 * @file Card.c++
 * @author Sean Hinton (sahwork21@gmail.com)
 * @brief Class containing information on a Card. Cards are just containers of ints and names.
 *
 */
#include <string>
/**
 * @brief Class for a Card containing its value, name, and suit
 *
 */
class Card
{
private:
  // Fields
  int value;
  std::string name;
  std::string suit;

public:
  // Default constructor that does nothing
  Card()
  {
    Card(0, "", "");
  }

  // Parametrized constructor
  Card(int value, std::string name, std::string suit)
  {
    setValue(value);
    setName(name);
    setSuit(suit);
  }

  // Destructor for Card but we didn't allocate any resources so do nothing
  ~Card()
  {
  }

  // Getters and setter for data
  int getValue()
  {
    return value;
  }

  std::string getName()
  {
    return name;
  }

  std::string getSuit()
  {
    return suit;
  }

  void setValue(int value)
  {
    this->value = value;
  }

  void setName(std::string name)
  {
    this->name = name; 
    
  }
  
  void setSuit(std::string suit){
    this->suit = suit;
  }
};
