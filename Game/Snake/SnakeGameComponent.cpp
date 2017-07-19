#include "SnakeGameComponent.h"
#include "assert.h"

CSnakeGameComponent::CSnakeGameComponent()
{
	m_observer = nullptr;
}
CSnakeGameComponent::~CSnakeGameComponent()
{
}

void CSnakeGameComponent::NotifyObserver(bool bDraw, int a_nScore)
{
	assert(m_observer);
	
	if (m_observer)
	{
		if (bDraw)
			m_observer->UpdateUI();
		if (a_nScore >= 0)
			m_observer->UpdateScore(a_nScore);
	}
}
