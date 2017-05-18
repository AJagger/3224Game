/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* The Draw class joins the game logic and objects used in the rest of the engine with the logic and objects used in the renderer. This class is responsible 
* for converting and selecting the specific data needed to render the gameObjects and providing it to the Renderer.
*/

#include "stdafx.h"
#include "Draw.h"
#include "../../Frameworks/DataArray.cpp" //Temp fix to Linker Errors

Draw::Draw()
{
}


Draw::~Draw()
{
}

//Loop through the GameObjects, extract the render data and add it to the Renderer pipeline.
void Draw::RenderObjects(GameScene *scene, GameState *state)
{
	vector<DrawData> renderData = vector<DrawData>();
	DataArray<StandardGameObject> *objects = &scene->gameObjects;

	StandardGameObject *object = objects->TryToGetFirst();
	if(object != nullptr)
	{
		state->renderer.AddToPipeline(*scene->gameMeshes->TryToGet(object->meshId), *scene->gameTextures->TryToGet(object->textureId), object->position, object->rotation);

		while(objects->IsNext())
		{
			object = objects->Next();
			if (object != nullptr)
			{
				state->renderer.AddToPipeline(*scene->gameMeshes->TryToGet(object->meshId), *scene->gameTextures->TryToGet(object->textureId), object->position, object->rotation);
			}
		}
	}

	state->renderer.RenderScene();

}

void Draw::UpdateCamera(GameState *state, Vector3 playerCharPosition)
{
	float bottomY = playerCharPosition.y - 5;
	float topY = bottomY + 20;

	if(bottomY <= 0)
	{
		state->renderer.SetProjectionMatrix(Matrix4::Orthographic(-2, 100, 32, 0, 20, 0));
		state->cameraYValue = 0;
	}
	else
	{
		state->renderer.SetProjectionMatrix(Matrix4::Orthographic(-2, 100, 32, 0, topY, bottomY));
		state->cameraYValue = bottomY;
	}
}
