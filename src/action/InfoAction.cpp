//-------------------------------------------------------------------------------------

#include "Action.h"
#include "InfoAction.h"
#include "InfoMenu.h"
#include "SubMenu.h"
//#include "Movement.h"
//#include "Attack.h"
//#include "Unit.h"
//#include "Map.h"
//#include <cmath>
//#include "FunctionCaller.H"

//class EntityHP;
//class EntityAction;

//-------------------------------------------------------------------------------------

InfoAction::InfoAction(Entity * target, InfoMenu * info_menu) :
  Action()
{
  setTarget(target);
  setInfoMenu(info_menu);
}

ReturnContainer makeInfoAction(ArgContainer args)
{
  InfoAction * ia = new InfoAction( args.mTargetEntity, args.mInfoMenu );
  ReturnContainer rcontainer = ReturnContainer();
  rcontainer.mAction = ia;
  return rcontainer;
}

InfoAction::~InfoAction()
{
  std::cout << "Deleting InfoAction" << std::endl;
}

bool InfoAction::doAction()
{
  TerminalText::printTerminal("INFO: InfoAction::doAction: Making the action menu.");
  mInfoMenu->wipe();
  TerminalText::printTerminal("INFO: InfoAction::doAction: Finished wiping the menu.");
  //add the blurb
  mInfoMenu->getTextBox(0)->setWords( mTarget->blurb() );
  //inventory menu is 1st in the InfoMenu SubMenu list
  if ( EntityAction * ea = dynamic_cast<EntityAction*>(mTarget) )
    {
      //set up the InfoMenu for EntityActions with Inventory and HP
      mInfoMenu->getSubMenu(1)->getTextBox(0)->setWords( ea->printInventory() );
      //set up the InfoMenu for EntityActions with Inventory and HP
      mInfoMenu->getSubMenu(0)->getTextBox(0)->setWords( ea->printStats() );
    }
  if ( Resource * r = dynamic_cast<Resource*>(mTarget) )
    {
      //set up the InfoMenu for EntityActions with Inventory and HP
      mInfoMenu->getSubMenu(0)->getTextBox(0)->setWords( r->printStats() );
    }
  mInfoMenu->setActive(true);
  TerminalText::printTerminal("INFO: InfoAction::doAction: Finished making the action menu.");
  return true;
}
