// Monopoly.cpp : Defines the entry point for the application.
//

#include "stdafx.h"
#include "MonopolyUI.h"
#include "UI/MainWindow.h"
#include "UI/GLWidget.h"
#include "UI/PlaceDetails.h"
#include "GameMap/GameMap.h"
#include "Rendering/MapRenderer.h"
#include "ObjectLoader/ObjLoader.h"

BOOL APIENTRY MonopolyUIEntry(HMODULE hModule,
                              DWORD  ul_reason_for_call,
                              LPVOID lpReserved)
{
	switch (ul_reason_for_call)
	{
	case DLL_PROCESS_ATTACH:
	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}

	return TRUE;
}

void Monopoly::DoSomething()
{
	char* argv[4096] ;
    int argc = 0 ;
	QApplication app(argc, argv);

	const int cSize = 1000;
	const int cNumberOfPlaces = 36;
	GameMap map(cSize, cNumberOfPlaces);

	ObjLoader objLoader;
	std::string fileNameTest = "Wavefront/building/building.obj";
	objLoader.LoadOBJ(fileNameTest);

	MapRenderer mapRenderer(map, objLoader);
	
	PlaceDetails placeDetailsWidget(map);
	placeDetailsWidget.setupUi();

	MainWindow mainWindow;
	mainWindow.setupUi();
	GLWidget mapWidget(mapRenderer, placeDetailsWidget, mainWindow.getMapWidget());
	mapWidget.setFixedWidth(cSize);
	mapWidget.setFixedHeight(cSize);

	mainWindow.show();

	app.exec();
}

void Monopoly::FireEvent()
{
	CallbackType callbackFunc = (CallbackType)(m_eventListener);
    callbackFunc();    
}

void Monopoly::RegisterListener(void* p_listener)
{
	m_eventListener = p_listener;
}

void Monopoly::UnregisterListener(void* p_listener)
{
	delete p_listener;
}