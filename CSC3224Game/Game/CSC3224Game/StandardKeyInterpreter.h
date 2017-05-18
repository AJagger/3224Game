/* CSC3224 Code
* Author: Aidan Jagger | 130281034
* Class Description:
* This class is a modification of the DemoKeyInterpreter provided in the original engine demo and deals with collecting and processing all input data. It has been expanded to include mouse data collection.
*/

#pragma once
#include "../../Frameworks/KeyInterpreter.h"
#include "../../Frameworks/DataArray.h"
#include "../../Core/GameScene.h"
#include "../../Core/GameState.h"
#include "StandardGameObject.h"

class StandardKeyInterpreter : public KeyInterpreter
{
public:
	StandardKeyInterpreter();
	~StandardKeyInterpreter();

	void ProcessKeyPresses(std::vector<int> keys, GameState &gameState, GameScene &gameScene) override;
	void ProcessMouse(GameState &gameState, GameScene &gameScene);
	void ProcessLimitedKeys(std::vector<int> keys, GameState &gameState) override;
	
private:
	enum KeyConfiguration
	{
		CONFIG_TOGGLE_PAUSE = KEYBOARD_ESCAPE,
		CONFIG_PLAYER_FORWARD = KEYBOARD_W,
		CONFIG_PLAYER_BACKWARD = KEYBOARD_S,
		CONFIG_PLAYER_LEFT = KEYBOARD_D,
		CONFIG_PLAYER_RIGHT = KEYBOARD_A,
		CONFIG_FORCE_END = KEYBOARD_C,
		CONFIG_DEBUG_TOGGLE = KEYBOARD_L,
		CONFIG_WEAPON_SWITCH_1 = KEYBOARD_1
	};

	void Force_End(GameState &gamestate);
	void Toggle_Pause(GameState &gamestate);
	void Player_Forward(GameScene &gamescene);
	void Player_Backward(GameScene &gamescene);
	void Player_Left(GameScene &gamescene);
	void Player_Right(GameScene &gamescene);
	void Debug_Toggle(GameState &gamestate);
	void Switch_Weapon(int weapon);
	int DetermineOrientation(std::vector<int> keys);

	vector<StandardGameObject*> controlledEntities;
};