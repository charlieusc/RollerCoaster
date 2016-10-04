// assign2.cpp : Defines the entry point for the console application.
//

/*
	CSCI 480 Computer Graphics
	Assignment 2: Simulating a Roller Coaster
	C++ starter code
*/
#include "stdafx.h"
#include <pic.h>
#include <windows.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <GL/glu.h>
#include <GL/glut.h>
#include "headers.h"



int _tmain(int argc, _TCHAR* argv[])
{
	if (argc<2)
	{  
		printf ("usage: %s <trackfile>\n", argv[0]);
		exit(0);
	}
	//load Splines to struct g_Splines
	loadSplines(argv[1]);

	//allocate memory for saving myPoint list
	pointNuminList = 10000;
	pointsList = (struct myPoint *)malloc(pointNuminList * sizeof(struct myPoint));
	getMyPointList();

	// glut initiation
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_DEPTH | GLUT_RGB);
	glutInitWindowSize(winW, winH);
	glutCreateWindow("Roller Coaster in Space!");

	/* do initialization */
	myinit();
	textureInitiation();
	
	/* tells glut to use a particular display function to redraw */
	glutDisplayFunc(display);
	//glutReshapeFunc(reshape);
	glutKeyboardFunc(modechose);
	//glutReshapeFunc(resizeview);


	/* replace with any animate code */
	glutIdleFunc(doIdle);

	/* callback for mouse drags */
	glutMotionFunc(mousedrag);

	/* callback for idle mouse movement */
	glutPassiveMotionFunc(mouseidle);

	/* callback for mouse button changes */
	glutMouseFunc(mousebutton);
	//saveScreenshot("./savedScreen/000.jpg");
	glutMainLoop();

	return 0;
}
/*
	animation create from here
*/
void doIdle()
{
	/* do some stuff... */
	/*
		char str[200];
	if (counter < 20){
		CpLIndex += 1;
	}else if (counter >= 20 && counter <=920){
			CpLIndex += 2;
			sprintf(str, "./savedScreen/%03d.jpg", counter-20);
			saveScreenshot(str);
	}
	
	counter +=1 ;
	*/
	/* make the screen update */
	glutPostRedisplay();
}
/*
	load texture image to memory and do glTex initiation
*/
void textureInitiation() {
	groundTexture = jpeg_read("Images/Earth_Stars_1024.jpg", NULL); 
	skyTexture = jpeg_read("Images/Stars_1024.jpg", NULL);
	groundIndex = 0;
	glGenTextures(1, &groundIndex);
	glBindTexture(GL_TEXTURE_2D, groundIndex);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT); 
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
}
/*
	draw XYZ axis, for test only
*/
void drawTextureBox(float groundSize, float belowGround) {
	// Enable OpenGL texturing
	glTexEnvf(GL_TEXTURE_ENV, GL_TEXTURE_ENV_MODE, GL_REPLACE); 
	// Turn on the texturing
	glEnable(GL_TEXTURE_2D);
	// Load  ground texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, groundTexture->nx, groundTexture->ny, 0, GL_RGB, GL_UNSIGNED_BYTE, groundTexture->pix);
	// Draw ground plane
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5 * groundSize, -0.5 * groundSize, -belowGround);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.5 * groundSize, -0.5 * groundSize, -belowGround);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5 * groundSize, 0.5 * groundSize, -belowGround);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.5 * groundSize, 0.5 * groundSize, -belowGround);
	
	glEnd();
	// Load  skys texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, skyTexture->nx, skyTexture->ny, 0, GL_RGB, GL_UNSIGNED_BYTE, skyTexture->pix);
	// Draw the top sky plane
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5 * groundSize, -0.5 * groundSize, groundSize - belowGround);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.5 * groundSize, -0.5 * groundSize, groundSize - belowGround);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5 * groundSize, 0.5 * groundSize, groundSize - belowGround);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.5 * groundSize, 0.5 * groundSize, groundSize - belowGround);

	glEnd();

	// Draw the left sky plane
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5 * groundSize, -0.5 * groundSize, - belowGround);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5 * groundSize, -0.5 * groundSize, groundSize - belowGround);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5 * groundSize, -0.5 * groundSize, groundSize - belowGround);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5 * groundSize, -0.5 * groundSize, -belowGround);

	glEnd();

	// Draw the right sky plane
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5 * groundSize, 0.5 * groundSize, -belowGround);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5 * groundSize, 0.5 * groundSize, groundSize - belowGround);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5 * groundSize, 0.5 * groundSize, groundSize - belowGround);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5 * groundSize, 0.5 * groundSize, -belowGround);

	glEnd();

	// Draw the front sky plane
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(-0.5 * groundSize, -0.5 * groundSize, -belowGround);
	glTexCoord2f(1.0, 0.0); glVertex3f(-0.5 * groundSize, -0.5 * groundSize, groundSize - belowGround);
	glTexCoord2f(1.0, 1.0); glVertex3f(-0.5 * groundSize, 0.5 * groundSize, groundSize - belowGround);
	glTexCoord2f(0.0, 1.0); glVertex3f(-0.5 * groundSize, 0.5 * groundSize, -belowGround);

	glEnd();

	// Draw the back sky plane
	glBegin(GL_QUADS);

	glTexCoord2f(0.0, 0.0); glVertex3f(0.5 * groundSize, -0.5 * groundSize, -belowGround);
	glTexCoord2f(1.0, 0.0); glVertex3f(0.5 * groundSize, -0.5 * groundSize, groundSize - belowGround);
	glTexCoord2f(1.0, 1.0); glVertex3f(0.5 * groundSize, 0.5 * groundSize, groundSize - belowGround);
	glTexCoord2f(0.0, 1.0); glVertex3f(0.5 * groundSize, 0.5 * groundSize, -belowGround);

	glEnd();

	// Disable the texturing
	glDisable(GL_TEXTURE_2D);
}

/*
	draw XYZ axis, for test only
*/
void drawXYZ(point p0, point p1, point p2, point p3)
{
	glPushMatrix();
	glBegin(GL_LINES);
	//X is red
	glTranslatef(-1.0, -1.0, -1.0);
	glColor3f(1.0, 0.0, 0.0);
	glVertex3f(p0.x, p0.y, p0.z);
	glVertex3f(p1.x, p1.y, p1.z);
	//Y is green
	glColor3f(0.0, 1.0, 0.0);
	glVertex3f(p0.x, p0.y, p0.z);
	glVertex3f(p2.x, p2.y, p2.z);
	//Z is blue
	glColor3f(0.0, 0.0, 1.0);
	glVertex3f(p0.x, p0.y, p0.z);
	glVertex3f(p3.x, p3.y, p3.z);
	// glTranslatef(1.0,1.0,1.0);
	glEnd();
	glPopMatrix();
}

/*
	draw control points in spline, for test only
*/
void drawPoints(){
	
	glPointSize(5);
	glBegin(GL_POINTS);
	for (int i = 0; i < g_iNumOfSplines; i++)
	{
		for (int j = 0; j < g_Splines[i].numControlPoints; j++){
			glColor3f(1, 0, 0);
			glVertex3f(g_Splines[i].points[j].x, g_Splines[i].points[j].y, g_Splines[i].points[j].z);
		}
	}
	glEnd();
}
/*
	draw Points' Normal of some points in spline, for test only
*/
void drawPointsNormal(){
	glBegin(GL_LINES);
	for (int i = 0; i < pLIndex; i+=10)
	{
		glColor3f(1, 0, 0);
		glVertex3f(pointsList[i].curpoint.x, pointsList[i].curpoint.y, pointsList[i].curpoint.z);
		glColor3f(1, 0, 0);
		glVertex3f(pointsList[i].curpoint.x + pointsList[i].normal.x, pointsList[i].curpoint.y + pointsList[i].normal.y, pointsList[i].curpoint.z + pointsList[i].normal.z);
	}
	glEnd();
}
/*
draw Points' Tandent of some points in spline, for test only
*/
void drawPointsTandent(){
	glBegin(GL_LINES);
	for (int i = 0; i < pLIndex; i += 10)
	{
		glColor3f(1, 0, 1);
		glVertex3f(pointsList[i].curpoint.x, pointsList[i].curpoint.y, pointsList[i].curpoint.z);
		glColor3f(1, 0, 1);
		glVertex3f(pointsList[i].curpoint.x + pointsList[i].lookAt.x, pointsList[i].curpoint.y + pointsList[i].lookAt.y, pointsList[i].curpoint.z + pointsList[i].lookAt.z);
	}
	glEnd();
}
/*
	draw binormal for some points, but it also represents the stick in 2D
*/
void drawPointsBinormal(){
	//draw stick
	glLineWidth(LW);
	glBegin(GL_LINES);
	for (int i = 0; i < pLIndex; i += 10)
	{
		trackhW.x = TWS * pointsList[i].biNormal.x;
		trackhW.y = TWS * pointsList[i].biNormal.y;
		trackhW.z = TWS * pointsList[i].biNormal.z;
		glColor3f(0, 1, 1);
		glVertex3f(pointsList[i].curpoint.x - trackhW.x, pointsList[i].curpoint.y - trackhW.y, pointsList[i].curpoint.z - trackhW.z);
		glColor3f(0, 1, 1);
		glVertex3f(pointsList[i].curpoint.x + trackhW.x, pointsList[i].curpoint.y + trackhW.y, pointsList[i].curpoint.z + trackhW.z);
	}
}

/*
	this function set Track points for drawing track in 3D
	i represents current Track center point Index, LorR represents left or right Track center
*/
void setTrack(int i, int LorR){
	trackhW.x = TWS * pointsList[i].biNormal.x;
	trackhW.y = TWS * pointsList[i].biNormal.y;
	trackhW.z = TWS * pointsList[i].biNormal.z;
	if (LorR == 0){
		TrackP.x = pointsList[i].curpoint.x - trackhW.x - belowScale * pointsList[i].normal.x;
		TrackP.y = pointsList[i].curpoint.y - trackhW.y - belowScale * pointsList[i].normal.y;
		TrackP.z = pointsList[i].curpoint.z - trackhW.z - belowScale * pointsList[i].normal.z;
	}
	else if (LorR == 1){
		TrackP.x = pointsList[i].curpoint.x + trackhW.x - belowScale * pointsList[i].normal.x;
		TrackP.y = pointsList[i].curpoint.y + trackhW.y - belowScale * pointsList[i].normal.y;
		TrackP.z = pointsList[i].curpoint.z + trackhW.z - belowScale * pointsList[i].normal.z;
	}

	//get front 4 point
	V00.x = TrackP.x + alpha * (pointsList[i].normal.x - pointsList[i].biNormal.x);
	V00.y = TrackP.y + alpha * (pointsList[i].normal.y - pointsList[i].biNormal.y);
	V00.z = TrackP.z + alpha * (pointsList[i].normal.z - pointsList[i].biNormal.z);

	V01.x = TrackP.x + alpha * (pointsList[i].normal.x + pointsList[i].biNormal.x);
	V01.y = TrackP.y + alpha * (pointsList[i].normal.y + pointsList[i].biNormal.y);
	V01.z = TrackP.z + alpha * (pointsList[i].normal.z + pointsList[i].biNormal.z);

	V02.x = TrackP.x + alpha * (-pointsList[i].normal.x + pointsList[i].biNormal.x);
	V02.y = TrackP.y + alpha * (-pointsList[i].normal.y + pointsList[i].biNormal.y);
	V02.z = TrackP.z + alpha * (-pointsList[i].normal.z + pointsList[i].biNormal.z);

	V03.x = TrackP.x + alpha * (-pointsList[i].normal.x - pointsList[i].biNormal.x);
	V03.y = TrackP.y + alpha * (-pointsList[i].normal.y - pointsList[i].biNormal.y);
	V03.z = TrackP.z + alpha * (-pointsList[i].normal.z - pointsList[i].biNormal.z);

	//get back 4 point

	trackhW.x = TWS * pointsList[i + 1].biNormal.x;
	trackhW.y = TWS * pointsList[i + 1].biNormal.y;
	trackhW.z = TWS * pointsList[i + 1].biNormal.z;
	if (LorR == 0){
		TrackP.x = pointsList[i + 1].curpoint.x - trackhW.x - belowScale * pointsList[i + 1].normal.x;
		TrackP.y = pointsList[i + 1].curpoint.y - trackhW.y - belowScale * pointsList[i + 1].normal.y;
		TrackP.z = pointsList[i + 1].curpoint.z - trackhW.z - belowScale * pointsList[i + 1].normal.z;
	}
	else if (LorR == 1){
		TrackP.x = pointsList[i + 1].curpoint.x + trackhW.x - belowScale * pointsList[i + 1].normal.x;
		TrackP.y = pointsList[i + 1].curpoint.y + trackhW.y - belowScale * pointsList[i + 1].normal.y;
		TrackP.z = pointsList[i + 1].curpoint.z + trackhW.z - belowScale * pointsList[i + 1].normal.z;
	}

	V10.x = TrackP.x + alpha * (pointsList[i + 1].normal.x - pointsList[i + 1].biNormal.x);
	V10.y = TrackP.y + alpha * (pointsList[i + 1].normal.y - pointsList[i + 1].biNormal.y);
	V10.z = TrackP.z + alpha * (pointsList[i + 1].normal.z - pointsList[i + 1].biNormal.z);

	V11.x = TrackP.x + alpha * (pointsList[i + 1].normal.x + pointsList[i + 1].biNormal.x);
	V11.y = TrackP.y + alpha * (pointsList[i + 1].normal.y + pointsList[i + 1].biNormal.y);
	V11.z = TrackP.z + alpha * (pointsList[i + 1].normal.z + pointsList[i + 1].biNormal.z);

	V12.x = TrackP.x + alpha * (-pointsList[i + 1].normal.x + pointsList[i + 1].biNormal.x);
	V12.y = TrackP.y + alpha * (-pointsList[i + 1].normal.y + pointsList[i + 1].biNormal.y);
	V12.z = TrackP.z + alpha * (-pointsList[i + 1].normal.z + pointsList[i + 1].biNormal.z);

	V13.x = TrackP.x + alpha * (-pointsList[i + 1].normal.x - pointsList[i + 1].biNormal.x);
	V13.y = TrackP.y + alpha * (-pointsList[i + 1].normal.y - pointsList[i + 1].biNormal.y);
	V13.z = TrackP.z + alpha * (-pointsList[i + 1].normal.z - pointsList[i + 1].biNormal.z);
}

/*
	draw bcube uing 8 point
*/
void drawQuads(point V00, point V01, point V02, point V03, point V10, point V11, point V12, point V13){
	//draw up
	glBegin(GL_QUADS);

	glColor3f(1, 1, 1);
	glVertex3f(V01.x, V01.y, V01.z);

	glColor3f(1, 1, 1);
	glVertex3f(V02.x, V02.y, V02.z);

	glColor3f(1, 1, 1);
	glVertex3f(V12.x, V12.y, V12.z);
	
	glColor3f(1, 1, 1);	
	glVertex3f(V11.x, V11.y, V11.z);

	glEnd();

	//draw bottom

	glBegin(GL_QUADS);

	glColor3f(1, 1, 1);
	glVertex3f(V00.x, V00.y, V00.z);

	glColor3f(1, 1, 1);
	glVertex3f(V10.x, V10.y, V10.z);

	glColor3f(1, 1, 1);
	glVertex3f(V13.x, V13.y, V13.z);

	glColor3f(1, 1, 1);
	glVertex3f(V03.x, V03.y, V03.z);

	glEnd();

	//draw right
	glBegin(GL_QUADS);

	glColor3f(1, 0, 0);
	glVertex3f(V01.x, V01.y, V01.z);

	glColor3f(1, 0, 0);
	glVertex3f(V11.x, V11.y, V11.z);

	glColor3f(1, 0, 0);
	glVertex3f(V10.x, V10.y, V10.z);

	glColor3f(1, 0, 0);
	glVertex3f(V00.x, V00.y, V00.z);

	glEnd();

	//draw left

	glBegin(GL_QUADS);

	glColor3f(1, 0, 0);
	glVertex3f(V03.x, V03.y, V03.z);

	glColor3f(1, 0, 0);
	glVertex3f(V02.x, V02.y, V02.z);

	glColor3f(1, 0, 0);
	glVertex3f(V12.x, V12.y, V12.z);

	glColor3f(1, 0, 0);
	glVertex3f(V13.x, V13.y, V13.z);

	glEnd();

	//draw front

	glBegin(GL_QUADS);

	glColor3f(1, 0, 1);
	glVertex3f(V03.x, V03.y, V03.z);

	glColor3f(1, 0, 1);
	glVertex3f(V02.x, V02.y, V02.z);

	glColor3f(1, 0, 1);
	glVertex3f(V01.x, V01.y, V01.z);

	glColor3f(1, 0, 1);
	glVertex3f(V00.x, V00.y, V00.z);

	glEnd();

	//	//draw left

	glBegin(GL_QUADS);

	glColor3f(1, 0, 1);
	glVertex3f(V13.x, V13.y, V13.z);

	glColor3f(1, 0, 1);
	glVertex3f(V12.x, V12.y, V12.z);

	glColor3f(1, 0, 1);
	glVertex3f(V11.x, V11.y, V11.z);

	glColor3f(1, 0, 1);
	glVertex3f(V10.x, V10.y, V10.z);

	glEnd();


}
/*
	draw tracks in 3D
*/
void drawtracks3d(){

	//draw track
	for (int i = 0; i < pLIndex; i++)
	{
		//set lefttrack
		setTrack(i, 0);
		drawQuads(V00, V01, V02, V03, V10, V11, V12, V13);
		//set righttrack
		setTrack(i, 1);
		drawQuads(V00, V01, V02, V03, V10, V11, V12, V13);

	}
	//glEnd();
}
/*
	this function set Crosssection points for drawing Crosssection in 3D
	i represents current Crosssection center point Index
*/
void setCrosssection(int i){
	crossSectionhW.x = CTS * pointsList[i].biNormal.x;
	crossSectionhW.y = CTS * pointsList[i].biNormal.y;
	crossSectionhW.z = CTS * pointsList[i].biNormal.z;
	lP.x = pointsList[i].curpoint.x - crossSectionhW.x - bSforCS * pointsList[i].normal.x;
	lP.y = pointsList[i].curpoint.y - crossSectionhW.y - bSforCS * pointsList[i].normal.y;
	lP.z = pointsList[i].curpoint.z - crossSectionhW.z - bSforCS * pointsList[i].normal.z;

	rP.x = pointsList[i].curpoint.x + crossSectionhW.x - bSforCS * pointsList[i].normal.x;
	rP.y = pointsList[i].curpoint.y + crossSectionhW.y - bSforCS * pointsList[i].normal.y;
	rP.z = pointsList[i].curpoint.z + crossSectionhW.z - bSforCS * pointsList[i].normal.z;

	//get right 4 point

	V00.x = rP.x + alpha * (- pointsList[i].normal.x - pointsList[i].lookAt.x);
	V00.y = rP.y + alpha * (- pointsList[i].normal.y - pointsList[i].lookAt.y);
	V00.z = rP.z + alpha * (- pointsList[i].normal.z - pointsList[i].lookAt.z);

	V01.x = rP.x + alpha * (pointsList[i].normal.x - pointsList[i].lookAt.x);
	V01.y = rP.y + alpha * (pointsList[i].normal.y - pointsList[i].lookAt.y);
	V01.z = rP.z + alpha * (pointsList[i].normal.z - pointsList[i].lookAt.z);

	V11.x = rP.x + alpha * (pointsList[i].normal.x + pointsList[i].lookAt.x);
	V11.y = rP.y + alpha * (pointsList[i].normal.y + pointsList[i].lookAt.y);
	V11.z = rP.z + alpha * (pointsList[i].normal.z + pointsList[i].lookAt.z);

	V10.x = rP.x + alpha * (- pointsList[i].normal.x + pointsList[i].lookAt.x);
	V10.y = rP.y + alpha * (- pointsList[i].normal.y + pointsList[i].lookAt.y);
	V10.z = rP.z + alpha * (- pointsList[i].normal.z + pointsList[i].lookAt.z);

	//get left 4 point

	V03.x = lP.x + alpha * (-pointsList[i].normal.x - pointsList[i].lookAt.x);
	V03.y = lP.y + alpha * (-pointsList[i].normal.y - pointsList[i].lookAt.y);
	V03.z = lP.z + alpha * (-pointsList[i].normal.z - pointsList[i].lookAt.z);

	V02.x = lP.x + alpha * (pointsList[i].normal.x - pointsList[i].lookAt.x);
	V02.y = lP.y + alpha * (pointsList[i].normal.y - pointsList[i].lookAt.y);
	V02.z = lP.z + alpha * (pointsList[i].normal.z - pointsList[i].lookAt.z);

	V12.x = lP.x + alpha * (pointsList[i].normal.x + pointsList[i].lookAt.x);
	V12.y = lP.y + alpha * (pointsList[i].normal.y + pointsList[i].lookAt.y);
	V12.z = lP.z + alpha * (pointsList[i].normal.z + pointsList[i].lookAt.z);

	V13.x = lP.x + alpha * (-pointsList[i].normal.x + pointsList[i].lookAt.x);
	V13.y = lP.y + alpha * (-pointsList[i].normal.y + pointsList[i].lookAt.y);
	V13.z = lP.z + alpha * (-pointsList[i].normal.z + pointsList[i].lookAt.z);
}
/*
	draw Crosssections in 3D
*/
void drawCrosssection(){
	//draw track
	for (int i = 0; i < pLIndex; i += 12)
	{
		//set each crosssection
		setCrosssection(i);
		drawQuads(V00, V01, V02, V03, V10, V11, V12, V13);
	}
}
/*
	draw spline, for test only
*/
void drawSpline(){

	glLineWidth(LW);
	
	glBegin(GL_LINES);
	for (int i = 0; i < pLIndex ; i++)
	{
				glColor3f(0, 0, 0);
				glVertex3f(pointsList[i].curpoint.x, pointsList[i].curpoint.y, pointsList[i].curpoint.z);
				glColor3f(1, 1, 1);
				glVertex3f(pointsList[i+1].curpoint.x, pointsList[i+1].curpoint.y, pointsList[i+1].curpoint.z);
	}
	glEnd();
	
	

	//draw track in line
	
	
	glBegin(GL_LINES);
	for (int i = 0; i < pLIndex; i++)
	{
		trackhW.x = TWS * pointsList[i].biNormal.x;
		trackhW.y = TWS * pointsList[i].biNormal.y;
		trackhW.z = TWS * pointsList[i].biNormal.z;
		glColor3f(0.5, 1, 0.5);
		glVertex3f(pointsList[i].curpoint.x + trackhW.x, pointsList[i].curpoint.y + trackhW.y, pointsList[i].curpoint.z + trackhW.z);
		trackhW.x = TWS * pointsList[i + 1].biNormal.x;
		trackhW.y = TWS * pointsList[i + 1].biNormal.y;
		trackhW.z = TWS * pointsList[i + 1].biNormal.z;
		glColor3f(0.5, 1, 0.5);
		glVertex3f(pointsList[i + 1].curpoint.x + trackhW.x, pointsList[i + 1].curpoint.y + trackhW.y, pointsList[i + 1].curpoint.z + trackhW.z);
	}
	glEnd();

	glBegin(GL_LINES);
	for (int i = 0; i < pLIndex - 1; i++)
	{
		point trackhW;
		trackhW.x = TWS * pointsList[i].biNormal.x;
		trackhW.y = TWS * pointsList[i].biNormal.y;
		trackhW.z = TWS * pointsList[i].biNormal.z;
		glColor3f(0.5, 1, 0.5);
		glVertex3f(pointsList[i].curpoint.x - trackhW.x, pointsList[i].curpoint.y - trackhW.y, pointsList[i].curpoint.z - trackhW.z);
		trackhW.x = TWS * pointsList[i + 1].biNormal.x;
		trackhW.y = TWS * pointsList[i + 1].biNormal.y;
		trackhW.z = TWS * pointsList[i + 1].biNormal.z;
		glColor3f(0.5, 1, 0.5);
		glVertex3f(pointsList[i + 1].curpoint.x - trackhW.x, pointsList[i + 1].curpoint.y - trackhW.y, pointsList[i + 1].curpoint.z - trackhW.z);
	}
	glEnd();

	
	
}
/*
	setup gl view
*/
void myinit()
{
	glClearColor(0.5, 0.5, 0.5, 0.0);
	glEnable(GL_DEPTH_TEST);
	glShadeModel(GL_SMOOTH);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(60.0, (double)winW / winH, 0.01, 1000.0);

}
/*
	store all the point in the spline using my own struct 
	it also stores the normal, tangent and binormal of each point too.
*/
void getMyPointList(){

	for (int i = 0; i < g_iNumOfSplines; i++)
	{
		for (int j = 1; j < g_Splines[i].numControlPoints - 1; j++){

			setControlPoint(i, j);
			while (u >= 0 && u < 1){
				drawPoint = setDrawCRPoint(u);
				tangentPoint = setTangentPoint(u);
				setCurrentPoint(drawPoint, tangentPoint);
				u += uPlus;
				pLIndex++;
			}
			u = 0;


		}
	}
}
/*
	setup first sight look
*/
void setupCamera()
{
	//Initial Setup 
	
	/*
	set view for roller
	*/
	float k = 0.05;
	glOrtho(-k* winW, k* winW, -k* winH, k* winH, 0.1, 50.0);


	/*
	set view for birdView
	
	float k = 2;
	glOrtho(-k* winW, k* winW, -k* winH, k* winH, 0.1, 1000.0);
*/

	glTranslatef(0, 0, 0);
	glScalef(15.0, 15.0, 15.0);
	//glRotatef(-180.0f, 0.0f, 0.0f, 1.0f);
	//glRotatef(90.0f, 0.0f, 0.0f, 1.0f);
}

void reshape(int w, int h)
{
	glViewport(0, 0, (GLsizei)w, (GLsizei)h);
	glMatrixMode(GL_PROJECTION);

	glLoadIdentity();
	gluPerspective(60.0, (GLfloat)w / (GLfloat)h, 0.1, 400.0);

	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
}
/*
	setup the cameraposition, where to look at and where the upvector is.
*/
void setLookPosition(){

	/*
	cameraPosition[0] = pointsList[CpLIndex].curpoint.x + 1 * pointsList[CpLIndex].normal.x;
	cameraPosition[1] = pointsList[CpLIndex].curpoint.y + 1 * pointsList[CpLIndex].normal.y;
	cameraPosition[2] = pointsList[CpLIndex].curpoint.z + 1 * pointsList[CpLIndex].normal.z;
	*/
	cameraPosition[0] = pointsList[CpLIndex].curpoint.x;
	cameraPosition[1] = pointsList[CpLIndex].curpoint.y;
	cameraPosition[2] = pointsList[CpLIndex].curpoint.z;
	
	
	/*
	set view for roller
	
	cameraLookAt[0] = -500 * (pointsList[CpLIndex + 10].lookAt.x - 0.5 * pointsList[CpLIndex].normal.x);
	cameraLookAt[1] = -500 * (pointsList[CpLIndex + 10].lookAt.y - 0.5 * pointsList[CpLIndex].normal.y);
	cameraLookAt[2] = -500 * (pointsList[CpLIndex + 10].lookAt.z - 0.5 * pointsList[CpLIndex].normal.z);
	*/
	/*
	set view for birdView
	*/
	cameraLookAt[0] =  - 1000 * pointsList[CpLIndex].lookAt.x;
	cameraLookAt[1] =  - 1000 * pointsList[CpLIndex].lookAt.y;
	cameraLookAt[2] =  - 1000 * pointsList[CpLIndex].lookAt.z;


	/*
	cameraLookAt[0] = pointsList[CpLIndex + 1].curpoint.x + 0.5 * pointsList[CpLIndex + 1].normal.x;
	cameraLookAt[1] = pointsList[CpLIndex + 1].curpoint.y + 0.5 * pointsList[CpLIndex + 1].normal.y;
	cameraLookAt[2] = pointsList[CpLIndex + 1].curpoint.z + 0.5 * pointsList[CpLIndex + 1].normal.z ;
	*/
	cameraNormal[0] = pointsList[CpLIndex].normal.x;
	cameraNormal[1] = pointsList[CpLIndex].normal.y;
	cameraNormal[2] = pointsList[CpLIndex].normal.z;


	
	/*
	cameraPosition[0] = pointsList[0].curpoint.x;
	cameraPosition[1] = pointsList[0].curpoint.y;
	cameraPosition[2] = pointsList[0].curpoint.z;

	cameraLookAt[0] = pointsList[0].curpoint.x + pointsList[0].lookAt.x;
	cameraLookAt[1] = pointsList[0].curpoint.y + pointsList[0].lookAt.y;
	cameraLookAt[2] = pointsList[0].curpoint.z + pointsList[0].lookAt.z;

	cameraNormal[0] = pointsList[0].curpoint.x + pointsList[0].normal.x;
	cameraNormal[1] = pointsList[0].curpoint.y + pointsList[0].normal.y;
	cameraNormal[2] = pointsList[0].curpoint.z + pointsList[0].normal.z;
	*/
	


}

void display()
{
	/* draw 1x1 cube about origin
	replace this code with your height field implementation
	you may also want to precede it with your
	rotation/translation/scaling */
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glPushMatrix();
	setupCamera();
	setLookPosition();
	gluLookAt(cameraPosition[0], cameraPosition[1], cameraPosition[2], cameraLookAt[0], cameraLookAt[1], cameraLookAt[2], cameraNormal[0], cameraNormal[1], cameraNormal[2]);
	//TRANSLATION - Move object on X or Y axis using middle mouse button drag
	//glTranslatef(g_vLandTranslate[0], g_vLandTranslate[1], g_vLandTranslate[2]);
	//SCALE - Zoom in or zoom out using mouse drag + SHIFT key
	//glScalef(g_vLandScale[0], g_vLandScale[1], g_vLandScale[2]);
	//ROTATION - Rotate image along X and Y using left mouse button drag, rotate image along z using right mouse button drag
	//glRotated(g_vLandRotate[0], 1.0, 0.0, 0.0);
	//glRotated(g_vLandRotate[1], 0.0, 1.0, 0.0);
	//glRotated(g_vLandRotate[2], 0.0, 0.0, 1.0);
	//setupXYZaxis(0, 0, 0, 50, 0, 0, 0, 50, 0, 0, 0, 50);
	drawTextureBox(1024, 100 + cameraPosition[2]);
	//drawXYZ(sP, xP, yP, zP);
	//drawPoints();
	//drawPointsNormal();
	//drawPointsTandent();
	//drawPointsBinormal();
	//drawLines();
	//drawSpline();
	drawtracks3d();
	drawCrosssection();
	glPopMatrix();
	glutSwapBuffers();
}

void resizeview(int w, int h)
{
	glViewport(0, 0, w, h);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(45.0, (double)(w / h), 0.01, 1000.0);
}

int loadSplines(char *argv) {
	char *cName = (char *)malloc(128 * sizeof(char));
	FILE *fileList;
	FILE *fileSpline;
	int iType, i = 0, j, iLength;

	/* load the track file */
	fileList = fopen(argv, "r");
	if (fileList == NULL) {
		printf("can't open file\n");
		exit(1);
	}

	/* stores the number of splines in a global variable */
	fscanf(fileList, "%d", &g_iNumOfSplines);

	g_Splines = (struct spline *)malloc(g_iNumOfSplines * sizeof(struct spline));

	/* reads through the spline files */
	for (j = 0; j < g_iNumOfSplines; j++) {
		i = 0;
		fscanf(fileList, "%s", cName);
		fileSpline = fopen(cName, "r");

		if (fileSpline == NULL) {
			printf("can't open file\n");
			exit(1);
		}

		/* gets length for spline file */
		fscanf(fileSpline, "%d %d", &iLength, &iType);

		/* allocate memory for all the points */
		g_Splines[j].points = (struct point *)malloc(iLength * sizeof(struct point));
		g_Splines[j].numControlPoints = iLength;

	

		/* saves the data to the struct */
		while (fscanf(fileSpline, "%lf %lf %lf",
			&g_Splines[j].points[i].x,
			&g_Splines[j].points[i].y,
			&g_Splines[j].points[i].z) != EOF) {
			i++;
		}
	}	
	


	free(cName);

	return 0;
}

/* Write a screenshot to the specified filename */
void saveScreenshot(char *filename)
{
	int i, j;
	Pic *in = NULL;

	if (filename == NULL)
		return;

	/* Allocate a picture buffer */
	in = pic_alloc(640, 480, 3, NULL);

	printf("File to save to: %s\n", filename);

	for (i = 479; i >= 0; i--) {
		glReadPixels(0, 479 - i, 640, 1, GL_RGB, GL_UNSIGNED_BYTE,
			&in->pix[i*in->nx*in->bpp]);
	}

	if (jpeg_write(filename, in))
		printf("File saved Successfully\n");
	else
		printf("Error in Saving\n");

	pic_free(in);
}

/*
	store current Point to point list
*/
void setCurrentPoint(point curpoint, point lookAt){
	pointsList[pLIndex].curpoint.x = curpoint.x;
	pointsList[pLIndex].curpoint.y = curpoint.y;
	pointsList[pLIndex].curpoint.z = curpoint.z;

	pointsList[pLIndex].lookAt.x = lookAt.x;
	pointsList[pLIndex].lookAt.y = lookAt.y;
	pointsList[pLIndex].lookAt.z = lookAt.z;
	pointsList[pLIndex].lookAt = normalize(pointsList[pLIndex].lookAt);
	//Sloan's Method
	if (pLIndex == 0){
		VectorR.x = 0;
		VectorR.y = 0;
		VectorR.z = 1;
		pointsList[pLIndex].normal.x = crossProduct(lookAt,VectorR).x;
		pointsList[pLIndex].normal.y = crossProduct(lookAt, VectorR).y;
		pointsList[pLIndex].normal.z = crossProduct(lookAt, VectorR).z;
		pointsList[pLIndex].normal = normalize(pointsList[pLIndex].normal);
	}
	else{
		pointsList[pLIndex].normal.x = crossProduct(pointsList[pLIndex - 1].biNormal, lookAt).x;
		pointsList[pLIndex].normal.y = crossProduct(pointsList[pLIndex - 1].biNormal, lookAt).y;
		pointsList[pLIndex].normal.z = crossProduct(pointsList[pLIndex - 1].biNormal, lookAt).z;
		pointsList[pLIndex].normal = normalize(pointsList[pLIndex].normal);
	}
		pointsList[pLIndex].biNormal.x = crossProduct(lookAt, pointsList[pLIndex].normal).x;
		pointsList[pLIndex].biNormal.y = crossProduct(lookAt, pointsList[pLIndex].normal).y;
		pointsList[pLIndex].biNormal.z = crossProduct(lookAt, pointsList[pLIndex].normal).z;
		pointsList[pLIndex].biNormal = normalize(pointsList[pLIndex].biNormal);
	/*
	pointsList[pLIndex].biNormal.x = crossProduct(pointsList[pLIndex].lookAt, pointsList[pLIndex].normal).x;
	pointsList[pLIndex].biNormal.y = crossProduct(pointsList[pLIndex].lookAt, pointsList[pLIndex].normal).y;
	pointsList[pLIndex].biNormal.z = crossProduct(pointsList[pLIndex].lookAt, pointsList[pLIndex].normal).z;
	normalize(pointsList[pLIndex].biNormal);
	*/
	

}

/*
	set control point to calculate the point position in spline.
*/
void setControlPoint(int i, int j){

	p1.x = g_Splines[i].points[j - 1].x;
	p1.y = g_Splines[i].points[j - 1].y;
	p1.z = g_Splines[i].points[j - 1].z;

	p2.x = g_Splines[i].points[j].x;
	p2.y = g_Splines[i].points[j].y;
	p2.z = g_Splines[i].points[j].z;

	p3.x = g_Splines[i].points[j + 1].x;
	p3.y = g_Splines[i].points[j + 1].y;
	p3.z = g_Splines[i].points[j + 1].z;

	p4.x = g_Splines[i].points[j + 2].x;
	p4.y = g_Splines[i].points[j + 2].y;
	p4.z = g_Splines[i].points[j + 2].z;
}
/*
	calculate the point position in spline according to u.
*/
point setDrawCRPoint(float u){
	point p; 

	p.x = (p1.x * (-(pow(u, 3) * s) + (2 * pow(u, 2) * s) - (u * s))) +
		(p2.x * ((pow(u, 3) * (2 - s)) + (pow(u, 2) * ((s - 3))) + (1))) +
		(p3.x * ((pow(u, 3) * (s - 2)) + (pow(u, 2) * (3 - (2 * s))) + (u * s))) +
		(p4.x * ((pow(u, 3) * s) - (pow(u, 2) * s)));

	p.y = (p1.y * (-(pow(u, 3) * s) + (2 * pow(u, 2) * s) - (u * s))) +
		(p2.y * ((pow(u, 3) * (2 - s)) + (pow(u, 2) * ((s - 3))) + (1))) +
		(p3.y * ((pow(u, 3) * (s - 2)) + (pow(u, 2) * (3 - (2 * s))) + (u * s))) +
		(p4.y * ((pow(u, 3) * s) - (pow(u, 2) * s)));

	p.z = (p1.z * (-(pow(u, 3) * s) + (2 * pow(u, 2) * s) - (u * s))) +
		(p2.z * ((pow(u, 3) * (2 - s)) + (pow(u, 2) * ((s - 3))) + (1))) +
		(p3.z * ((pow(u, 3) * (s - 2)) + (pow(u, 2) * (3 - (2 * s))) + (u * s))) +
		(p4.z * ((pow(u, 3) * s) - (pow(u, 2) * s)));

	return p;
}
/*
	calculate the point tangent in spline according to u.
*/
point setTangentPoint(float u) {
	point p; 

	p.x = (p1.x * (-(3 * pow(u, 2) * s) + (4 * u * s) - (s))) +
		(p2.x * ((3 * pow(u, 2) * (2 - s)) + (2 * u * ((s - 3))) + (0))) +
		(p3.x * ((3 * pow(u, 2) * (s - 2)) + (2 * u * (3 - (2 * s))) + (s))) +
		(p4.x * ((3 * pow(u, 2) * s) - (2 * u * s)));

	p.y = (p1.y * (-(3 * pow(u, 2) * s) + (4 * u * s) - (s))) +
		(p2.y * ((3 * pow(u, 2) * (2 - s)) + (2 * u * ((s - 3))) + (0))) +
		(p3.y * ((3 * pow(u, 2) * (s - 2)) + (2 * u * (3 - (2 * s))) + (s))) +
		(p4.y * ((3 * pow(u, 2) * s) - (2 * u * s)));

	p.z = (p1.z * (-(3 * pow(u, 2) * s) + (4 * u * s) - (s))) +
		(p2.z * ((3 * pow(u, 2) * (2 - s)) + (2 * u * ((s - 3))) + (0))) +
		(p3.z * ((3 * pow(u, 2) * (s - 2)) + (2 * u * (3 - (2 * s))) + (s))) +
		(p4.z * ((3 * pow(u, 2) * s) - (2 * u * s)));

	return p;
}

/*
	setup xyzaxis, test only
*/
void setupXYZaxis(float spx, float spy, float spz, float xpx, float xpy, float xpz, float ypx, float ypy, float ypz, float zpx, float zpy, float zpz){

	sP.x = spx;
	sP.y = spy;
	sP.z = spz;

	xP.x = xpx;
	xP.y = xpy;
	xP.z = xpz;

	yP.x = ypx;
	yP.y = ypy;
	yP.z = ypz;

	zP.x = zpx;
	zP.y = zpy;
	zP.z = zpz;
}

void menufunc(int value)
{
	switch (value)
	{
	case 0:
		exit(0);
		break;
	}
}

/* converts mouse drags into information about
rotation/translation/scaling */
void mousedrag(int x, int y)
{
	int vMouseDelta[2] = { x - g_vMousePos[0], y - g_vMousePos[1] };

	switch (g_ControlState)
	{
	case TRANSLATE:
		if (g_iLeftMouseButton)
		{
			g_vLandTranslate[0] += vMouseDelta[0] * 0.01;
			g_vLandTranslate[1] -= vMouseDelta[1] * 0.01;
		}
		if (g_iMiddleMouseButton)
		{
			g_vLandTranslate[2] += vMouseDelta[1] * 0.01;
		}
		break;
	case ROTATE:
		if (g_iLeftMouseButton)
		{
			g_vLandRotate[0] += vMouseDelta[1];
			g_vLandRotate[1] += vMouseDelta[0];
		}
		if (g_iMiddleMouseButton)
		{
			g_vLandRotate[2] += vMouseDelta[1];
		}
		break;
	case SCALE:
		if (g_iLeftMouseButton)
		{
			g_vLandScale[0] *= 1.0 + vMouseDelta[1] * 0.01;
			g_vLandScale[1] *= 1.0 + vMouseDelta[1] * 0.01;
			g_vLandScale[2] *= 1.0 + vMouseDelta[1] * 0.01;
		}
		if (g_iMiddleMouseButton)
		{
			//g_vLandScale[2] *= 1.0 - vMouseDelta[1] * 0.01;
		}
		break;
	}
	g_vMousePos[0] = x;
	g_vMousePos[1] = y;
}

void mouseidle(int x, int y)
{
	g_vMousePos[0] = x;
	g_vMousePos[1] = y;
}

void mousebutton(int button, int state, int x, int y)
{

	switch (button)
	{
	case GLUT_LEFT_BUTTON:
		g_iLeftMouseButton = (state == GLUT_DOWN);
		break;
	case GLUT_MIDDLE_BUTTON:
		g_iMiddleMouseButton = (state == GLUT_DOWN);
		break;
	case GLUT_RIGHT_BUTTON:
		g_iRightMouseButton = (state == GLUT_DOWN);
		break;
	}

	switch (glutGetModifiers())
	{
	case GLUT_ACTIVE_CTRL:
		g_ControlState = TRANSLATE;
		break;
	case GLUT_ACTIVE_SHIFT:
		g_ControlState = SCALE;
		break;
	default:
		g_ControlState = ROTATE;
		break;
	}

	g_vMousePos[0] = x;
	g_vMousePos[1] = y;
}

void modechose(unsigned char key, int x, int y)
{
	switch (key) {
	case '1': CpLIndex++;
		if (CpLIndex == pLIndex - 1/uPlus -1){
			CpLIndex = 0;
		}
		break;
	case '2': CpLIndex--;
		if (CpLIndex < 0){
			CpLIndex = pLIndex -  1/ uPlus -2;
		}
		break;
	case '3': CpLIndex+=3;
		if (CpLIndex >= pLIndex - 1 / uPlus - 1){
						CpLIndex = 0;
	}
		break;
	case 27: exit(0);
	}

}

/*
	function for cross product of two vectors
*/
point crossProduct(point p1, point p2){
	point p;
	p.x = p1.y * p2.z - p1.z * p2.y;
	p.y = p1.z * p2.x - p1.x * p2.z;
	p.z = p1.x * p2.y - p1.y * p2.x;
	return p;
}

/*
	function for normalize vector
*/
point normalize(point vector){
	point p;
	float sum = sqrt((vector.x * vector.x + vector.y * vector.y + vector.z * vector.z));

	p.x = vector.x / sum;
	p.y = vector.y / sum;
	p.z = vector.z / sum;
	return p;
}


