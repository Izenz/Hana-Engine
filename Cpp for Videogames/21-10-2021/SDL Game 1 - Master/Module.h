#pragma once

class Application;

class Module
{
public:

	Module()
	{
	}

	virtual bool Init() 
	{
		return true; 
	}

	// TODO 3: Create a new method "Start()" that should be called for all modules just before the first frame

	virtual update_status Update()
	{
		return UPDATE_CONTINUE;
	}

	virtual bool CleanUp() 
	{ 
		return true; 
	}
};