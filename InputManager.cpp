#include "InputManager.h"

InputManager* InputManager::GetInstance()
{
	static InputManager instance;
	return &instance;
}

void InputManager::Update()
{
	GetInstance()->_Update();
}



void InputManager::_Update()
{
	memcpy(preKeys,keys,256);
	Novice::GetHitKeyStateAll(keys);
	Novice::GetAnalogInputLeft(0, &inputStick.x, &inputStick.y);



}

bool InputManager::IsPressKey(int DIK)
{	
	return keys[DIK];
}

bool InputManager::IsReleaseKey(int DIK)
{
	return preKeys[DIK]&&!keys[DIK];
}

void InputManager::Init()
{
	for (int i = 0; i < 256; i++)
	{
		keys[i] = 0;
		preKeys[i] = 0;
	}
}


bool InputManager::IsTriggerKey(int DIK)
{
	return keys[DIK]&&!preKeys[DIK];
}
