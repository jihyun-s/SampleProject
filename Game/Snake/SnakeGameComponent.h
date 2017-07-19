#pragma once
#include "../Observer.h"

class CSnakeGameComponent
{
protected:
	CObserver* m_observer;
public:
	explicit CSnakeGameComponent();
	virtual ~CSnakeGameComponent();

	void NotifyObserver(bool bDraw=true, int a_nScore=-1);
	virtual void SetObserver(CObserver* a_observer) = 0;
};

