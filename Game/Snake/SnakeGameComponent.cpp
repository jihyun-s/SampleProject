#include "SnakeGameComponent.h"

CSnakeGameComponent::CSnakeGameComponent()
{
	m_observer = nullptr;
}
CSnakeGameComponent::~CSnakeGameComponent()
{
}

void CSnakeGameComponent::NotifyObserver()
{
	if (m_observer)
		m_observer->Update();
}
