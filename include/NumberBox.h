//Class for choosing a number
//
//Kevin Maguire
//25/03/2017
//

//Notes:
// * This derives from submenu, so it must be placed on a preexisting menu
// * Has two buttons for adding/subtracting and two for adding/subtracting more than 1

//Problems:
// * I originally tried to use a TextBox for idsplaying the number, but changing the
//   TextBox text doesn't work, the tex just disappears.
//   * I used a TextLine instead

//-------------------------------------------------------------------------------------

#ifndef NUMBERBOX_H_
#define NUMBERBOX_H_

//#include <string>
//#include <iostream>

//#include "TextLine.h"
//#include "TextMaker.h"
//#include "Button.h"
#include "SubMenu.h"

//-------------------------------------------------------------------------------------

//class Button;

class NumberBox: public SubMenu
{
 public:

  //NumberBox(float x, float y, float width, float height, std::vector<std::string> words, TextMaker * maker);
  NumberBox(float minval, float maxval, float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent);
  virtual ~NumberBox();
  void setValue(float vl);

  float getMax()
    {
      return mMax;
    }
  float getMin()
    {
      return mMin;
    }
  float getValue()
    {
      return mValue;
    }
  void setMax(float mv)
    {
      mMax = mv;
    }
  void setMin(float mv)
    {
      mMin = mv;
    }


 private:

  void setup();
  void setValue();

  float mMin;
  float mMax;
  float mValue;

};

ReturnContainer incrementValueByOne(ArgContainer args);
ReturnContainer decrementValueByOne(ArgContainer args);
ReturnContainer incrementValueByTen(ArgContainer args);
ReturnContainer decrementValueByTen(ArgContainer args);

#endif
