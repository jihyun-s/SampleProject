#pragma once
#include "../Observer.h"

class CSnakeGameComponent
{
protected:
	CObserver* m_observer;
public:
	explicit CSnakeGameComponent();
	virtual ~CSnakeGameComponent();

	void NotifyObserver();
	virtual void SetObserver(CObserver* a_observer) = 0;
};

