#pragma once 
#include "Display.h"


class UIelement
{
    //master object for User Interface objects to be drawn through 
public:
virtual void AddToLayer() = 0;
virtual void Update() = 0;

int M_ScreenPriority;
bool M_HasBackGround;
Display * M_graphics;

};



class Textbox : public UIelement{

};