#include "SelectionMenu.h"
#include "Selectable.h"
#include <sstream>

SelectionMenu::SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, std::vector<Selectable*> selection_list)
  : DisplayPiece(parent->getPosX() + rel_x, parent->getPosY() + rel_y, parent->getWidth() * rel_w, parent->getHeight() * rel_h, parent),
  SubMenu( rel_x, rel_y, rel_w, rel_h, parent )
// SelectionMenu::SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, std::vector<Selectable*> selection_list)
//  : SubMenu( rel_x, rel_y, rel_w, rel_h, parent )
 //SelectionMenu::SelectionMenu(float x, float y, float w, float h, Menu * parent, std::vector<Selectable*> selection_list)
 //  : DisplayPiece(x, y, w, h, parent->mRenderer, parent->mWindow, parent->mTextMaker), Menu(x, y, w, h, parent->mRenderer, parent->mWindow, parent->mTextMaker)
{
  setParent(parent);
  setRelX(rel_x);
  setRelY(rel_y);
  setRelHeight(rel_h);
  setRelWidth(rel_w);
  setPositions();
  setSelectionList(selection_list);
  setup();
}

SelectionMenu::SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent)
 : DisplayPiece(parent->getPosX() + rel_x, parent->getPosY() + rel_y, parent->getWidth() * rel_w, parent->getHeight() * rel_h, parent),
   SubMenu( rel_x, rel_y, rel_w, rel_h, parent )
//SelectionMenu::SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent)
// : SubMenu( rel_x, rel_y, rel_w, rel_h, parent )
//SelectionMenu::SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent)
//  : DisplayPiece(x, y, w, h, parent->mRenderer, parent->mWindow, parent->mTextMaker), Menu(x, y, w, h, parent->mRenderer, parent->mWindow, parent->mTextMaker)
{
  setParent(parent);
  setRelX(rel_x);
  setRelY(rel_y);
  setRelHeight(rel_h);
  setRelWidth(rel_w);
  setPositions();
  //setup();
}

SelectionMenu::SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, std::vector<Entity*> selection_list)
  : SelectionMenu( rel_x, rel_y, rel_w, rel_h, parent)
{
  std::vector<Selectable*> sl;
  for(std::vector<Entity*>::iterator it = selection_list.begin(); it != selection_list.end(); ++it)
    sl.push_back( dynamic_cast<Selectable*>((*it)) );
  setSelectionList(sl);
  setup();
}

SelectionMenu::SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, std::vector<Item*> selection_list)
  : SelectionMenu( rel_x, rel_y, rel_w, rel_h, parent)
{
  std::vector<Selectable*> sl;
  for(std::vector<Item*>::iterator it = selection_list.begin(); it != selection_list.end(); ++it)
    sl.push_back( dynamic_cast<Selectable*>((*it)) );
  setSelectionList(sl);
  setup();
}

SelectionMenu::SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, EntityGroup* eg)
  : SelectionMenu( rel_x, rel_y, rel_w, rel_h, parent, eg->mEntities )
{}

SelectionMenu::SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, ItemGroup* ig)
  : SelectionMenu( rel_x, rel_y, rel_w, rel_h, parent, ig->mItems )
{}

SelectionMenu::~SelectionMenu()
{}

void SelectionMenu::setup()
{
  //make a text box with one line for each entry, make mMaxLines buttons for the selections
  setHasSelection(false);
  float bt_x = 230;
  float tb_x = 5;
  float bt_w = 0.15;
  float tb_w = 0.7;
  TextBox * title = new TextBox(tb_x, 0.1*this->getHeight(), 0.9, 0.2, "Press to select:", this->mTextMaker, this);
  this->addTextBox( title );
  std::string selst = "";
  for(std::vector<Selectable*>::iterator it = mSelectionList.begin(); it != mSelectionList.end(); ++it)
    {
      selst += (*it)->getName();
      if ( dynamic_cast<Item*>( *it ) )
        selst += "("+makeString( dynamic_cast<Item*>( *it )->getType() )+")("+makeString( dynamic_cast<Item*>( *it )->getAmount() )+") #newline ";
      else
        selst += " #newline ";
    }
  TextBox * tb = new TextBox(tb_x, 0.2*this->getHeight(), tb_w, 0.8, selst, this->mTextMaker, this);
  this->addTextBox( tb );
  //make a button for each of the lines displayed in a scroll window
  int maxlines = tb->getMaxLines() == 0 ? mSelectionList.size() : tb->getMaxLines();
  for ( int i=0; i< maxlines; i++  )
    {
      ArgContainer args = ArgContainer();
      args.setInt(i);
      args.setSelectionMenu( this );
      std::stringstream ssbtitle;
      ssbtitle << i;
      Button * bt = new Button(bt_x, 0.2*this->getHeight() + this->getHeight()/20. + (ACTUAL_TEXT_HEIGHT*0.87)*i,
                               bt_w, ACTUAL_TEXT_HEIGHT*0.85 / this->getHeight(), ssbtitle.str(), &setButtonSelection, args, this);
      this->addButton( bt );
    }
}

ReturnContainer setButtonSelection(ArgContainer args)
{
  ReturnContainer rcontainer = ReturnContainer();
  TextBox * tb = args.mSelectionMenu->getTextBox(1); //first tb is the title
  int scr = tb->getScroll();
  int ml = tb->getMaxLines();
  int selint = scr*ml + args.mInt;
  if ( selint < args.mSelectionMenu->getSizeSelectionList() )
    args.mSelectionMenu->setSelection( selint );
  return rcontainer;
}
