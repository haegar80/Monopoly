#ifndef MonopolyManagedWrapper_H
#define MonopolyManagedWrapper_H

#include "../MonopolyUI/MonopolyUI.h"

using namespace System;

public delegate void EventDelegate();

[event_receiver(managed)]
public ref class MonopolyManagedWrapper
{
public:
	MonopolyManagedWrapper();
	virtual ~MonopolyManagedWrapper();
	void DoSomething();
protected:
	// finalizer
	!MonopolyManagedWrapper();
private:
	Monopoly* m_monopolyUI;

	void registerEvent();
	void unregisterEvent();
	void handleEvent();
};

#endif // MonopolyManagedWrapper_H
