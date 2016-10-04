========================================================================
    CONSOLE APPLICATION : assign2 Project Overview
========================================================================

AppWizard has created this assign2 application for you.

This file contains a summary of what you will find in each of the files that
make up your assign2 application.


assign2.vcxproj
    This is the main project file for VC++ projects generated using an Application Wizard.
    It contains information about the version of Visual C++ that generated the file, and
    information about the platforms, configurations, and project features selected with the
    Application Wizard.

assign2.vcxproj.filters
    This is the filters file for VC++ projects generated using an Application Wizard. 
    It contains information about the association between the files in your project 
    and the filters. This association is used in the IDE to show grouping of files with
    similar extensions under a specific node (for e.g. ".cpp" files are associated with the
    "Source Files" filter).

assign2.cpp
    This is the main application source file.

/////////////////////////////////////////////////////////////////////////////
Other standard files:

StdAfx.h, StdAfx.cpp
    These files are used to build a precompiled header (PCH) file
    named assign2.pch and a precompiled types file named StdAfx.obj.

/////////////////////////////////////////////////////////////////////////////
Other notes:

AppWizard uses "TODO:" comments to indicate parts of the source code you
should add to or customize.

/////////////////////////////////////////////////////////////////////////////




Tips for dear grader:

I have moved almost all variable and functions' definition to headers'h.

Some of the functions are come form assign1 such as mouse event functions, 
	but the mouse function is only for testing, I have disable the those fuctions in display fuction.

I also modified some fucntions from previous assignment to fit this assignment:

/*
	user interactions
*/
	I have Change the modechose function, 
	press key '1' means go forward for one step for Rolar Coaster, 
	press key '2' means go backward for one step, 
	press key '3' means go forward for three step, which means speed up:)
/*
	end
*/

	I have Change the setCamera function to get a better view of first sight look

I have create some fucntions
 
	some of them are for drawing objects in  window, and there are some sub fuctions to do the set point job for drawing.
		like drawQuads, drawSpline, drawTextureBox, drawtrack3d, drawCrosssection,
		set points functions like setCurrentPoint, set DrawCRPoint, setControlPoint etc.
		some of it are for testing, others are for final animation.

	getMyPointList is the function for me to store all the point in the spline. 
		I have create my own struct to store the point in spline, and it also stores the normal, tangent and binormal of that point too.
		And there is a list to store all myPoint data due to the index of that point.

see more description, I have write it in the headers.h file

Thanks~

Jialin Yang