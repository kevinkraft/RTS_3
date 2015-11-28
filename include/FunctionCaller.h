#ifndef FUNCTIONCALLER_H_
#define FUNCTIONCALLER_H_

#include <string>
#include <iostream>

#include "ArgContainer.h"

typedef ReturnContainer (*FunctionCaller)(ArgContainer);
typedef std::pair<FunctionCaller, std::string> FunctionCallerID;

#endif
