#include "EntityContainer.h"
#include "TextLine.h"

EntityContainer::EntityContainer(std::string name, SDL_Renderer *renderer, SDL_Window *window)
  : Selectable()
{
  mName = name;
}

EntityContainer::~EntityContainer()
{
  TerminalText::printTerminal("INFO: EntityContainer::~EntityContainer: Deleting EntityContainer.");
  //delete mGroupMap;
  //for (auto &itm: mGroupMap)
  //  delete &itm;
}

void EntityContainer::addContainer(std::string id, EntityContainer * ec)
{
  if (mContainerMap.count(id) == 0 )
    {
      std::vector<EntityContainer*> cv;
      cv.push_back(ec);
      mContainerMap[id] = cv;
      return;
    }
  mContainerMap[id].push_back(ec);
}

void EntityContainer::addContainers( std::string id, std::vector<EntityContainer*> ecs )
{
  if (mContainerMap.count(id) == 1 )
    {
      TerminalText::printTerminal("WARN: EntityContainer::addContainer: Container already has containers called "+id);
      return;
    }
  mContainerMap[id] = ecs;
 }

void EntityContainer::addEntity(std::string id, Entity * ent)
{
  if ( mGroupMap.count(id) == 0 )
    {
      TerminalText::printTerminal("WARN: EntityContainer::addEntity: Container has no group called "+id);
      return;
    }
  mGroupMap[id]->addEntity(ent);
}

void EntityContainer::addEntityGroup(std::string id, EntityGroup * eg)
{
  if ( mGroupMap.count(id) == 1 )
    {
      TerminalText::printTerminal("WARN: EntityContainer::addEntityGroup: Container already has a group called "+id);
      return;
    }
  mGroupMap[id] = eg;
}

Entity * EntityContainer::collide(float x, float y, int cameraoffset_x, int cameraoffset_y, float zoom)
{
  Entity * ent;
  for ( auto &itc: mContainerMap )
    {
      for ( auto &itcc: itc.second )
        {
          ent = itcc->collide(x, y, cameraoffset_x, cameraoffset_y, zoom);
          if ( ent != nullptr)
            return ent;
        }
    }
  for ( auto &itc: mGroupMap )
    {
      ent = itc.second->collide(x, y, cameraoffset_x, cameraoffset_y, zoom);
      if ( ent != nullptr)
        return ent;
    }
  return nullptr;
}

void EntityContainer::doActions()
{
  for ( auto &itc: mContainerMap )
    {
      for ( auto &itcc: itc.second )
        itcc->doActions();
    }
  for ( auto &itc: mGroupMap )
    itc.second->doActions();
}

std::vector<EntityContainer*> * EntityContainer::getContainerGroup(std::string gname)
{
  //returns the container group with name given
  if ( mContainerMap.count(gname) == 0 )
    {
      TerminalText::printTerminal("WARN: EntityContainer::getContainerGroup: Container has no container called "+gname);
      return nullptr;
    }
  return &mContainerMap[gname];
}

Entity * EntityContainer::getEntity(std::string ename)
{
  std::map<std::string,Entity*> emap;
  for (auto &itc: mGroupMap)
    emap[itc.first] = itc.second->getEntity(ename);

  std::vector<std::string> clist;
  for (auto &itme: emap)
    {
      if (itme.second != nullptr)
        clist.push_back( itme.first );
    }

  std::string wstring;
  //no matching entity
  if (clist.size() == 0)
    return nullptr;
  //one matching entity
  else if (clist.size() == 1)
    return emap[clist[0]];
  //more than one matching entity
  else
    {
      for (auto &its: clist)
        wstring += " "+its+" ";
      TerminalText::printTerminal("WARN: EntityContainer::getEntity: The same name, "+ename+ ", exists in two groups, "+wstring+". Returning nullptr.");
      return nullptr;
    }
}

EntityGroup * EntityContainer::getEntityGroup(std::string gname)
{
  //get an entity group from the map
  if ( mGroupMap.count(gname) == 0 )
    {
      TerminalText::printTerminal("WARN: EntityContainer::getEntityGroup: Container has no group called "+gname);
      return nullptr;
    }
  return mGroupMap[gname];
}

void EntityContainer::render(int cameraoffset_x, int cameraoffset_y, float zoom, std::vector<std::string> * group_order)
{
  if ( group_order == nullptr)
    {
      for ( auto &itc: mGroupMap )
        itc.second->render(cameraoffset_x, cameraoffset_y, zoom);
    }
  else
    {
      for ( auto &itl: *group_order )
        {
          if ( mGroupMap.count(itl) == 1 )
            mGroupMap[itl]->render(cameraoffset_x, cameraoffset_y, zoom);
        }
    }
  for ( auto &itc: mContainerMap )
    {
      for ( auto &itcc: itc.second )
        itcc->render(cameraoffset_x, cameraoffset_y, zoom);
    }
}

void EntityContainer::update()
{
  for ( auto &itc: mGroupMap )
    itc.second->update();
  for ( auto &itc: mContainerMap )
    {
      for ( auto &itcc: itc.second )
        itcc->update();
    }
}
