#include "EntityNodes.h"
#include "../Windows/spx_FileDialog.h"

unsigned int loadTexture(const std::string& filePath);

EntityNodes* EntityNodes::Instance() {
    static EntityNodes component;
    return &component;
}

void EntityNodes::Initialize()
{
    BaseModel* selectedData = nullptr;  // Define the external variable
        
    // Add The Default editor grid on start up                       TO DO ADD THIS TO SETTINGS
    //ObjectVector.push_back(std::make_unique<MainGrid>(0, "Main Grid", grid_square, grid_size));
   
}

void EntityNodes::ObjectEditor(std::vector<std::unique_ptr<BaseModel>>& selectedData)
{
    if (showObjectEditor) { // if this is true open the editor window
        ImGui::Begin("Mesh Object Editor", &showObjectEditor);
        ImGui::InputText("Object Name", nameBuffer, IM_ARRAYSIZE(nameBuffer));
        ImGui::TextColored(COLOR_LIGHTBLUE, ICON_FA_EDIT " Mesh Editor");
        ImGui::SeparatorText("Object Editor");

        ImGui::BeginTable("Edit Table", 1, ImGuiTableFlags_Reorderable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders);

        ImGui::TableNextColumn();
       
        // Retrieve the current position and scale from the selected object
        ImGui::DragFloat3("##pos", object_Pos, 0.0f, 0.0f, 0.0f);       
        ImGui::SameLine();
        if (ImGui::Button("Reset_Position")) {
            object_Pos[0] = 0.0f, object_Pos[1] = 0.0f, object_Pos[2] = 0.0f;
        }
        
        ImGui::TableNextRow();
        ImGui::TableNextColumn();

        ImGui::DragFloat3("##Scale", object_Scale, 0.0f, 0.0f, 0.0f);
        ImGui::SameLine();
        if (ImGui::Button("Reset Scale")) {
            object_Scale[0], object_Scale[1], object_Scale[2];
        }

        ImGui::TableNextRow();
        ImGui::TableNextColumn();
        
        ImGui::DragFloat3("##Rot", object_Rotation, 0.0f, 0.0f, 0.0f);
        ImGui::SameLine();
        if (ImGui::Button("Reset Rotation")) {
            object_Rotation[0] = 0.0f, object_Rotation[1] = 0.0f, object_Rotation[2] = 0.0f;
        }

        ImGui::EndTable();
        // put an if in here
        ImGui::TextColored(COLOR_LIGHTBLUE, ICON_FA_IMAGE " Texture Editor");
        ImGui::SeparatorText(" Texture Editor");
       
        // load the texture
        spx_FileDialog openDialog;
        if (ImGui::Button("Set New Texture")) {
            std::string myTexturePath = openDialog.openFileDialog();
            if (!myTexturePath.empty()) {
                std::cout << "Texture path selected: " << myTexturePath << std::endl;
                objectUpdateIndex = SelectedDataManager::Instance().GetSelectedData()->objectIndex; // just added
                if (objectUpdateIndex != -1) {
                    std::cout << "Updating texture for cube index: " << objectUpdateIndex << std::endl;
                     ObjectVector[objectUpdateIndex]->textureID = loadTexture(myTexturePath);
                   
                    std::cout << "New texture ID: " << ObjectVector[objectUpdateIndex]->textureID << std::endl;

                    creatMap = loadTexture((myTexturePath).c_str()); // this is the image on the object edit window
                }
                else {
                    std::cout << "objectUpdateIndex is not set correctly." << std::endl;
                }
            }
            else {
                std::cout << "No texture path selected." << std::endl;
            }
        }


        if (creatMap != 0) {
            ImGui::Text("Your selected Texture");
            ImGui::Image((void*)(intptr_t)creatMap, ImVec2(65, 65));
        }
        else {
           // std::cout << "No texture loaded." << std::endl;
        }
        

        // Update button                           
        if (ImGui::Button("Update")) { // Update the object's name 

            // Check if nameBuffer is not empty
            if (strlen(nameBuffer) > 0) {
                if (SelectedDataManager::Instance().GetSelectedData() != nullptr) {
                    SelectedDataManager::Instance().GetSelectedData()->objectName = std::string(nameBuffer);
                    // THIS is what we are working on
                    if (SelectedDataManager::Instance().GetSelectedData()->objectTypeID != -1) {


                        switch (SelectedDataManager::Instance().GetSelectedData()->objectTypeID) {
                        case 0: // Grid open the settings window
                            //show_settings_window = true;
                            break;
                        
                        case 1: // Player                     
                            ShouldUpdatePlayerSprite = true;
                            
                            break;
                        case 2: // Plane
                            

                           
                            break;
                        case 3: // Circle
                            
                            break;
                        case 4: // Line
                            break;
                        case 5: // OBJ_SPHERE
                            break;
                        case 6: // OBJ_CYLINDER
                            break;
                        case 7: // OBJ_TORUS
                            break;
                        case 8: //  Grid not the editor grid !
                            break;
                        case 9: //  Cone                        
                            break;
                        case 10: // pyramid
                            
                            break;
                        case 11: //  Triangel                        
                            break;
                        case 12: // Obj Models
                            
                            break;
                        }
                    }


                    objectUpdateIndex = SelectedDataManager::Instance().GetSelectedData()->objectIndex; // Ensure this is set correctly

                    std::cout << "Object update index set to: " << objectUpdateIndex << std::endl;

                    std::cout << "Selected " << SelectedDataManager::Instance().GetSelectedData()->objectName << " Index " <<
                        SelectedDataManager::Instance().GetSelectedData()->objectIndex << std::endl;
                } 
                
            }
                showObjectEditor = false;
                
                creatMap = 0;
               
        }
       
        ImGui::End();
    }
    
}

std::vector<std::unique_ptr<BaseModel>>& EntityNodes::GetModels()
{
    return ObjectVector;
}

//void EntityNodes::EntityManagmentSystem(std::vector<std::unique_ptr<BaseModel>>& ObjectVector,
//    int& currentIndex, int& index, int& objectIndex, int& indexTypeID) {
//    ImGui::Begin("Entity Management System"); // start of the window
//
//    
//    ImGui::SeparatorText("Scene Collection");
//
//    if (ImGui::BeginTabBar("##Main", ImGuiTabBarFlags_None))
//    {
//        if (ImGui::BeginTabItem("Scene Tree"))
//        {
//           
//            auto flags = ImGuiTreeNodeFlags_DefaultOpen;
//            if (ImGui::TreeNodeEx("Editor Scene", flags)) {
//
//                for (const auto& data : ObjectVector) {
//                    
//                    ImGuiTreeNodeFlags nodeFlags = flags | (SelectedDataManager::Instance().GetSelectedData() == data.get() ? ImGuiTreeNodeFlags_Selected : 0);
//
//                    bool nodeOpen = ImGui::TreeNodeEx((void*)(intptr_t)data->objectIndex, nodeFlags,
//                        "  %s : %d : Type ID : %d",
//                       // %d : %s : %d : Type ID : %d",
//                        //"Object: %d : %s : %d : Type ID : %d",
//                        data->objectName.c_str(), data->objectIndex, data->objectTypeID);
//                       // data->index, data->objectName.c_str(), data->objectIndex, data->objectTypeID);
//                    // #####
//                   
//                    // #####
//                    if (ImGui::IsItemClicked()) {
//                        SelectedDataManager::Instance().SetSelectedData(data.get());
//                        data->isSelected = true;
//                        
//                        std::cout << "Data Selected was " << data->objectName.c_str() << " : " << data->objectIndex << std::endl;
//                    }
//
//                    if (ImGui::IsItemHovered()) {
//                        // Perform actions when the node is hovered
//                        ImGui::SetTooltip("Right click to Edit %s | %d", data->objectName.c_str(), data->objectIndex);
//                        
//                    }
//
//                    if (nodeOpen) {
//                        //this->onRightClick(data->objectIndex); // Pass a unique identifier
//                        this->onRightClick(data->index); // Pass a unique identifier
//
//                        if (ImGui::BeginPopup(("NodePopup" + std::to_string(data->index)).c_str())) {
//                            ImGui::TextColored(COLOR_LIGHTBLUE, ICON_FA_EDIT " ENTITY");
//                            ImGui::Separator(); // Draw a line
//                            if (ImGui::Selectable(ICON_FA_PEN_ALT " Edit")) {
//                                SelectedDataManager::Instance().SetSelectedData(data.get());
//
//                                // Copy the current name to the buffer
//                                 strncpy_s(nameBuffer, data->objectName.c_str(), sizeof(nameBuffer));
//                                 nameBuffer[sizeof(nameBuffer) - 1] = '\0';
//                                
//                               
//                                std::cout << "Object Selected To Edit " << data->objectName.c_str() << " : " << data->objectIndex << std::endl;
//                                
//                                switch (data.get()->objectTypeID) {
//                                case 0: // Grid
//                                    break;
//                                case 1: // cube
//                                    showObjectEditor = true;
//
//                                    std::cout << "Data Selected  is a Cube " << data->objectName.c_str() << " : " << data->objectIndex << std::endl;
//                                    LogInternals::Instance()->Debug("Data Selected  is a Cube");
//                                    break;
//                                case 2: // plane
//                                    showObjectEditor = true;
//                                    LogInternals::Instance()->Debug("Data Selected  is a plane");
//                                    break;
//                                case 3:
//                                    break;
//                                case 4: //
//                                   
//                                    break;
//                                case 5:
//                                    break;
//                                case 6:
//                                    break;
//                                case 7:
//                                    break;
//                                case 8:
//                                    showObjectEditor = true;
//                                    break;
//                                case 9:
//                                    showObjectEditor = true;
//                                    break;
//                                case 10:
//                                    showObjectEditor = true;
//                                    break;
//                                case 11: // pyramid
//                                    showObjectEditor = true;
//                                    LogInternals::Instance()->Debug("Data Selected  is a plane");
//                                    break;
//                                case 12: // 0bj file
//                                    showObjectEditor = true;
//                                    LogInternals::Instance()->Debug("Data Selected  is a obj file");
//                                    break;
//
//
//                                default:
//                                    std::cout << "Data Selected Something Else " << data->objectName.c_str() << " : " << data->objectIndex << std::endl;
//                                    break;
//
//                                }                                                                              
//                            
//                            
//                            }
//                            if (ImGui::Selectable(ICON_FA_PLUS " New")) {
//                                // open a window or popup to select the object
//                                std::cout << "Object To Add "  << std::endl;
//                            }
//                            if (ImGui::Selectable(ICON_FA_COPY " Clone")) {
//
//                                std::cout << "Data Selected To Clone " << data->objectName.c_str() << " : " << data->objectIndex << std::endl;
//                            }
//                            if (ImGui::Selectable(ICON_FA_TRASH_ALT " Delete")) {
//                                // open window to ask if your sure
//                                std::cout << "Data Selected To Delete " << data->objectName.c_str() << " : " << data->objectIndex << std::endl;
//                            }
//
//                            ImGui::EndPopup();
//                        }
//
//                        ImGui::TreePop();
//                                                
//                    }
//                    
//          
//                }
//                ImGui::TreePop();
//                                
//            }      
//
//            ImGui::EndTabItem();
//
//        }
//        // ###########################################  MAP EDITOR ##################################
//        if (ImGui::BeginTabItem("Map Editor"))
//        {
//            ImGui::SeparatorText("Scene Editor");
//            ImGui::Checkbox("Show Editor Grid", &showGrid); // show editor grid
//
//            
//            ImGui::Text("Spidex 2d Engine ", nullptr);
//
//            if (ImGui::CollapsingHeader(ICON_FA_VIDEO" Texture Settings", ImGuiTreeNodeFlags_DefaultOpen))
//            {
//                ImGui::BeginTable("Test Table", 1, ImGuiTableFlags_Reorderable | ImGuiTableFlags_NoSavedSettings | ImGuiTableFlags_Borders);
//
//                ImGui::TableNextColumn();
//
//                ImGui::Text("Tabel one");
//
//                ImGui::TableNextRow();
//                ImGui::TableNextColumn();
//
//                ImGui::Text("Tabel two");
//                
//
//                ImGui::EndTable();
//            }
//           
//            ImGui::SeparatorText("EDITOR");
//            if (ImGui::CollapsingHeader(ICON_FA_VIDEO" Player Settings", ImGuiTreeNodeFlags_DefaultOpen)) {
//
//            }
//           
//
//            ImGui::EndTabItem();
//
//        }
//
//        ImGui::EndTabItem();
//    }
//    
//    ImGui::End();
//}


       

// ####   Render Scene
void EntityNodes::RenderScene(const glm::mat4& view, const glm::mat4& projection,
    std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex)
{
   
    EntityNodes::RenderSprite(view, projection, ObjectVector, currentIndex, SpriteIdx);
    EntityNodes::RenderTileMap(view, projection, ObjectVector, currentIndex, MapIdx);
    
   
}

void EntityNodes::RenderSprite(const glm::mat4& view, const glm::mat4& projection,
    std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex, int& SpriteIdx)
{
    stbi_set_flip_vertically_on_load(true);

    if (ShouldAddPlayerSprite) {
        SpriteIdx = ObjectVector.size();

        //std::unique_ptr<PlaneModel> newPlane = std::make_unique<PlaneModel>(currentIndex++, "DefaultPlane", Planeobjidx++);
        std::unique_ptr<Sprite> newSprite = std::make_unique<Sprite>(currentIndex, "Player Sprite", SpriteIdx);
        switch (SpriteIdx) {
        case 0:
            newSprite->position = glm::vec3(0.0f, 0.0f, 0.0f);
            newSprite->scale = glm::vec3(100.0f, 100.0f, 1.0f);
            break;
        case 1:
            newSprite->position = glm::vec3(1.5f, 0.0f, 0.0f);
            newSprite->scale = glm::vec3(100.0f, 100.0f, 1.0f);
            break;

        case 2:
            newSprite->position = glm::vec3(2.0f, 0.0f, 0.0f);
            newSprite->scale = glm::vec3(100.0f, 100.0f, 1.0f);
            break;
        default:
            newSprite->position = glm::vec3(3.0f, 2.0f, 0.0f);
            newSprite->scale = glm::vec3(100.0f, 100.0f, 1.0f);
            break;
        }

        newSprite->modelMatrix = glm::mat4(1.0f);
        newSprite->modelMatrix = glm::translate(newSprite->modelMatrix, newSprite->position);
        newSprite->modelMatrix = glm::scale(newSprite->modelMatrix, newSprite->scale);

        newSprite->textureID = loadTexture("Textures/Brick.jpg");

        ObjectVector.push_back(std::move(newSprite));


        ShouldAddPlayerSprite = false; // Reset the flag after adding the plane
    }
    // ##########
    if (ShouldUpdatePlayerSprite) { // then we update the cube position and scale

        int selectedIndex = SelectedDataManager::Instance().GetSelectedData()->objectIndex;

        if (selectedIndex >= 0 && selectedIndex < ObjectVector.size()) {

            glm::vec3 newPlanePosition = glm::vec3(object_Pos[0], object_Pos[1], object_Pos[2]); // New position
            ObjectVector[selectedIndex]->position = newPlanePosition;

            glm::vec3 newPlaneScale = glm::vec3(object_Scale[0], object_Scale[1], object_Scale[2]); // New scale
            ObjectVector[selectedIndex]->scale = newPlaneScale;

            ObjectVector[selectedIndex]->modelMatrix = glm::mat4(1.0f);
            ObjectVector[selectedIndex]->modelMatrix = glm::translate(ObjectVector[selectedIndex]->modelMatrix, newPlanePosition);
            ObjectVector[selectedIndex]->modelMatrix = glm::scale(ObjectVector[selectedIndex]->modelMatrix, newPlaneScale);

        }

        ShouldUpdatePlayerSprite = false;
    }

    // ###########


    for (const auto& model : ObjectVector) {

        

        if (auto* plane = dynamic_cast<Sprite*>(model.get())) {
            ShaderManager::SpriteShader->Use();
            ShaderManager::SpriteShader->setMat4("projection", projection);
            ShaderManager::SpriteShader->setMat4("view", view);
            modelMatrix = glm::mat4(1.0f);
            ShaderManager::SpriteShader->setMat4("model", plane->modelMatrix);

            glActiveTexture(GL_TEXTURE0);
            glBindTexture(GL_TEXTURE_2D, plane->textureID);
            //
            plane->DrawSprite();
            glBindTexture(GL_TEXTURE_2D, 0);
        }
    }
}

void EntityNodes::RenderTileMap(const glm::mat4& view, const glm::mat4& projection,
    std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex, int& MapIdx)
{
    if (TileMapNo < 1) { // if TileMapNo = 0 load a map
        if (ShouldAddTileMap) {
            std::unique_ptr<TileMap> newMap = std::make_unique<TileMap>(currentIndex, "Main Map", MapIdx);

            // we will need to set the pos here I think
            //newMap->position = glm::vec3(0.0f, -1.0f, 0.0f);
            //newMap->scale = glm::vec3(100.0f, 100.0f, 1.0f);

           /* newMap->modelMatrix = glm::mat4(1.0f);
            newMap->modelMatrix = glm::translate(newMap->modelMatrix, newMap->position);
            newMap->modelMatrix = glm::scale(newMap->modelMatrix, newMap->scale);*/

            
            newMap->LoadExampleMap();

            newMap->tileTexture = loadTexture("Textures/Brick.jpg");

            ObjectVector.push_back(std::move(newMap));
            TileMapNo = 1; // only allow 1 map

            ShouldAddTileMap = false;
        }
    }

    if (ShouldUpdateTileMap) {
        // use this to change maps
    }

    for (const auto& model : ObjectVector) {

        if (auto* map = dynamic_cast<TileMap*>(model.get())) {
           
            ShaderManager::SpriteShader->Use();
            ShaderManager::SpriteShader->setMat4("view", view);
            ShaderManager::SpriteShader->setMat4("projection", projection);
            ShaderManager::SpriteShader->setInt("spriteTexture", 0);       
           
            map->DrawMap(*ShaderManager::SpriteShader);
                        
        }
    }

}




