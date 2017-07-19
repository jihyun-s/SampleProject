#pragma once
class CObserver
{
public:
	explicit CObserver();
	virtual ~CObserver();
	virtual void UpdateUI()=0;
	virtual void UpdateScore(int a_nScore)=0;
};

