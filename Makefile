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
	$(CXX) $(LDFLAGS) main.o $(OBJFILES) -o $(EXE)

main.o: $(OBJFILES) main.cpp
	$(CXX) $(CXXFLAGS) -c main.cpp	

clean:
	rm *.o && rm $(EXE)

depend: 
	makedepend -- $(CXXFLAGS) -- $(CPPFILES)
# DO NOT DELETE

src/Item.o: include/Item.h include/Sprite.h include/global.h
src/Item.o: include/texture.h include/logging.h
src/ItemGroup.o: include/ItemGroup.h include/Item.h include/Sprite.h
src/ItemGroup.o: include/global.h include/texture.h include/logging.h
src/Map.o: include/Map.h include/Sprite.h include/global.h include/texture.h
src/Map.o: include/logging.h
src/Timer.o: include/Timer.h
src/logging.o: include/logging.h
src/entity/Entity.o: include/Sprite.h include/global.h include/texture.h
src/entity/Entity.o: include/logging.h include/Entity.h include/Action.h
src/entity/Entity.o: include/FunctionCaller.h
src/entity/EntityAction.o: include/EntityAction.h include/EntityHP.h
src/entity/EntityAction.o: include/Entity.h include/Sprite.h include/global.h
src/entity/EntityAction.o: include/texture.h include/logging.h
src/entity/EntityAction.o: include/Action.h include/FunctionCaller.h
src/entity/EntityAction.o: include/ActionGroup.h include/ItemGroup.h
src/entity/EntityAction.o: include/Item.h include/Attack.h
src/entity/EntityGroup.o: include/EntityGroup.h include/Entity.h
src/entity/EntityGroup.o: include/Sprite.h include/global.h include/texture.h
src/entity/EntityGroup.o: include/logging.h include/Action.h
src/entity/EntityGroup.o: include/FunctionCaller.h include/SpriteGroup.h
src/entity/EntityHP.o: include/EntityHP.h include/Entity.h include/Sprite.h
src/entity/EntityHP.o: include/global.h include/texture.h include/logging.h
src/entity/EntityHP.o: include/Action.h include/FunctionCaller.h
src/entity/EntityHP.o: include/Attack.h
src/entity/Unit.o: include/Unit.h include/EntityAction.h include/EntityHP.h
src/entity/Unit.o: include/Entity.h include/Sprite.h include/global.h
src/entity/Unit.o: include/texture.h include/logging.h include/Action.h
src/entity/Unit.o: include/FunctionCaller.h include/ActionGroup.h
src/entity/Unit.o: include/ItemGroup.h include/Item.h include/Movement.h
src/action/Action.o: include/Action.h include/FunctionCaller.h
src/action/Action.o: include/EntityAction.h include/EntityHP.h
src/action/Action.o: include/Entity.h include/Sprite.h include/global.h
src/action/Action.o: include/texture.h include/logging.h
src/action/Action.o: include/ActionGroup.h include/ItemGroup.h include/Item.h
src/action/Action.o: include/PopMenu.h include/Button.h include/Message.h
src/action/Action.o: include/TextMaker.h include/Map.h include/Menu.h
src/action/ActionGroup.o: include/ActionGroup.h include/Action.h
src/action/ActionGroup.o: include/FunctionCaller.h
src/action/Attack.o: include/Action.h include/FunctionCaller.h
src/action/Attack.o: include/Movement.h include/EntityAction.h
src/action/Attack.o: include/EntityHP.h include/Entity.h include/Sprite.h
src/action/Attack.o: include/global.h include/texture.h include/logging.h
src/action/Attack.o: include/ActionGroup.h include/ItemGroup.h include/Item.h
src/action/Attack.o: include/Unit.h include/Attack.h include/Map.h
src/action/Attack.o: include/FunctionCaller.H
src/action/Movement.o: include/Action.h include/FunctionCaller.h
src/action/Movement.o: include/Movement.h include/EntityAction.h
src/action/Movement.o: include/EntityHP.h include/Entity.h include/Sprite.h
src/action/Movement.o: include/global.h include/texture.h include/logging.h
src/action/Movement.o: include/ActionGroup.h include/ItemGroup.h
src/action/Movement.o: include/Item.h include/Unit.h
src/graphics/Button.o: include/Button.h include/Message.h include/TextMaker.h
src/graphics/Button.o: include/global.h include/FunctionCaller.h
src/graphics/Button.o: include/Action.h include/texture.h include/logging.h
src/graphics/Button.o: include/Menu.h include/Map.h include/Sprite.h
src/graphics/Menu.o: include/Menu.h include/Button.h include/Message.h
src/graphics/Menu.o: include/TextMaker.h include/global.h
src/graphics/Menu.o: include/FunctionCaller.h include/texture.h
src/graphics/Menu.o: include/logging.h include/Map.h include/Sprite.h
src/graphics/MenuGroup.o: include/MenuGroup.h include/Menu.h include/Button.h
src/graphics/MenuGroup.o: include/Message.h include/TextMaker.h
src/graphics/MenuGroup.o: include/global.h include/FunctionCaller.h
src/graphics/MenuGroup.o: include/PopMenu.h include/Map.h include/Sprite.h
src/graphics/MenuGroup.o: include/texture.h include/logging.h
src/graphics/MenuGroup.o: include/EntityAction.h include/EntityHP.h
src/graphics/MenuGroup.o: include/Entity.h include/Action.h
src/graphics/MenuGroup.o: include/ActionGroup.h include/ItemGroup.h
src/graphics/MenuGroup.o: include/Item.h
src/graphics/Message.o: include/texture.h include/logging.h
src/graphics/Message.o: include/TextMaker.h include/global.h
src/graphics/Message.o: include/Message.h include/Map.h include/Sprite.h
src/graphics/PopMenu.o: include/PopMenu.h include/Button.h include/Message.h
src/graphics/PopMenu.o: include/TextMaker.h include/global.h
src/graphics/PopMenu.o: include/FunctionCaller.h include/Map.h
src/graphics/PopMenu.o: include/Sprite.h include/texture.h include/logging.h
src/graphics/PopMenu.o: include/EntityAction.h include/EntityHP.h
src/graphics/PopMenu.o: include/Entity.h include/Action.h
src/graphics/PopMenu.o: include/ActionGroup.h include/ItemGroup.h
src/graphics/PopMenu.o: include/Item.h include/Menu.h
src/graphics/Sprite.o: include/Sprite.h include/global.h include/texture.h
src/graphics/Sprite.o: include/logging.h include/Map.h
src/graphics/SpriteGroup.o: include/SpriteGroup.h include/global.h
src/graphics/SpriteGroup.o: include/Sprite.h include/texture.h
src/graphics/SpriteGroup.o: include/logging.h
src/graphics/TextMaker.o: include/TextMaker.h include/global.h
src/graphics/TextMaker.o: include/logging.h
src/graphics/texture.o: include/texture.h include/logging.h
