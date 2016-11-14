CXX = clang++
SDL = -framework SDL2 -framework SDL2_image -framework SDL2_ttf
CXXFLAGS = -Wall -c -Iinclude -Isrc -Iobj -Isrc/entity -Isrc/action/ -std=c++11
LDFLAGS = $(SDL)
EXE = bin/IsoMap.exe
CPPSRC := $(wildcard src/*.cpp)
CPPENTITY := $(wildcard src/entity/*.cpp)
CPPACTION := $(wildcard src/action/*.cpp)
CPPGRAPHICS := $(wildcard src/graphics/*.cpp)
CPPFILES := $(CPPSRC) $(CPPENTITY) $(CPPACTION) $(CPPGRAPHICS)
OBJFILES := $(addprefix src/,$(notdir $(CPPSRC:.cpp=.o))) $(addprefix src/entity/,$(notdir $(CPPENTITY:.cpp=.o))) $(addprefix src/action/,$(notdir $(CPPACTION:.cpp=.o))) $(addprefix src/graphics/,$(notdir $(CPPGRAPHICS:.cpp=.o)))

all: $(EXE)

$(EXE): main.o
	$(CXX) $(LDFLAGS) main.o $(OBJFILES) -g -o $(EXE)

main.o: $(OBJFILES) main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp	

clean:
	rm *.o 
	rm */*.o
	rm */*/*.o

depend: 
	makedepend -- $(CXXFLAGS) -- $(CPPFILES)
# DO NOT DELETE

src/Item.o: include/Item.h include/Sprite.h include/global.h
src/Item.o: include/texture.h include/logging.h include/Selectable.h
src/Item.o: include/TextLine.h include/TextMaker.h
src/ItemGroup.o: include/ItemGroup.h include/Item.h include/Sprite.h
src/ItemGroup.o: include/global.h include/texture.h include/logging.h
src/ItemGroup.o: include/Selectable.h include/TextLine.h include/TextMaker.h
src/Map.o: include/Map.h include/Sprite.h include/global.h include/texture.h
src/Map.o: include/logging.h
src/Selectable.o: include/Selectable.h
src/Timer.o: include/Timer.h
src/logging.o: include/logging.h
src/entity/Building.o: include/Building.h include/FunctionCaller.h
src/entity/Building.o: include/ArgContainer.h include/EntityAction.h
src/entity/Building.o: include/EntityHP.h include/Entity.h include/Sprite.h
src/entity/Building.o: include/global.h include/texture.h include/logging.h
src/entity/Building.o: include/Action.h include/ActionGroup.h
src/entity/Building.o: include/ItemGroup.h include/Item.h
src/entity/Building.o: include/Selectable.h
src/entity/Entity.o: include/Sprite.h include/global.h include/texture.h
src/entity/Entity.o: include/logging.h include/Entity.h include/Action.h
src/entity/Entity.o: include/FunctionCaller.h include/ArgContainer.h
src/entity/EntityAction.o: include/EntityAction.h include/EntityHP.h
src/entity/EntityAction.o: include/Entity.h include/Sprite.h include/global.h
src/entity/EntityAction.o: include/texture.h include/logging.h
src/entity/EntityAction.o: include/Action.h include/FunctionCaller.h
src/entity/EntityAction.o: include/ArgContainer.h include/ActionGroup.h
src/entity/EntityAction.o: include/ItemGroup.h include/Item.h
src/entity/EntityAction.o: include/Selectable.h include/Attack.h
src/entity/EntityAction.o: include/InfoAction.h include/Resource.h
src/entity/EntityAction.o: include/EntityGroup.h include/SpriteGroup.h
src/entity/EntityAction.o: include/TextLine.h include/TextMaker.h
src/entity/EntityGroup.o: include/EntityGroup.h include/Entity.h
src/entity/EntityGroup.o: include/Sprite.h include/global.h include/texture.h
src/entity/EntityGroup.o: include/logging.h include/Action.h
src/entity/EntityGroup.o: include/FunctionCaller.h include/ArgContainer.h
src/entity/EntityGroup.o: include/SpriteGroup.h
src/entity/EntityHP.o: include/EntityHP.h include/Entity.h include/Sprite.h
src/entity/EntityHP.o: include/global.h include/texture.h include/logging.h
src/entity/EntityHP.o: include/Action.h include/FunctionCaller.h
src/entity/EntityHP.o: include/ArgContainer.h include/Attack.h
src/entity/Resource.o: include/Resource.h include/Entity.h include/Sprite.h
src/entity/Resource.o: include/global.h include/texture.h include/logging.h
src/entity/Resource.o: include/Action.h include/FunctionCaller.h
src/entity/Resource.o: include/ArgContainer.h include/EntityGroup.h
src/entity/Resource.o: include/SpriteGroup.h include/InfoAction.h
src/entity/Resource.o: include/TextLine.h include/TextMaker.h
src/entity/Unit.o: include/Unit.h include/EntityAction.h include/EntityHP.h
src/entity/Unit.o: include/Entity.h include/Sprite.h include/global.h
src/entity/Unit.o: include/texture.h include/logging.h include/Action.h
src/entity/Unit.o: include/FunctionCaller.h include/ArgContainer.h
src/entity/Unit.o: include/ActionGroup.h include/ItemGroup.h include/Item.h
src/entity/Unit.o: include/Selectable.h include/Movement.h
src/action/Action.o: include/Action.h include/FunctionCaller.h
src/action/Action.o: include/ArgContainer.h include/EntityAction.h
src/action/Action.o: include/EntityHP.h include/Entity.h include/Sprite.h
src/action/Action.o: include/global.h include/texture.h include/logging.h
src/action/Action.o: include/ActionGroup.h include/ItemGroup.h include/Item.h
src/action/Action.o: include/Selectable.h include/PopMenu.h include/Button.h
src/action/Action.o: include/TextLine.h include/TextMaker.h
src/action/Action.o: include/DisplayPiece.h include/Map.h include/Menu.h
src/action/Action.o: include/TextBox.h
src/action/ActionGroup.o: include/ActionGroup.h include/Action.h
src/action/ActionGroup.o: include/FunctionCaller.h include/ArgContainer.h
src/action/Attack.o: include/Action.h include/FunctionCaller.h
src/action/Attack.o: include/ArgContainer.h include/Movement.h
src/action/Attack.o: include/EntityAction.h include/EntityHP.h
src/action/Attack.o: include/Entity.h include/Sprite.h include/global.h
src/action/Attack.o: include/texture.h include/logging.h
src/action/Attack.o: include/ActionGroup.h include/ItemGroup.h include/Item.h
src/action/Attack.o: include/Selectable.h include/Unit.h include/Attack.h
src/action/Attack.o: include/Map.h include/FunctionCaller.H
src/action/InfoAction.o: include/Action.h include/FunctionCaller.h
src/action/InfoAction.o: include/ArgContainer.h include/InfoAction.h
src/action/InfoAction.o: include/Resource.h include/Entity.h include/Sprite.h
src/action/InfoAction.o: include/global.h include/texture.h include/logging.h
src/action/InfoAction.o: include/EntityGroup.h include/SpriteGroup.h
src/action/InfoAction.o: include/InfoMenu.h include/EntityAction.h
src/action/InfoAction.o: include/EntityHP.h include/ActionGroup.h
src/action/InfoAction.o: include/ItemGroup.h include/Item.h
src/action/InfoAction.o: include/Selectable.h include/Menu.h
src/action/InfoAction.o: include/DisplayPiece.h include/TextMaker.h
src/action/InfoAction.o: include/Button.h include/TextLine.h
src/action/InfoAction.o: include/TextBox.h include/SubMenu.h
src/action/Movement.o: include/Action.h include/FunctionCaller.h
src/action/Movement.o: include/ArgContainer.h include/Movement.h
src/action/Movement.o: include/EntityAction.h include/EntityHP.h
src/action/Movement.o: include/Entity.h include/Sprite.h include/global.h
src/action/Movement.o: include/texture.h include/logging.h
src/action/Movement.o: include/ActionGroup.h include/ItemGroup.h
src/action/Movement.o: include/Item.h include/Selectable.h include/Unit.h
src/graphics/Button.o: include/Action.h include/FunctionCaller.h
src/graphics/Button.o: include/ArgContainer.h include/texture.h
src/graphics/Button.o: include/logging.h include/Map.h include/Sprite.h
src/graphics/Button.o: include/global.h include/TextLine.h
src/graphics/Button.o: include/TextMaker.h include/Menu.h
src/graphics/Button.o: include/DisplayPiece.h include/Button.h
src/graphics/Button.o: include/TextBox.h
src/graphics/DisplayPiece.o: include/texture.h include/logging.h
src/graphics/DisplayPiece.o: include/Map.h include/Sprite.h include/global.h
src/graphics/DisplayPiece.o: include/Menu.h include/DisplayPiece.h
src/graphics/DisplayPiece.o: include/TextMaker.h include/Button.h
src/graphics/DisplayPiece.o: include/TextLine.h include/FunctionCaller.h
src/graphics/DisplayPiece.o: include/ArgContainer.h include/TextBox.h
src/graphics/DisplayPiece.o: include/SubMenu.h
src/graphics/InfoMenu.o: include/InfoMenu.h include/EntityAction.h
src/graphics/InfoMenu.o: include/EntityHP.h include/Entity.h include/Sprite.h
src/graphics/InfoMenu.o: include/global.h include/texture.h include/logging.h
src/graphics/InfoMenu.o: include/Action.h include/FunctionCaller.h
src/graphics/InfoMenu.o: include/ArgContainer.h include/ActionGroup.h
src/graphics/InfoMenu.o: include/ItemGroup.h include/Item.h
src/graphics/InfoMenu.o: include/Selectable.h include/Menu.h
src/graphics/InfoMenu.o: include/DisplayPiece.h include/TextMaker.h
src/graphics/InfoMenu.o: include/Button.h include/TextLine.h
src/graphics/InfoMenu.o: include/TextBox.h include/Resource.h
src/graphics/InfoMenu.o: include/EntityGroup.h include/SpriteGroup.h
src/graphics/InfoMenu.o: include/SubMenu.h
src/graphics/Menu.o: include/texture.h include/logging.h include/Map.h
src/graphics/Menu.o: include/Sprite.h include/global.h include/Menu.h
src/graphics/Menu.o: include/DisplayPiece.h include/TextMaker.h
src/graphics/Menu.o: include/Button.h include/TextLine.h
src/graphics/Menu.o: include/FunctionCaller.h include/ArgContainer.h
src/graphics/Menu.o: include/TextBox.h include/SubMenu.h
src/graphics/MenuGroup.o: include/MenuGroup.h include/Menu.h
src/graphics/MenuGroup.o: include/DisplayPiece.h include/TextMaker.h
src/graphics/MenuGroup.o: include/global.h include/Button.h
src/graphics/MenuGroup.o: include/TextLine.h include/FunctionCaller.h
src/graphics/MenuGroup.o: include/ArgContainer.h include/TextBox.h
src/graphics/MenuGroup.o: include/PopMenu.h include/Map.h include/Sprite.h
src/graphics/MenuGroup.o: include/texture.h include/logging.h
src/graphics/MenuGroup.o: include/EntityAction.h include/EntityHP.h
src/graphics/MenuGroup.o: include/Entity.h include/Action.h
src/graphics/MenuGroup.o: include/ActionGroup.h include/ItemGroup.h
src/graphics/MenuGroup.o: include/Item.h include/Selectable.h
src/graphics/PopMenu.o: include/PopMenu.h include/Button.h include/TextLine.h
src/graphics/PopMenu.o: include/TextMaker.h include/global.h
src/graphics/PopMenu.o: include/DisplayPiece.h include/FunctionCaller.h
src/graphics/PopMenu.o: include/ArgContainer.h include/Map.h include/Sprite.h
src/graphics/PopMenu.o: include/texture.h include/logging.h
src/graphics/PopMenu.o: include/EntityAction.h include/EntityHP.h
src/graphics/PopMenu.o: include/Entity.h include/Action.h
src/graphics/PopMenu.o: include/ActionGroup.h include/ItemGroup.h
src/graphics/PopMenu.o: include/Item.h include/Selectable.h include/Menu.h
src/graphics/PopMenu.o: include/TextBox.h include/InfoAction.h
src/graphics/PopMenu.o: include/Resource.h include/EntityGroup.h
src/graphics/PopMenu.o: include/SpriteGroup.h
src/graphics/SelectionList.o: include/SelectionList.h include/Selectable.h
src/graphics/SelectionList.o: include/Menu.h include/DisplayPiece.h
src/graphics/SelectionList.o: include/TextMaker.h include/global.h
src/graphics/SelectionList.o: include/Button.h include/TextLine.h
src/graphics/SelectionList.o: include/FunctionCaller.h include/ArgContainer.h
src/graphics/SelectionList.o: include/TextBox.h
src/graphics/Sprite.o: include/Sprite.h include/global.h include/texture.h
src/graphics/Sprite.o: include/logging.h include/Map.h
src/graphics/SpriteGroup.o: include/SpriteGroup.h include/global.h
src/graphics/SpriteGroup.o: include/Sprite.h include/texture.h
src/graphics/SpriteGroup.o: include/logging.h
src/graphics/SubMenu.o: include/SubMenu.h include/Menu.h
src/graphics/SubMenu.o: include/DisplayPiece.h include/TextMaker.h
src/graphics/SubMenu.o: include/global.h include/Button.h include/TextLine.h
src/graphics/SubMenu.o: include/FunctionCaller.h include/ArgContainer.h
src/graphics/SubMenu.o: include/TextBox.h include/texture.h include/logging.h
src/graphics/TextBox.o: include/TextBox.h include/TextLine.h
src/graphics/TextBox.o: include/TextMaker.h include/global.h include/Button.h
src/graphics/TextBox.o: include/DisplayPiece.h include/FunctionCaller.h
src/graphics/TextBox.o: include/ArgContainer.h include/Menu.h
src/graphics/TextBox.o: include/texture.h include/logging.h
src/graphics/TextLine.o: include/texture.h include/logging.h
src/graphics/TextLine.o: include/TextMaker.h include/global.h
src/graphics/TextLine.o: include/TextLine.h include/Map.h include/Sprite.h
src/graphics/TextMaker.o: include/TextMaker.h include/global.h
src/graphics/TextMaker.o: include/logging.h
src/graphics/texture.o: include/texture.h include/logging.h
