#include "Button.h"
#include "Action.h"
#include "texture.h"
#include "Menu.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "Map.h"
#include "Message.h"

Button::Button(float rel_x, float rel_y, float rel_w, float rel_h, std::string title, int * outcome, SDL_Renderer *renderer, SDL_Window *window)
{

  std::cout << "Button::Button: INFO: In first constructor" << std::endl;
  mTexture = nullptr;
  mRenderer = nullptr;
  mWindow = nullptr;
  mTitle = nullptr;

  FunctionCaller funcCaller = nullptr;
  ArgContainer args = ArgContainer();
  setFunctionCaller(funcCaller);
  setArgContainer(args);

  mTexture = loadTexture("res/images/menu/button_0_0.png", renderer, true);
  
  mRenderer = renderer;
  mWindow = window;
  
  mRect = new SDL_Rect();

  setRelPosX(rel_x);
  setRelPosY(rel_y);
  setRelWidth(rel_w);
  setRelHeight(rel_h);

  setHighlight(false);
  setTitleString(title);

  setOutcome(outcome);
}

Button::Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, FunctionCaller caller, ArgContainer args,
	       Menu * menu)
  : Button::Button(rel_x, rel_y, rel_width, rel_height, title, nullptr, menu->mRenderer, menu->mWindow)
{
  setArgContainer(args);
  setFunctionCaller(caller);
  mTextMaker = menu->getTextMaker();
  makeTitleMessage();
}

Button::~Button()
{
  std::cout << "Deleting Button" << std::endl;
}

void Button::makeTitleMessage()
{
  Message * message = new Message(mTitleString, mTextMaker);
  mTitle = message;
}

ReturnContainer Button::outcome()
{
  ReturnContainer funcReturn;
  if (mOutcome != nullptr && mFunctionCaller == nullptr)
    {
      funcReturn.setOutcome(mOutcome);
    }
  if (mOutcome == nullptr && mFunctionCaller != nullptr)
    {
      funcReturn = mFunctionCaller(mArgContainer);
    }
  if (mOutcome == nullptr && mFunctionCaller == nullptr)
    {
      std::cout << "Button::outcome: WARN: This button has no outcome" << std::endl; 
    }
  return funcReturn;
}


void Button::render(int cameraoffset_x, int cameraoffset_y, float zoom, Menu * menu)
{
  //NEED TO RESET THE MESSAGE POSITIONS HERE SOMEWHERE
  float posx = menu->getPosX();
  float posy = menu->getPosY(); 
  float width = menu->getWidth() * mRelWidth;
  float height = menu->getHeight() * mRelHeight;
  float rectposx = getPixelX(posx, posy, cameraoffset_x, cameraoffset_y, zoom) + mRel_x;
  float rectposy = getPixelY(posx, posy, cameraoffset_x, cameraoffset_y, zoom) + mRel_y;
  renderTexture(mTexture, mRenderer, rectposx, rectposy, width, height);
  //render the title message
  if (mTitle != nullptr)
    {
      float title_scale = 0.7;
      mTitle->setActive(true);
      mTitle->setHeight(height * title_scale);
      mTitle->setWidth(width * title_scale);
      float tborder = (1.-0.8)/2.;
      float tposx = getIsoX(rectposx + tborder * width, rectposy + tborder * height, cameraoffset_x, cameraoffset_y, zoom);
      float tposy = getIsoY(rectposx+ tborder * width, rectposy + tborder * height, cameraoffset_x, cameraoffset_y, zoom);
      mTitle->setPosX( tposx );
      mTitle->setPosY( tposy );
      mTitle->render(cameraoffset_x, cameraoffset_y, zoom);
    }
}
