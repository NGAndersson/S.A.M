#ifndef SCREENMANAGER_H
#define SCREENMANAGER_H

enum EnumScreens { START, USERINTERFACE, HIGHSCORE, OPTION, PAUSE, ENDSCREEN };

//Includes
//1.Diff Screens
//2.input
//3.modelhandler

class ScreenManager
{
//----------------------------Functions----------------------------------------
public:
	//Destructor and Constructor
	ScreenManager();
	~ScreenManager();
	//Uppdate screens
	void Update(double time);
	//Initializing the screen manager
	void InitializeScreen();
	//Rendercall
	void Render();
	
	int GetCurrentScreen() { return m_Current; }

//----------------------------Attributes----------------------------------------
private:
	//Current status.
	EnumScreens m_Current;
	//Different screens


	//input


	//Modelhandler


};

#endif
