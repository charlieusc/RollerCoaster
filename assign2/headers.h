int g_iMenuId;
int g_vMousePos[2] = { 0, 0 };
int g_iLeftMouseButton = 0;    /* 1 if pressed, 0 if not */
int g_iMiddleMouseButton = 0;
int g_iRightMouseButton = 0;

typedef enum { ROTATE, TRANSLATE, SCALE } CONTROLSTATE;

CONTROLSTATE g_ControlState = ROTATE;

/* state of the world */
float g_vLandRotate[3] = { 0.0, 0.0, 0.0 };
float g_vLandTranslate[3] = { 0.0, 0.0, 0.0 };
float g_vLandScale[3] = { 1.0, 1.0, 1.0 };

int winW = 640, winH = 480;
unsigned char drawMode = '3';
GLdouble Rs = 2, Ts = 10, Ss = 0.03;

/* represents one control point along the spline */
struct point {
	double x;
	double y;
	double z;
};

/* spline struct which contains how many control points, and an array of control points */
struct spline {
	int numControlPoints;
	struct point *points;
};

/* the spline array */
struct spline *g_Splines;

/* total number of splines */
int g_iNumOfSplines;


/*
varibles for assign2
*/
float u = 0.0000;
float uPlus = 0.01;
typedef float	myMatrix[4][4];
point p1, p2, p3, p4;
point VectorR;
int pointNuminList;
int pLIndex = 0;
int CpLIndex = 0;
static int counter = 0;
struct myPoint{
	point curpoint;
	point normal;
	point lookAt;
	point biNormal;

};

/* the myPoint array */
struct myPoint *pointsList;

float s = 0.5;
point sP, xP, yP, zP, drawPoint, tangentPoint;

//point for track half Width


//LineWidth
GLfloat LW = 1.5;

//set Camera
float cameraPosition[3] = { 0, 0, 0 };
float cameraLookAt[3] = { 0, 0, 0 };
float cameraNormal[3] = { 0, 0, 0 };

//for texture mapping
Pic* groundTexture;
GLuint groundIndex;
Pic* skyTexture;

//for drawing tracks in 3d
point TrackP;
point V00, V01, V02, V03;
point V10, V11, V12, V13;
//track thick
float alpha = 0.03;
float belowScale = 0.5 ;
point trackhW;
float TWS = 0.2;


//for drawing crosssection
point lP, rP;
float bSforCS = belowScale + alpha;
point crossSectionhW;
float CTS = 0.3;



/*
animation create from here
*/
void doIdle();
/*
load texture image to memory and do glTex initiation
*/
void textureInitiation();
/*
draw XYZ axis, for test only
*/
void drawTextureBox(float groundSize, float belowGround);

/*
draw XYZ axis, for test only
*/
void drawXYZ(point p0, point p1, point p2, point p3);

/*
draw control points in spline, for test only
*/
void drawPoints();
/*
draw Points' Normal of some points in spline, for test only
*/
void drawPointsNormal();
/*
draw Points' Tandent of some points in spline, for test only
*/
void drawPointsTandent();
/*
draw binormal for some points, but it also represents the stick in 2D
*/
void drawPointsBinormal();

/*
this function set Track points for drawing track in 3D
i represents current Track center point Index, LorR represents left or right Track center
*/
void setTrack(int i, int LorR);

/*
draw bcube uing 8 point
*/
void drawQuads(point V00, point V01, point V02, point V03, point V10, point V11, point V12, point V13);
/*
draw tracks in 3D
*/
void drawtracks3d();
/*
this function set Crosssection points for drawing Crosssection in 3D
i represents current Crosssection center point Index
*/
void setCrosssection(int i);
/*
draw Crosssections in 3D
*/
void drawCrosssection();
/*
draw spline, for test only
*/
void drawSpline();
/*
setup gl view
*/
void myinit();
/*
store all the point in the spline using my own struct
it also stores the normal, tangent and binormal of each point too.
*/
void getMyPointList();
/*
setup first sight look
*/
void setupCamera();

void reshape(int w, int h);
/*
setup the cameraposition, where to look at and where the upvector is.
*/
void setLookPosition();

void display();

void resizeview(int w, int h);

int loadSplines(char *argv);

/* Write a screenshot to the specified filename */
void saveScreenshot(char *filename);

/*
store current Point to point list
*/
void setCurrentPoint(point curpoint, point lookAt);

/*
set control point to calculate the point position in spline.
*/
void setControlPoint(int i, int j);
/*
calculate the point position in spline according to u.
*/
point setDrawCRPoint(float u);
/*
calculate the point tangent in spline according to u.
*/
point setTangentPoint(float u);

/*
setup xyzaxis, test only
*/
void setupXYZaxis(float spx, float spy, float spz, float xpx, float xpy, float xpz, float ypx, float ypy, float ypz, float zpx, float zpy, float zpz);

void menufunc(int value);

/* converts mouse drags into information about
rotation/translation/scaling */
void mousedrag(int x, int y);

void mouseidle(int x, int y);

void mousebutton(int button, int state, int x, int y);

void modechose(unsigned char key, int x, int y);

/*
function for cross product of two vectors
*/
point crossProduct(point p1, point p2);

/*
function for normalize vector
*/
point normalize(point vector);


