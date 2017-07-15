#include "SnakeGameComponent.h"

CSnakeGameComponent::CSnakeGameComponent()
{
	m_observer = nullptr;
}
CSnakeGameComponent::~CSnakeGameComponent()
{
}

void CSnakeGameComponent::notifyObserver()
{
	if (!m_observer)
		m_observer->Update();
}
