// GameEngineClient.cpp : Defines the exported functions for the DLL application.
//

#include "stdafx.h"
#include "GameEngineClient.h"

GameEngineClient::GameEngineClient()
{
}

GameEngineClient::~GameEngineClient()
{
}

void GameEngineClient::DoSomething()
{
	__raise MyEvent();
}