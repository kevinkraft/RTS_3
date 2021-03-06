//Base class for the actions
//
//Kevin Maguire
//09/08/2015
//

//Note:
// * The doAction function gives false if not finished and true if finished

//-------------------------------------------------------------------------------------

#include "Action.h"
#include "EntityAction.h"
#include "PopMenu.h"
#include "FunctionCaller.h"
#include "Resource.h"
#include "Construction.h"

//-------------------------------------------------------------------------------------

Action::Action()
{}

Action::~Action()
{
  //std::cout << "Deleting Action" << std::endl;
}
void Action::setActer(EntityAction * acter)
{
  std::cout << "WARN: Action::setActer: This function should be overloaded and in most cases should not be called." << std::endl;
}

//-------------------------------------------------------------------------------------
// Other Functions
//-------------------------------------------------------------------------------------

void makeActionMenu(PopMenu * pop_menu, std::vector<FunctionCallerID> callerIDs, ArgContainer args)
{
  std::cout << "INFO: Action: makeActionMenu: Start populating pop menu" << std::endl;
  args.setPosX( pop_menu->getGamePosX() );
  args.setPosY( pop_menu->getGamePosY() );
  //float rel_x = 0.;
  //float rel_y = 0.;
  //float rel_h = 1./(callerIDs.size() + 0.0);
  for(std::vector<FunctionCallerID>::iterator it = callerIDs.begin(); it != callerIDs.end(); ++it)
    {
      //The button positions are set in PopMenu at render time
      //Button * button = new Button(rel_x, rel_y, 1., rel_h, (it)->second, (it)->first, args, pop_menu);
      Button * button = new Button(0., 0., 1., 0., (it)->second, (it)->first, args, pop_menu);
      pop_menu->addButton(button);
      //pop_menu->addButton(button);
      //rel_y += pop_menu->getItemHeight();
    }
  pop_menu->scaleHeight();
  pop_menu->setActive(true);
  TerminalText::printTerminal( "INFO: action::makeActionMenu: Finished populating the pop menu" );
}

void makeActionMenu(PopMenu * pop_menu, EntityAction * selected)
{
  std::cout << "INFO: Action: makeActionMenu: In this fuction." <<std::endl;
 //make the buttons for actions selected can do on their own
  std::vector<FunctionCallerID> callerIDs = selected->actionsByMyself();
  ArgContainer args = ArgContainer();
  pop_menu->setSelectedEntity(selected);
  makeActionMenu(pop_menu, callerIDs, args);
}

void makeActionMenu(PopMenu * pop_menu, EntityAction * selected, Entity * target, InfoMenu * info_menu, ExchangeMenu * exchange_menu)
{
  //make the buttons for actions that selected can do on target
  //std::vector<FunctionCallerID> callerIDs = selected->actionsByMyself();
  std::vector<FunctionCallerID> callerIDs;
  std::vector<FunctionCallerID> sel_callerIDs = selected->actionsByMe();
  std::vector<FunctionCallerID> tar_callerIDs = target->actionsOnMe();
  //only keep what is in both lists
  for(std::vector<FunctionCallerID>::iterator it = sel_callerIDs.begin(); it != sel_callerIDs.end(); ++it)
    {
      for(std::vector<FunctionCallerID>::iterator tar_it = tar_callerIDs.begin(); tar_it != tar_callerIDs.end(); ++tar_it)
	{
	  if ( (it)->second == (tar_it->second) )
	    {
	      callerIDs.push_back( (*it) );
	    }
	}
    }
  ArgContainer args = ArgContainer();
  args.setTargetEntity(target);
  args.setTargetEntityHP(dynamic_cast<EntityHP*>(target));
  args.setResource(dynamic_cast<Resource*>(target));
  args.setInfoMenu(info_menu);
  args.setExchangeMenu(exchange_menu);
  args.setConstruction(dynamic_cast<Construction*>(target));
  pop_menu->setSelectedEntity(selected);
  makeActionMenu(pop_menu, callerIDs, args);
}
