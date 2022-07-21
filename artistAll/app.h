#pragma once
#include "mainWrapper.h"


class cApp : public wxApp
{
public:
	cApp();
	~cApp();

public:
	std::unique_ptr<mainWrapper>mainController;

public:
	virtual bool OnInit();
	int OnExit();
};
