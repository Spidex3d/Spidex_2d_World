#pragma once
#include <vector>
#include <memory>
#include "../Ecs/BaseModel.h"

extern std::vector<std::unique_ptr<BaseModel>> ObjectVector; // the vector for all Models

extern const int MAP_IDX;
extern const int PLAYER_SPRITE;

extern bool ShouldAddPlayerSprite;		// add a player
extern bool ShouldUpdatePlayerSprite;		// update player
extern bool ShouldAddTileMap;		// add a map
extern bool ShouldUpdateTileMap;	// change map
extern int SetMapBaseHeight;

extern int TileMapNo;

extern int SpriteIdx;
extern int MapIdx;

// #### Map Editor ######
extern bool showGrid; // show grid and enabel editing


extern int objectUpdateIndex; // this is in use

// Selecting objects
extern bool SelectedObject;

//############# objects maps
extern unsigned int creatMap;	// this only for the image that shows on the edit window

// ###### Textures ##############
extern bool IsTexture;  // for the open dialoge box

// ###### Textures ##############

extern int currentIndex;

extern bool show_settings_window;

extern float object_Pos[3];
extern float object_Scale[3];
extern float object_Rotation[3];
// End of Cube
