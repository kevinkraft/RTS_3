#include "ExchangeMenu.h"
#include "SelectionMenu.h"
//#include "TextMaker.h"
//#include "SubMenu.h"
#include "NumberBox.h"

//-------------------------------------------------------------------------------------

ExchangeMenu::ExchangeMenu(float x, float y, float w, float h, SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker)
  : DisplayPiece(x, y, w, h, renderer, window, textMaker), Menu(x, y, w, h, renderer, window, textMaker)
{
  setup();
}

ExchangeMenu::ExchangeMenu(SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker)
  : DisplayPiece(0., 0., SCREEN_WIDTH, SCREEN_HEIGHT, renderer, window, textMaker), Menu(0., 0., SCREEN_WIDTH, SCREEN_HEIGHT, renderer, window, textMaker)
{
  setup();
}

ExchangeMenu::~ExchangeMenu()
{
}

void ExchangeMenu::clear()
{
  mWasClosed = false;
  mFinishedSelection = false;
  wipe();
  Menu::clear();
}

std::vector< std::pair<int, float> > ExchangeMenu::getFinalExchangeList()
{
  //Called by the Exchange action, returns the final item selection if
  //the user has clicked OK
  std::vector< std::pair<int, float> > exl;
  if ( mFinishedSelection == true )
    {
      TerminalText::printTerminal(  "INFO: ExchangeMenu::getFinalExchangeList: OK IS CLICKED, PASSING BACK THE LIST"  );
      exl = mExchangeList;
      //this->clear();
      setActive(false);
      return mExchangeList;
    }

  return exl;
}

void ExchangeMenu::setup()
{
  std::cout << "INFO: ExchangeMenu::setup : Setting up exchange menu " << std::endl;
  std::vector< std::pair<int, float> > exl_temp;
  mExchangeList = exl_temp;
  mFinishedSelection = false;
  mWasClosed = false;
}

void ExchangeMenu::makeCloseButton()
{
  //add a close button to the list of buttons on the menu
  float close_scale = 13./14.;
  FunctionCaller closeFunc = &closeExchangeMenu;
  ArgContainer ac;
  ac.setMenu(this);
  Button * closeInfoMenu = new Button( close_scale * getWidth() , 0., 1-close_scale, 1-close_scale, "X", closeFunc, ac, this );
  addButton(closeInfoMenu);
}

void ExchangeMenu::populate(Unit * acter, EntityAction * target)
//populate the exchange menu with sub menus and text boxes for the
//making of the exchange action parameters
{
  mFinishedSelection = false;
  this->makeCloseButton();
  setWasClosed(false);
  setActer(acter);
  setTarget(target);
  //make two SelectionMenus of the acter and target inventories and place then
  SelectionMenu * acter_slm = new SelectionMenu( 0.05*getWidth(), 0.45*getHeight(), 0.4, 0.5, this, mActer->getInventory() );
  this->addSelectionMenu( acter_slm );
  SelectionMenu * target_slm = new SelectionMenu( 0.55*getWidth(), 0.45*getHeight(), 0.4, 0.5, this, mTarget->getInventory() );
  this->addSelectionMenu( target_slm );
  //make two textboxes with the entity names above the sel menus
  TextBox * acter_name = new TextBox( 0.0025*getWidth(), 0.37*getHeight(), 0.4, 0.1, mActer->getName()+"'s Inventory:", this->mTextMaker, this);
  TextBox * target_name = new TextBox( 0.5425*getWidth(), 0.37*getHeight(), 0.4, 0.1, mTarget->getName()+"'s Inventory:", this->mTextMaker, this);
  this->addTextBox( acter_name );
  this->addTextBox( target_name );
  //make a number box for input of the amount to exchange
  //max and min are +/- the max number of an item that an entity has
  float nmin = 0.;
  float nmax = 0.;
  for ( auto &ititem: mActer->getInventory()->mItems )
    {
      if ( ititem->getAmount() > nmax )
        nmax = ititem->getAmount();
    }
  for ( auto &ititem: mTarget->getInventory()->mItems )
    {
      if ( ititem->getAmount() > nmax )
        nmax = ititem->getAmount();
    }
  nmin = -1*nmax;
  NumberBox * nb = new NumberBox( nmin, nmax, 0.1*getWidth(), 0.1*getHeight(), 0.2, 0.2, this);
  this->addSubMenu( nb );
  //make a textbox to display the exchange list that has been made
  TextBox * tbsel = new TextBox(0.45*getWidth(), 0.05*getHeight(), 0.5, 0.4, "LIST OF SELECTED ITEMS", this->mTextMaker, this);
  this->addTextBox( tbsel );
  //make a button to cancel the previous entry
  ArgContainer args = ArgContainer();
  args.setMenu(this);
  Button * bcancel = new Button(0.35*getWidth(), 0.27*getHeight(), 0.09, 0.07, "Cancel", &cancelPreviousEntry, args, this);
  this->addButton( bcancel );
  //make a button to accept the list and make the exchange action
  Button * okb = new Button(0.35*getWidth(), 0.15*getHeight(), 0.09, 0.07, "Ok", &setExchangeMenuSelection, args, this);
  this->addButton( okb );
}

bool ExchangeMenu::outcome()
{
  //if the selection menus are pressed, then update the exchange list and the display
  //the first one is acter, the second is target
  //first update the sel menus
  for(std::vector<SelectionMenu*>::iterator it = mSelectionMenus.begin(); it != mSelectionMenus.end(); ++it)
    (*it)->outcome();

  Item * item;
  float value = dynamic_cast<NumberBox*>( this->mSubMenus[0] )->getValue();
  if ( this->getSelectionMenu(0)->hasSelection() == true)
    {
      item = dynamic_cast<Item*>( this->getSelectionMenu(0)->getSelection() );
      this->getSelectionMenu(0)->setHasSelection(false);
      if ( item != mSelectedItem )
        {
          mSelectedItem = item;
          mExchangeList.push_back( {mSelectedItem->getType(),value} );
          updateSelectedItems();
          TerminalText::printTerminal( "ACTER SELECTION MADE" );
        }
    }
  if ( this->getSelectionMenu(1)->hasSelection() == true )
    {
      item = dynamic_cast<Item*>( this->getSelectionMenu(1)->getSelection() );
      this->getSelectionMenu(1)->setHasSelection(false);
      if ( item != mSelectedItem )
        {
          mSelectedItem = item;
          mExchangeList.push_back( {mSelectedItem->getType(), -1*value} );
          updateSelectedItems();
          TerminalText::printTerminal( "TARGET SELECTION MADE" );
        }
    }
  for (auto &it: mExchangeList)
    {
      TerminalText::printTerminal( makeString(it.first) +" : "+ makeString(it.second)  );
    }
  return Menu::outcome();
}

void ExchangeMenu::updateSelectedItems()
{
  //update the textlines showing the items that have been selected
  std::string words = "";
  if ( mExchangeList.size() == 0 )
    mTextBoxes[2]->setWords("LIST OF SELECTED ITEMS");
  else
    {
      for (auto &it: mExchangeList)
        {
          //make a temporary item to check the names;
          Item * item_temp = new Item(it.first, 0.);
          words += "Exchange " + makeString( it.second ) + " " + item_temp->getName() + " from " + mActer->getName() + " to " + mTarget->getName() + " #newline ";
        }
      mTextBoxes[2]->setWords(words);
    }
  return;
}

void ExchangeMenu::wipe()
{
  //wipe the menu and reset the acter and target
  mActer = nullptr;
  mTarget = nullptr;
  std::vector< std::pair<int, float> > exl_temp;
  mExchangeList = exl_temp;
  Menu::wipe();
}

//-----------------------------------------------------------------------------------------------
// Other Functions
//-----------------------------------------------------------------------------------------------

ReturnContainer cancelPreviousEntry(ArgContainer args)
{
  //removes the last entry from the exchange list
  ExchangeMenu * em = dynamic_cast<ExchangeMenu*>( args.mMenu );
  std::vector< std::pair<int, float> > exl = em->getExchangeList();
  std::vector< std::pair<int, float> > exl_temp;
  if ( exl.size() == 0 )
    return ReturnContainer();
  if ( exl.size() == 1 )
    exl = exl_temp;
  else
    exl.erase( exl.end() -1 );
  em->setExchangeList( exl );
  em->updateSelectedItems();
  return ReturnContainer();
}

ReturnContainer setExchangeMenuSelection(ArgContainer args)
{
  //sets the selection as finished
  ExchangeMenu * em = dynamic_cast<ExchangeMenu*>(args.mMenu);
  em->setFinishedSelection(true);
}

ReturnContainer closeExchangeMenu(ArgContainer ac)
{
  ExchangeMenu * em = dynamic_cast<ExchangeMenu*>(ac.mMenu);
  em->setActive(false);
  em->wipe();
  em->setWasClosed(true);
  ReturnContainer rt;
  return rt;
}

