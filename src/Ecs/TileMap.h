#pragma once
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include "BaseModel.h"
#include "../Headers/config.h"
#include "../Headers/GlobalVars.h"
#include "../Shader/Shader.h"
#include "../Windows/spx_FileDialog.h"

#include <fstream>
#include <sstream>

#include <filesystem>
namespace fs = std::filesystem;

struct TileTexture {
    GLuint id;
    std::string path;
    std::string name;
    GLuint tileTexID;
};


static GLuint quadVAO = 0;
static GLuint quadVBO = 0;

class TileMap : public BaseModel {
public:
GLuint tileTexture;

    TileMap(int idx, const std::string& name, int MapIdx) {
        index = idx;
        objectName = name;
        objectIndex = MapIdx;
        objectTypeID = MAP_IDX;

        // Setup quad once
        if (quadVAO == 0) {
            float vertices[] = {
                // positions   // texCoords
                0.0f, 1.0f,    0.0f, 1.0f,
                1.0f, 1.0f,    1.0f, 1.0f,
                1.0f, 0.0f,    1.0f, 0.0f,
                0.0f, 0.0f,    0.0f, 0.0f
            };
            unsigned int indices[] = { 0, 1, 2, 2, 3, 0 };

            glGenVertexArrays(1, &quadVAO);
            glBindVertexArray(quadVAO);

            glGenBuffers(1, &quadVBO);
            glBindBuffer(GL_ARRAY_BUFFER, quadVBO);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            GLuint EBO;
            glGenBuffers(1, &EBO);
            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)(2 * sizeof(float)));
            glEnableVertexAttribArray(1);
        }
    }

    ~TileMap() {

    }

    void LoadExampleMap() {
        mapData = {
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
        {1,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,1,},
        {1,0,0,0,0,0,0,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
        {1,0,0,0,0,0,0,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,},
        {1,0,0,0,0,0,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,},
        {1,0,0,0,0,1,1,1,0,0,0,0,0,0,0,1,1,0,0,0,0,0,0,1,0,0,0,0,0,0,1,},
        {1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,1,},
        {0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0 }
        };
    }

    void DrawMap(Shader& shader) {
        ShaderManager::SpriteShader->setInt("spriteTexture", 0);

        glBindTexture(GL_TEXTURE_2D, tileTexture);
        glBindVertexArray(quadVAO);

        float mapOffsetY = SCR_HEIGHT - (rows * tileSize + SetMapBaseHeight); // push down or up

        for (int y = 0; y < rows; ++y) {
            for (int x = 0; x < cols; ++x) {
                if (mapData[y][x] == 1) {
                    glm::vec2 pos = glm::vec2(
                        x * tileSize,
                        y * tileSize + mapOffsetY
                    );

                    glm::mat4 model = glm::mat4(1.0f);
                    model = glm::translate(model, glm::vec3(pos, 0.0f));
                    model = glm::scale(model, glm::vec3(tileSize, tileSize, 1.0f));

                    ShaderManager::SpriteShader->setMat4("model", model);
                    glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
                }
            }
        }

        glBindVertexArray(0);
        glBindTexture(GL_TEXTURE_2D, 0);

    }
private:

    int rows = 10;
    //int cols = 16;
    int cols = 31;
    float tileSize = 32.0f; // pixels
    std::vector<std::vector<int>> mapData;
    
};
// this will get all the tile textures from a selected folder
inline std::vector<TileTexture> loadTileTextureFromFolder(const std::string& folderPath) {
    std::vector<TileTexture> tile_textures;
    
    int id_counter = 0;

    for (const auto& entry : std::filesystem::directory_iterator(folderPath)) {
        if (!entry.is_regular_file()) continue;

        std::string ext = entry.path().extension().string();
        if (ext != ".png" && ext != ".jpg" && ext != ".bmp") continue;

        std::string imagePath = entry.path().string();
        int width, height, channels;
        unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channels, 4); // force 4 channels (RGBA)
        if (!data) {
            std::cerr << "Failed to load image: " << imagePath << "\n";
            continue;
        }

        GLuint textureID;
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);

        glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, width, height, 0, GL_RGBA, GL_UNSIGNED_BYTE, data);
        glGenerateMipmap(GL_TEXTURE_2D);

        // Texture settings
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

        stbi_image_free(data);

        TileTexture tile;
        tile.id = id_counter++;
        tile.path = imagePath;
        tile.name = entry.path().filename().string();
        tile.tileTexID = textureID;
        tile_textures.push_back(tile);
    }

    
    return tile_textures;
}

class TileEditor {
public:
    std::vector<TileTexture> tileTexture;
    bool TileLoaded = false;
    bool dialogType = true;

    void Render(std::vector<std::unique_ptr<BaseModel>>& selectedData) {

        if (ShowTileEditor) { // if this is true open the editor window
            ImGui::GetStyle().WindowRounding = 12.0f;
            ImGui::Begin("Map Editor", &ShowTileEditor);
            ImGui::InputText("Map Name", nameBuffer, IM_ARRAYSIZE(nameBuffer));
            ImGui::TextColored(COLOR_LIGHTBLUE, ICON_FA_EDIT " Map Editor");
            
            if (ImGui::CollapsingHeader(ICON_FA_MALE " Player ", ImGuiTreeNodeFlags_DefaultOpen)) {

            }
                if (ImGui::CollapsingHeader(ICON_FA_MAP " Level Map", ImGuiTreeNodeFlags_DefaultOpen)) {
                    if (ImGui::CollapsingHeader(ICON_FA_MAP " Level Map", ImGuiTreeNodeFlags_DefaultOpen)) {
                        ImGui::SliderInt("Grid Width", &gridWidth, 1, 100);
                        ImGui::SliderInt("Grid Height", &gridHeight, 1, 100);
                        ImGui::SliderFloat("Tile Size", &tileSize, 16.0f, 64.0f);

                        if (placedTiles.size() != gridWidth || placedTiles[0].size() != gridHeight) {
                            placedTiles = std::vector<std::vector<int>>(gridWidth, std::vector<int>(gridHeight, -1));
                        }

                        ImVec2 canvasPos = ImGui::GetCursorScreenPos();
                        ImVec2 canvasSize(gridWidth * tileSize, gridHeight * tileSize);
                        ImDrawList* drawList = ImGui::GetWindowDrawList();
                        ImVec2 mousePos = ImGui::GetIO().MousePos;

                        // Draw each cell
                        for (int y = 0; y < gridHeight; ++y) {
                            for (int x = 0; x < gridWidth; ++x) {
                                ImVec2 tileMin = ImVec2(canvasPos.x + x * tileSize, canvasPos.y + y * tileSize);
                                ImVec2 tileMax = ImVec2(tileMin.x + tileSize, tileMin.y + tileSize);

                                // Handle click
                                bool hovered = ImGui::IsMouseHoveringRect(tileMin, tileMax);
                                if (hovered && ImGui::IsMouseClicked(ImGuiMouseButton_Left)) {
                                    placedTiles[x][y] = selectedTileID;
                                }

                                // Draw tile texture if assigned
                                GLuint texID = 0;
                                for (const auto& t : tileTexture) {
                                    if (t.id == placedTiles[x][y]) {
                                        texID = t.tileTexID;
                                        break;
                                    }
                                }

                                if (texID != 0) {
                                    drawList->AddImage((ImTextureID)(intptr_t)texID, tileMin, tileMax);
                                }
                                else {
                                    drawList->AddRectFilled(tileMin, tileMax, IM_COL32(40, 40, 40, 255)); // empty tile
                                }

                                drawList->AddRect(tileMin, tileMax, IM_COL32(100, 100, 100, 255)); // grid border
                            }
                        }

                        ImGui::Dummy(canvasSize); // reserve space
                    }

                    
                }

            

            ImGui::SeparatorText("Map Level Tiles");
            if (ImGui::CollapsingHeader(ICON_FA_VIDEO" Tile Textures", ImGuiTreeNodeFlags_DefaultOpen)) {

                
                if (dialogType) {
                    ImGui::SeparatorText(" Tile Picker");
                    ImGui::TextColored(COLOR_LIGHTBLUE, ICON_FA_IMAGE " Available Tile Textures");

                    if (!TileLoaded) {                            // this is the folder
                        tileTexture = loadTileTextureFromFolder("Textures/");
                        TileLoaded = true;
                    }

                    int columns = 6;
                    int count = 0;
                    ImGui::BeginChild("TextureGrid", ImVec2(0, 300), true); // scrollable

                    for (const auto& tile : tileTexture) {
                        ImGui::PushID(tile.id);
                        if (ImGui::ImageButton((void*)(intptr_t)tile.tileTexID, ImVec2(64, 64))) {

                            selectedTileID = tile.id; // New bit                           

                           /* if (objectUpdateIndex != -1) {

                                ObjectVector[objectUpdateIndex]->textureID = tile.id;
                                creatTileTex = tile.id;
                                ShouldUpdateTile = true;


                            }*/
                        }
                        ImGui::PopID();

                        if (++count % columns != 0) ImGui::SameLine();
                    }

                    ImGui::EndChild();
                }
            }

            // Save button 
            spx_FileDialog saveFileDialog;
            IsMap = true;
            if (ImGui::Button("Save Map")) { 
                std::string mapPath = saveFileDialog.saveFileDialog();

                if (!mapPath.empty()) {
                    // Add .spm if missing
                    if (mapPath.find(".spm") == std::string::npos) {
                        mapPath += ".spm";
                    }

                    std::ofstream outFile(mapPath); // Use the selected file path
                    if (outFile.is_open()) {
                        for (int y = 0; y < gridHeight; ++y) {
                            for (int x = 0; x < gridWidth; ++x) {
                                outFile << placedTiles[x][y];
                                if (x < gridWidth - 1)
                                    outFile << " ";
                            }
                            outFile << "\n";
                        }
                        outFile.close();
                        std::cout << "Map saved: " << mapPath << std::endl;
                    }
                    else {
                        std::cerr << "Failed to open file for saving: " << mapPath << std::endl;
                    }
                }
                else {
                    std::cout << "Save canceled.\n";
                }

                IsMap = false;
            }

            ImGui::SameLine();

            // Load Map 
            spx_FileDialog openFileDialog;
            IsMap = true; // Set this before calling the dialog
            if (ImGui::Button("Load Map")) {
                    std::string mapPath = openFileDialog.openFileDialog();  //  Get selected path from dialog

                    if (!mapPath.empty()) {
                        std::ifstream inFile(mapPath); //  Use returned path
                        if (inFile.is_open()) {
                            std::string line;
                            int y = 0;
                            while (std::getline(inFile, line) && y < gridHeight) {
                                std::istringstream ss(line);
                                int value;
                                int x = 0;
                                while (ss >> value && x < gridWidth) {
                                    placedTiles[x][y] = value;
                                    ++x;
                                }
                                ++y;
                            }
                            inFile.close();
                            std::cout << "Map loaded: " << mapPath << "\n";
                        }
                        else {
                            std::cerr << "Failed to open map file: " << mapPath << "\n";
                        }
                    }
                        else {
                        std::cout << "Load canceled.\n";
                        }
                    IsMap = false;
            }

            


            if (ImGui::Button("Close Editor")) {
                ShowTileEditor = false;
            }

            ImGui::End();
        }

    }
private:

    int selectedTileID = -1; // stores ID of the selected tile
    int gridWidth = 16;
    int gridHeight = 16;
    float tileSize = 32.0f;
    std::vector<std::vector<int>> placedTiles;

};
