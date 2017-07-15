#pragma once
class CObserver
{
public:
	explicit CObserver();
	virtual ~CObserver();
	virtual void Update()=0;
};

