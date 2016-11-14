//Class for an object which can go into a SelectionList
//
//Kevin Maguire
//21/08/2016
//

//Notes:
// * Class from which Item and Entity and anything that can go in a Selection List 
//   must derive from


//-------------------------------------------------------------------------------------      

#ifndef SELECTABLE_H_
#define SELECTABLE_H_

//-------------------------------------------------------------------------------------      

class Selectable
{
 public:
  
  Selectable();
  virtual ~Selectable();
  virtual std::string selectionString();
    
 protected:
  std::string mName; 
 
};

#endif
