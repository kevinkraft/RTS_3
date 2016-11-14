#include "SelectionMenu.h"
#include "Selectable.h"

SelectionMenu::SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, std::vector<Selectable*> selection_list) 
  : DisplayPiece(parent->getPosX() + rel_x, parent->getPosY() + rel_y, parent->getWidth() * rel_w, parent->getHeight() * rel_h, parent),
    SubMenu( rel_x, rel_y, rel_w, rel_h, parent )
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
{
  setParent(parent);
  setRelX(rel_x);
  setRelY(rel_y);
  setRelHeight(rel_h);
  setRelWidth(rel_w);
  setPositions();
  setup();
}

SelectionMenu::SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, std::vector<Entity*> selection_list) 
  : SelectionMenu( rel_x, rel_y, rel_w, rel_h, parent)
{
  std::vector<Selectable*> sl;
  for(std::vector<Entity*>::iterator it = selection_list.begin(); it != selection_list.end(); ++it)
    sl.push_back( dynamic_cast<Selectable*>((*it)) );
  setSelectionList(sl);
}

SelectionMenu::SelectionMenu(float rel_x, float rel_y, float rel_w, float rel_h, Menu * parent, std::vector<Item*> selection_list) 
  : SelectionMenu( rel_x, rel_y, rel_w, rel_h, parent)
{
  std::vector<Selectable*> sl;
  for(std::vector<Item*>::iterator it = selection_list.begin(); it != selection_list.end(); ++it)
    sl.push_back( dynamic_cast<Selectable*>((*it)) );
  setSelectionList(sl);
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
  //setup the buttons and the text boxes
  //make a TextLine for each entry
  int itr(0);
  float bt_x = 0.;
  float tb_x = 0.3;
  float bt_w = 0.3;
  float tb_w = 0.7;
  float rel_h = ( this->getHeight()/mSelectionList.size() ) / this->getHeight();
  float rel_y = 0.;
  for(std::vector<Selectable*>::iterator it = mSelectionList.begin(); it != mSelectionList.end(); ++it)
    {
      std::string selst = "temp";
      TextBox * tb = new TextBox(tb_x, rel_y, tb_w, rel_h, selst, this->mTextMaker, this);
      this->addTextBox( tb );
      ArgContainer args = ArgContainer();
      args.setInt(itr);
      args.setSelectionMenu( this );
      Button * bt = new Button(bt_x, rel_y, bt_w, rel_h, "O", &setButtonSelection, args, this);
      this->addButton( bt );
      rel_y += rel_h;
      itr++;
    }
}

ReturnContainer setButtonSelection(ArgContainer args)
{
  ReturnContainer rcontainer = ReturnContainer();
  args.mSelectionMenu->setSelection( args.mInt );
  return rcontainer;
}
