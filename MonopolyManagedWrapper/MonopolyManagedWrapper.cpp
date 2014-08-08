#include "stdafx.h"
#include "MonopolyManagedWrapper.h"

using namespace System::Runtime::InteropServices;

MonopolyManagedWrapper::MonopolyManagedWrapper()
{
	m_monopolyUI = new Monopoly;
}
MonopolyManagedWrapper::~MonopolyManagedWrapper()
{
	unregisterEvent();
	delete m_monopolyUI;
}

MonopolyManagedWrapper::!MonopolyManagedWrapper()
{
	delete m_monopolyUI;
}

void MonopolyManagedWrapper::DoSomething()
{
	registerEvent();
	// m_monopolyUI->FireEvent();
	m_monopolyUI->DoSomething();

}

void MonopolyManagedWrapper::registerEvent()
{
	EventDelegate^ eventDelegate = gcnew EventDelegate(this, &MonopolyManagedWrapper::handleEvent);
	void* functionPointer = Marshal::GetFunctionPointerForDelegate(eventDelegate).ToPointer();
	m_monopolyUI->RegisterListener(functionPointer);
}

void MonopolyManagedWrapper::unregisterEvent()
{
	EventDelegate^ eventDelegate = gcnew EventDelegate(this, &MonopolyManagedWrapper::handleEvent);
	void* functionPointer = Marshal::GetFunctionPointerForDelegate(eventDelegate).ToPointer();
	m_monopolyUI->UnregisterListener(functionPointer);
}

void MonopolyManagedWrapper::handleEvent()
{
	
}