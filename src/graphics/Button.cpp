#include "Action.h"
#include "texture.h"
#include "SDL2/SDL.h"
#include "SDL2_image/SDL_image.h"
#include "Map.h"
#include "TextLine.h"

#include "Menu.h"

#include "Button.h"



Button::Button(float rel_x, float rel_y, float rel_w, float rel_h, std::string title, int outcome, SDL_Renderer *renderer, SDL_Window *window,
	       TextMaker * TextHandler)
{

  std::cout << "Button::Button: INFO: In first constructor" << std::endl;
  mTexture = nullptr;
  mRenderer = nullptr;
  mWindow = nullptr;
  mTitle = nullptr;

  //FunctionCaller funcCaller = nullptr;
  mFunctionCaller = nullptr;
  ArgContainer args = ArgContainer();
  //setFunctionCaller(funcCaller);
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
  mTextMaker = TextHandler;
  makeTitleTextLine();

  setOutcome(outcome);
}

Button::Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, FunctionCaller caller, ArgContainer args,
	       Menu * menu)
  : Button::Button(rel_x, rel_y, rel_width, rel_height, title, 0, menu->mRenderer, menu->mWindow, menu->getTextMaker() )
{
  setArgContainer(args);
  setFunctionCaller(caller);
}

Button::Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, FunctionCaller caller, ArgContainer args,
	       SDL_Renderer *renderer, SDL_Window *window, TextMaker * TextHandler)
  : Button::Button(rel_x, rel_y, rel_width, rel_height, title, 0, renderer, window, TextHandler )
{
  setArgContainer(args);
  setFunctionCaller(caller);
}



Button::~Button()
{
  std::cout << "Deleting Button" << std::endl;
}

bool Button::collide(float x_screen, float y_screen, Menu * menu)
{
  //need to figure out the screen pos of the button corner and its width and heigh in pixels
  float posx = menu->getPosX();
  float posy = menu->getPosY(); 
  float width = menu->getWidth() * mRelWidth;
  float height = menu->getHeight() * mRelHeight;
  //float rposx = getPixelX(posx, posy, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE) + mRel_x;
  float rposx = posx + mRel_x;
  //float rposy = getPixelY(posx, posy, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE) + mRel_y;  
  float rposy = posy + mRel_y;  
  if ( 
      (x_screen < rposx + width) && (rposx <= x_screen ) && 
      (y_screen < rposy + height) && (rposy <= y_screen )
       )
    {
      setPressed(true);
      return true;
    }
  else
    {
      setPressed(false);
      return false;
    }
}

void Button::makeTitleTextLine()
{
  TextLine * message = new TextLine(mTitleString, mTextMaker);
  mTitle = message;
}

ReturnContainer Button::outcome()
{
  ReturnContainer funcReturn;
  if ( mPressed )
    {
      //Possible problem here as if mOutcome is 0 then ptr mOuntcome == nullptr?
      if (mFunctionCaller == nullptr)
	{
	  funcReturn.setOutcome(mOutcome);
	}
      else if (mOutcome == 0 && mFunctionCaller != nullptr)
	{
	  funcReturn = mFunctionCaller(mArgContainer);
	}
      else if (mOutcome == 0 && mFunctionCaller == nullptr)
	{
	  std::cout << "Button::outcome: WARN: This button has no outcome" << std::endl; 
	}
    }
  return funcReturn;
}

void Button::render(Menu * menu)
{
  float posx = menu->getPosX();
  float posy = menu->getPosY(); 
  float width = menu->getWidth() * mRelWidth;
  float height = menu->getHeight() * mRelHeight;
  this->render(posx, posy, width, height);
}

void Button::render(TextBox * tb)
{
  float posx = tb->getPosX();
  float posy = tb->getPosY(); 
  float width = tb->getWidth() * mRelWidth;
  float height = tb->getHeight() * mRelHeight;
  this->render(posx, posy, width, height);
}

void Button::render(float posx, float posy, float width, float height)
{
  //float rectposx = getPixelX(posx, posy, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE) + mRel_x;
  //float rectposy = getPixelY(posx, posy, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE) + mRel_y;
  float rectposx = posx + mRel_x;
  float rectposy = posy + mRel_y;
  renderTexture(mTexture, mRenderer, rectposx, rectposy, width, height);
  //render the title message
  if (mTitle != nullptr)
    {
      float title_scale = 0.7;
      mTitle->setActive(true);
      mTitle->setHeight(height * title_scale);
      mTitle->setWidth(width * title_scale);
      float tborder = (1.-0.8)/2.;
      //float tposx = getIsoX(rectposx + tborder * width, rectposy + tborder * height, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE);
      //float tposy = getIsoY(rectposx+ tborder * width, rectposy + tborder * height, cameraoffset_x, cameraoffset_y, zoom, TILE_SIZE);
      //float tposx = posx + mRel_x
      mTitle->setPosX( rectposx + tborder * width);
      mTitle->setPosY( rectposy + tborder * height);
      mTitle->render();
    }
}
