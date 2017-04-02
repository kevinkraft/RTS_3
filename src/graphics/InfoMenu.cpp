#include "InfoMenu.h"
//#include "TextMaker.h"
#include "SubMenu.h"

//-------------------------------------------------------------------------------------

InfoMenu::InfoMenu(float x, float y, float w, float h, SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker)
  : DisplayPiece(x, y, w, h, renderer, window, textMaker), Menu(x, y, w, h, renderer, window, textMaker)
{
  setup();
}

InfoMenu::InfoMenu(SDL_Renderer *renderer, SDL_Window *window, TextMaker * textMaker)
  : DisplayPiece(0., 0., SCREEN_WIDTH, SCREEN_HEIGHT, renderer, window, textMaker), Menu(0., 0., SCREEN_WIDTH, SCREEN_HEIGHT, renderer, window, textMaker)
{
  setup();
}

InfoMenu::~InfoMenu()
{
}

void InfoMenu::populate(EntityAction * ea)
//populate the info menu with EntityAction related info, these are currently in info action, but should be here
{

}

void InfoMenu::populate(Resource * r)
//populate the info menu with Resource related info, these are currently in info action, but should be here
{

}

void InfoMenu::setup()
//set up the info menu sub menus and text boxes
{
  //default testing string
  std::string splitline = "And #vspace7 to find out that he has to carry this saddness with him in his heart is simply soulcrushing. It is like pouring #newline salt #newline on the wound because it reminds you that this amazing actor has died too. She wheeled her wheel barrow through the streets broad and  narrow crying cockles and mussels #newline alive alive o. #vspace10 65 people were killed and 314 injured in a blast in Gulshan-e-Iqbal-long-name-very-long Park, in Iqbal Town area of Lahore. The sound of the blast was heard around 6:30 pm today, with rescue teams dispatched to the site. These include 23 ambulances and rescue vehicles. The Irish Times today claims it has reproduced a copy of the paper from 1916 but guess what, it has taken out a sentence";
  //add a close button
  this->makeCloseButton();
  //make a title
  TextBox * title = new TextBox(0., 30., 0.9, 0.2, splitline, mTextMaker, this);
  this->addTextBox(title);
  //make a stats menu
  SubMenu * submenu_stats = new SubMenu(50, 150, 0.3, 0.68, this);
  this->addSubMenu(submenu_stats);
  TextBox* stat_box = new TextBox( 0., 0., 1., 1., splitline, mTextMaker, submenu_stats);
  submenu_stats->addTextBox(stat_box);
  //make an inventory menu
  SubMenu * submenu_inv = new SubMenu(380., 150., 0.60, 0.68, this);
  this->addSubMenu(submenu_inv);
  TextBox* inv_box = new TextBox( 0., 0., 1., 1., splitline, mTextMaker, submenu_inv);
  submenu_inv->addTextBox(inv_box);

  //this->setActive(true);
}
