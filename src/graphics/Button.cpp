#include "Action.h"
#include "texture.h"
#include "SDL.h"
#include "SDL_image.h"
#include "Map.h"
#include "TextLine.h"

#include "Menu.h"
#include "DisplayPiece.h"

#include "Button.h"

/*Button::Button(float rel_x, float rel_y, float rel_w, float rel_h, std::string title, int outcome, SDL_Renderer *renderer, SDL_Window *window,
	       TextMaker * TextHandler)
	       : RelativeDisplayPiece( rel_x, rel_y, rel_w, rel_h )
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
  std::cout << "Button::Button: INFO: End of first constructor" << std::endl;
  }*/

Button::Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, int outcome, DisplayPiece * parent)
  : DisplayPiece(rel_x, rel_y, rel_width, rel_height, parent)
{
  /*mTexture = parent->mTexture;
  mRenderer = nullptr;
  mWindow = nullptr;
  mTitle = nullptr;*/

  //FunctionCaller funcCaller = nullptr;
  mFunctionCaller = nullptr;
  ArgContainer args = ArgContainer();
  //setFunctionCaller(funcCaller);
  setArgContainer(args);

  setParent(parent);

  mTexture = loadTexture("res/images/menu/button_0_0.png", mRenderer, true);

  //mRenderer = renderer;
  //mWindow = window;

  //mRect = new SDL_Rect();

  /*  setRelPosX(rel_x);
  setRelPosY(rel_y);
  setRelWidth(rel_w);
  setRelHeight(rel_h);*/

  setHighlight(false);

  setTitleString(title);
  //mTextMaker = TextHandler;
  makeTitleTextLine();

  setOutcome(outcome);

  setPressed(false);


}

Button::Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, int outcome, Menu * menu)
  : Button( rel_x, rel_y, rel_width, rel_height, title, outcome, dynamic_cast<DisplayPiece*>(menu) )
{
  //  menu->addButton(this);
}

Button::Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, FunctionCaller caller, ArgContainer args,
	       DisplayPiece * parent)
  : Button(rel_x, rel_y, rel_width, rel_height, title, 0, parent)
{
  setArgContainer(args);
  setFunctionCaller(caller);
}

Button::Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, FunctionCaller caller, ArgContainer args,
	       Menu * menu)
  : Button( rel_x, rel_y, rel_width, rel_height, title, 0, dynamic_cast<DisplayPiece*>(menu) )
{
  setArgContainer(args);
  setFunctionCaller(caller);
  //  menu->addButton(this);
}


/*Button::Button(float rel_x, float rel_y, float rel_width, float rel_height, std::string title, FunctionCaller caller, ArgContainer args,
	       SDL_Renderer *renderer, SDL_Window *window, TextMaker * TextHandler)
  : Button::Button(rel_x, rel_y, rel_width, rel_height, title, 0, renderer, window, TextHandler )
{
  setArgContainer(args);
  setFunctionCaller(caller);
  }*/


Button::~Button()
{
  std::cout << "INFO: Button::~Button: Deleting Button." << std::endl;
}

bool Button::collide(float x_screen, float y_screen)
{
  //need to figure out the screen pos of the button corner and its width and heigh in pixels
  /*  float posx = parent->getPosX();
  float posy = parent->getPosY();
  float width = parent->getWidth() * this->getRelWidth();
  float height = parent->getHeight() * this->getRelHeight();
  float rposx = posx + getRelX();
  float rposy = posy + getRelY();*/
  setPositions();
  float rposx = getPosX();
  float rposy = getPosY();
  float width = getWidth();
  float height = getHeight();
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
  setPressed(false);
  return funcReturn;
}

/*void Button::render()
{
  setPositions();
  this->render(posx, posy, width, height);
  }*/

 /*void Button::render(TextBox * tb)
{
  float posx = tb->getPosX();
  float posy = tb->getPosY();
  float width = tb->getWidth() * mRelWidth;
  float height = tb->getHeight() * mRelHeight;
  this->render(posx, posy, width, height);
  }*/

void Button::render(bool resetPos)
{
  //std::cout << "INFO: Button::render: Rendering the Button" << std::endl;
  float posx = getPosX();
  float posy = getPosY();
  float height = getHeight();
  float width = getWidth();
  if ( resetPos )
    setPositions();
  posx = getPosX();
  posy = getPosY();
  height = getHeight();
  width = getWidth();
  renderTexture( mTexture, mRenderer, posx, posy, width, height );
  //render the title message
  if (mTitle != nullptr)
    {
      float title_scale = 0.7;
      mTitle->setActive(true);
      mTitle->setHeight(height * title_scale);
      mTitle->setWidth(width * title_scale);
      float tborder = (1.-0.8)/2.;
      mTitle->setPosX( posx + tborder * width);
      mTitle->setPosY( posy + tborder * height);
      mTitle->render();
    }
}
