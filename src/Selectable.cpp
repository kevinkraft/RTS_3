#include <iostream>
#include "Selectable.h"


Selectable::Selectable()
{
}

Selectable::~Selectable()
{
}

std::string Selectable::selectionString()
{
  //I don't think this is used. mName is used instead
  std::cout << "WARN: Selection::selectionString: This should be overwritten by the base classes and should not be called." << std::endl;
  return " ";
}

