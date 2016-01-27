#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

#define START			0;
#define USERINTERFACE	1;
#define HIGHSCORE		2;
#define OPTION			3;
#define PAUSE			4;
#define ENDSCREEN		5;


//Includes
//1.Diff Screens
//2.input
//3.modelhandler

class ScreenManager
{
//----------------------------Functions----------------------------------------
private:
	//Destructor and Constructor
	ScreenManager();
	~ScreenManager();
	//Uppdate screens
	void Uppdate(int CurrentScreen);
	//Initializing the screen manager
	void InitializeScreen();
	//Rendercall
	void Render();

//----------------------------Attributes----------------------------------------
private:
	//Current status.
	int mCurrent;
	//Different screens


	//input


	//Modelhandler


};

#endif
