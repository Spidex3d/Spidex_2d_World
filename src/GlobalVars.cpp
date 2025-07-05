#include "Headers\GlobalVars.h"

std::vector<std::unique_ptr<BaseModel>> ObjectVector; // the vector for all Models

const int TILE_GRASS = 1;

const int MAP_IDX = 1;
const int PLAYER_SPRITE = 2;
bool ShouldAddPlayerSprite = false;
bool ShouldUpdatePlayerSprite = false;
bool ShouldAddTileMap = false;
bool ShouldUpdateTile = false;
bool ShouldUpdateTileMap = false;

int SetMapBaseHeight = 100;  // this is the height from the bottom of the window 

int TileMapNo = 0;

int SpriteIdx = 0;
int MapIdx = 0;

// #### Map Editor ######
bool showGrid = false;
bool ShowTileEditor = false;
unsigned int creatTileTex = 0;

int objectUpdateIndex = 0; 

// Selecting objects
bool SelectedObject = false;

unsigned int creatMap = 0;      // this only for the image that shows on the edit window for the selected texture

// ###### Textures ##############
bool IsTexture = true; // for the open dialoge box the default is for textures

// ###### Textures ##############

int currentIndex = -1;

float object_Pos[3] = { 0.0f, 0.0f, 0.0f };
float object_Scale[3] = { 1.0f, 1.0f, 1.0f };
float object_Rotation[3] = { 0.0f, 0.0f, 0.0f };
