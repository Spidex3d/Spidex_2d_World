#pragma once
#include "../Headers/Config.h"
#include <vector>
#include <memory>
#include <string>

#include <glm/glm.hpp>

#include "../Shader/ShaderManager.h"

#include <stb\stb_image.h>

#include "ObjectManager.h"
#include "TileMap.h"

#include "SelectedDataManager.h"


#include "../Headers/GlobalVars.h"

//#include "../Object_loader\spxObjectLoader.h"
//#include "../Object_loader\objLoader.h"

class EntityNodes
{
public:
	
	static EntityNodes* Instance();

	void Initialize();

	void ObjectEditor(std::vector<std::unique_ptr<BaseModel>>& selectedData);

	std::vector<std::unique_ptr<BaseModel>>& GetModels();

	void EntityManagmentSystem(std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex,
		int& index, int& objectIndex, int& indexTypeID);

	
	
	// Render the editor Grid
	//void RenderGrid(const glm::mat4& view, const glm::mat4& projection,
	//	std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex, int& Gridobjidx);

	void RenderScene(const glm::mat4& view, const glm::mat4& projection,
		std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex);
	
	//// Plane
	void RenderSprite(const glm::mat4& view, const glm::mat4& projection,
		 std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex, int& SpriteIdx);

	void RenderTileMap(const glm::mat4& view, const glm::mat4& projection,
		std::vector<std::unique_ptr<BaseModel>>& ObjectVector, int& currentIndex, int& MapIdx);
	


	
private:
	// Object Mesh Editor
	
	bool showObjectEditor = false;
	//char nameBuffer[128] = "";
	
	glm::mat4 modelMatrix;

		
	// End Object Mesh Editor
	//std::vector<std::unique_ptr<BaseModel>> ObjectVector; // the vector for all Models
	//std::vector<std::unique_ptr<BaseModel>> LightVector; // the vector for all Lights 
	//std::vector<std::unique_ptr<BaseModel>> SceneVector; // the vector for all Sky, water, 

	int objectIndex; // needed
	
	void onRightClick(int objectId) {
		if (ImGui::IsItemClicked(ImGuiMouseButton_Right)) {
			ImGui::OpenPopup(("NodePopup" + std::to_string(objectId)).c_str());
		}
	
	}
	
	float cam_pos_val[3] = { 0.0f, 0.0f, 0.0f };
	float cam_rot_val[3] = { 0.0f, 0.0f, 0.0f }; 
	float cam_scale_val[3] = { 0.0f, 0.0f, 0.0f }; 
	
};

