#include <stdlib.h> // standard definitions
#include <math.h> // math definitions
#include <stdio.h> // standard I/O

#ifdef _APPLE_
#include <GLUT/glut.h>
#else
#include <GL/glut.h>
#endif

// escape key (for exit)
#define ESC 27

// Camera position
float x = 15.0, y = -450.0, z = 80.0; // initially 5 units south of origin

float deltaMove = 0.0; // initially camera doesn't move

// Camera direction
float lx = 0.0, ly = 1.0; // camera points initially along y-axis

float angle = 0.0; // angle of rotation for the camera direction
float deltaAngle = 0.0; // additional angle change when dragging

// Mouse drag control
int isDragging = 0; // true when dragging
int xDragStart = 0; // records the x-coordinate when dragging starts

GLuint texture1;
GLuint texture2;
GLuint texture3;

// Funkcija za iscrtavanje texture
GLuint LoadTexture(const char* filename, int width, int height){
       GLuint texture;
       unsigned char* data;
       FILE* file;
       file=fopen(filename, "rb");
       if(file==NULL)return 0;
       data=(unsigned char*)malloc(width * height * 3);
       fread(data,width * height * 3,1,file);
       fclose(file);
       glGenTextures(1,&texture);
       glBindTexture(GL_TEXTURE_2D,texture);
       glTexEnvf(GL_TEXTURE_ENV,GL_TEXTURE_ENV_MODE,GL_MODULATE);
       glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MIN_FILTER,GL_LINEAR);
       glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
       glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_S,GL_REPEAT);
       glTexParameterf(GL_TEXTURE_2D,GL_TEXTURE_WRAP_T,GL_REPEAT);
       glTexImage2D(GL_TEXTURE_2D,0,GL_RGB,width,height,0,GL_RGB,GL_UNSIGNED_BYTE,data);
       free(data);
       return texture;
}

// Textura - trava
void trava()
{
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture1);
        glEnable(GL_TEXTURE_2D);

        glTranslatef(608,0,1);

        glBegin(GL_POLYGON);

        glTexCoord2d(1.0, 0.0); glVertex3f(-250, -300, 0);
        glTexCoord2d(1.0, 1.0); glVertex3f(-250, 300, 0);
        glTexCoord2d(0.0, 1.0); glVertex3f(250, 300, 0);
        glTexCoord2d(0.0, 0.0); glVertex3f(250, -300, 0);

        glEnd();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

// Textura - beton kocke
void beton()
{
    glPushMatrix();
        glBindTexture(GL_TEXTURE_2D, texture2);
        glEnable(GL_TEXTURE_2D);

        glTranslatef(0,-420,3);

        glBegin(GL_POLYGON);

        glTexCoord2d(1.0, 0.0); glVertex3f(-30, -60, 0);
        glTexCoord2d(1.0, 1.0); glVertex3f(-30, 60, 0);
        glTexCoord2d(0.0, 1.0); glVertex3f(30, 60, 0);
        glTexCoord2d(0.0, 0.0); glVertex3f(30, -60, 0);

        glEnd();

        glDisable(GL_TEXTURE_2D);
    glPopMatrix();
}

void changeSize(int w, int h)
{
	float ratio =  ((float) w) / ((float) h); // window aspect ratio
	glMatrixMode(GL_PROJECTION); // projection matrix is active
	glLoadIdentity(); // reset the projection
	gluPerspective(45.0, ratio, 0.1, 1000.0); // perspective transformation
	glMatrixMode(GL_MODELVIEW); // return to modelview mode
	glViewport(0, 0, w, h); // set viewport (drawing area) to entire window
}

void update(void)
{
	if (deltaMove) { // update camera position
		x += deltaMove * lx * 0.1;
		y += deltaMove * ly * 0.1;
	}
	glutPostRedisplay(); // redisplay everything
}

void crtajPod()
{
    // beton tamno sivi - zgrade
    glColor3f(0.4, 0.4, 0.4);

    glPushMatrix();
         glTranslatef(0,0,1);
         glRotatef(90,1,0,0);
         glScalef(700,0,700);
         glutSolidCube(0.9);
    glPopMatrix();

    // beton sivi - zgrade
    glColor3f(0.7, 0.7, 0.7);

    glPushMatrix();
         glTranslatef(-68,68,2);
         glRotatef(90,1,0,0);
         glScalef(550,0,550);
         glutSolidCube(0.9);
    glPopMatrix();

    // zelena površina - zgrade
    glColor3f(0.122, 0.635, 0.267);

    glPushMatrix();
         glTranslatef(-20,30,3);
         glRotatef(90,1,0,0);
         glScalef(325,0,400);
         glutSolidCube(0.9);
    glPopMatrix();

    // zelena površina - škola
    glColor3f(0.122, 0.635, 0.267);

    glPushMatrix();
         glTranslatef(585,0,1.2);
         glRotatef(90,1,0,0);
         glScalef(600,0,700);
         glutSolidCube(0.9);
    glPopMatrix();

    // sivi okvir zelene površine - škola
    glColor3f(0.7, 0.7, 0.7);

    glPushMatrix();
         glTranslatef(585,-307,2);
         glRotatef(90,1,0,0);
         glScalef(605,0,18);
         glutSolidCube(0.9);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(585,307,2);
         glRotatef(90,1,0,0);
         glScalef(605,0,18);
         glutSolidCube(0.9);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(849,0,2);
         glRotatef(90,1,0,0);
         glScalef(18,0,665);
         glutSolidCube(0.9);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(335.3,0,2);
         glRotatef(90,1,0,0);
         glScalef(50,0,665);
         glutSolidCube(0.9);
    glPopMatrix();

    // bela površina - škola
    glColor3f(1, 1, 1);

    glPushMatrix();
         glTranslatef(402.5,0,2);
         glRotatef(90,1,0,0);
         glScalef(100,0,200);
         glutSolidCube(0.9);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(500,0,2);
         glRotatef(90,1,0,0);
         glScalef(250,0,500);
         glutSolidCube(0.9);
    glPopMatrix();

    // zelena površina - bolnica
    glColor3f(0.122, 0.635, 0.267);

    glPushMatrix();
         glTranslatef(-67.5,-563,0.5);
         glRotatef(90,1,0,0);
         glScalef(550,0,550);
         glutSolidCube(0.9);
    glPopMatrix();

    // siva površina - bolnica
    glColor3f(0.7, 0.7, 0.7);

    glPushMatrix();
         glTranslatef(-68,-562.5,1);
         glRotatef(90,1,0,0);
         glScalef(450,0,550);
         glutSolidCube(0.9);
    glPopMatrix();

    // tamno siva površina - bolnica
    glColor3f(0.4, 0.4, 0.4);

    glPushMatrix();
         glTranslatef(-68,-561,2);
         glRotatef(90,1,0,0);
         glScalef(400,0,450);
         glutSolidCube(0.9);
    glPopMatrix();

    //  beton tamno sivi - supermarket
    glColor3f(0.4, 0.4, 0.4);

    glPushMatrix();
         glTranslatef(495,-562,1);
         glRotatef(90,1,0,0);
         glScalef(700,0,550);
         glutSolidCube(0.9);
    glPopMatrix();

    //  beton sivi - supermarket
    glColor3f(0.7, 0.7, 0.7);

    glPushMatrix();
         glTranslatef(583,-562,2);
         glRotatef(90,1,0,0);
         glScalef(600,0,550);
         glutSolidCube(0.9);
    glPopMatrix();

    //  beton svetlo sivi - supermarket
    glColor3f(0.937, 0.933, 0.945);

    glPushMatrix();
         glTranslatef(650,-553,3);
         glRotatef(90,1,0,0);
         glScalef(300,0,450);
         glutSolidCube(0.9);
    glPopMatrix();

    //  beton tamno plavi - supermarket
    glColor3f(0.392, 0.416, 0.478);

    glPushMatrix();
         glTranslatef(447.5,-553,3);
         glRotatef(90,1,0,0);
         glScalef(150,0,450);
         glutSolidCube(0.9);
    glPopMatrix();

    // parking - supermarket
    glColor3f(0.937, 0.933, 0.945);

    for(float i=-352.5; i>=-753.6; i-=66.85)
    {
        glPushMatrix();
            glTranslatef(447,i,3.5);
            glRotatef(90,1,0,0);
            glScalef(150,0,5);
            glutSolidCube(0.9);
        glPopMatrix();
    }

    for(float i=-352.5; i>=-753.6; i-=66.85)
    {
        glPushMatrix();
            glTranslatef(380,i,3.5);
            glRotatef(90,1,0,0);
            glScalef(8,0,15);
            glutSolidCube(0.9);
        glPopMatrix();
    }

    // isprekidane linije na putu
    glColor3f(1,1,1);

    for(int i=-250; i<=0; i+=35)
    {
        glPushMatrix();
            glTranslatef(i,-250,3);
            glRotatef(90,1,0,0);
            glScalef(25,0,10);
            glutSolidCube(0.9);
        glPopMatrix();
    }

    for(int i=250; i>=0; i-=40)
    {
        glPushMatrix();
            glTranslatef(250,i,3);
            glRotatef(90,1,0,0);
            glScalef(10,0,25);
            glutSolidCube(0.9);
        glPopMatrix();
    }

    glPushMatrix();

        glTranslatef(0,-600,0);

        for(int i=250; i>=-110; i-=40)
        {
            glPushMatrix();
                glTranslatef(250,i,3);
                glRotatef(90,1,0,0);
                glScalef(10,0,25);
                glutSolidCube(0.9);
            glPopMatrix();
        }
    glPopMatrix();

    // pešački prelaz - 1
    for(int i=-192; i>=-302; i-=22)
    {
        glPushMatrix();
            glTranslatef(100,i,3);
            glRotatef(90,1,0,0);
            glScalef(60,0,10);
            glutSolidCube(0.9);
        glPopMatrix();
    }

    // pešački prelaz - 2
    for(int i=190; i<=300; i+=22)
    {
        glPushMatrix();
            glTranslatef(i,-110,3);
            glRotatef(90,1,0,0);
            glScalef(10,0,60);
            glutSolidCube(0.9);
        glPopMatrix();
    }
}

void crtajSuperMarket()
{
    // siva zgrada supermarketa
    glColor3f(0.6, 0.643, 0.655);

    glPushMatrix();
         glTranslatef(650,-553,3);
         glScalef(18,35,22);
         glutSolidCube(10);
    glPopMatrix();

    // žuti krov supermarketa
    glColor3f(0.824, 0.62, 0.18);

    glPushMatrix();
         glTranslatef(650,-553,120);
         glScalef(20,37,2);
         glutSolidCube(10);
    glPopMatrix();

    // okvir prozora
    glColor3f(1,1,1);

    glPushMatrix();
         glTranslatef(560,-420,90);
         glScalef(0.1,6,2);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(560,-490,90);
         glScalef(0.1,6,2);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(560,-553,90);
         glScalef(0.1,4,2);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(560,-615,90);
         glScalef(0.1,6,2);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(560,-685,90);
         glScalef(0.1,6,2);
         glutSolidCube(10);
    glPopMatrix();

    //--------------------------------------

    glPushMatrix();
         glTranslatef(560,-398,40);
         glScalef(0.1,1.5,6);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(560,-430,40);
         glScalef(0.1,3.7,6);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(560,-478,40);
         glScalef(0.1,3.7,6);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(560,-511,40);
         glScalef(0.1,1.5,6);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(0,-195,0);

         glPushMatrix();
            glTranslatef(560,-398,40);
            glScalef(0.1,1.5,6);
            glutSolidCube(10);
         glPopMatrix();

         glPushMatrix();
            glTranslatef(560,-430,40);
            glScalef(0.1,3.7,6);
            glutSolidCube(10);
         glPopMatrix();
    glPopMatrix();

    glPushMatrix();
         glTranslatef(0,-195,0);

         glPushMatrix();
            glTranslatef(560,-478,40);
            glScalef(0.1,3.7,6);
            glutSolidCube(10);
         glPopMatrix();

         glPushMatrix();
            glTranslatef(560,-511,40);
            glScalef(0.1,1.5,6);
            glutSolidCube(10);
         glPopMatrix();
    glPopMatrix();

    // prozori
    glColor3f(0.451, 0.541, 0.451);

    glPushMatrix();
         glTranslatef(559,-420,90);
         glScalef(0.1,5.5,1.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(559,-490,90);
         glScalef(0.1,5.5,1.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(559,-553,90);
         glScalef(0.1,3.5,1.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(559,-615,90);
         glScalef(0.1,5.5,1.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(559,-685,90);
         glScalef(0.1,5.5,1.5);
         glutSolidCube(10);
    glPopMatrix();

    //--------------------------------------

    glPushMatrix();
         glTranslatef(559,-398,40);
         glScalef(0.1,1,5.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(559,-430,40);
         glScalef(0.1,3.2,5.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(559,-478,40);
         glScalef(0.1,3.2,5.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(559,-511,40);
         glScalef(0.1,1,5.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(0,-195,0);

         glPushMatrix();
            glTranslatef(559,-398,40);
            glScalef(0.1,1,5.5);
            glutSolidCube(10);
         glPopMatrix();

         glPushMatrix();
            glTranslatef(559,-430,40);
            glScalef(0.1,3.2,5.5);
            glutSolidCube(10);
         glPopMatrix();
    glPopMatrix();

    glPushMatrix();
         glTranslatef(0,-195,0);

         glPushMatrix();
            glTranslatef(559,-478,40);
            glScalef(0.1,3.2,5.5);
            glutSolidCube(10);
         glPopMatrix();

         glPushMatrix();
            glTranslatef(559,-511,40);
            glScalef(0.1,1,5.5);
            glutSolidCube(10);
         glPopMatrix();
    glPopMatrix();

    // okvir vrata
    glColor3f(1,1,1);

    glPushMatrix();
         glTranslatef(559,-553,35);
         glScalef(0.1,4.3,7.5);
         glutSolidCube(10);
    glPopMatrix();

    // vrata
    glColor3f(0.282, 0.29, 0.271);

    glPushMatrix();
         glTranslatef(558,-553,35);
         glScalef(0.1,3.8,7);
         glutSolidCube(10);
    glPopMatrix();

    glColor3f(1,1,1);

    glPushMatrix();
         glTranslatef(557,-553,35);
         glScalef(0.1,0.3,7.5);
         glutSolidCube(10);
    glPopMatrix();

    // kvaka
    glColor3f(1,1,1);

    glPushMatrix();
         glTranslatef(557,-545,35);
         glScalef(0.1,1,1);
         glutSolidSphere(3,10,10);
    glPopMatrix();
    glPushMatrix();
         glTranslatef(557,-560,35);
         glScalef(0.1,1,1);
         glutSolidSphere(3,10,10);
    glPopMatrix();
}

void crtajBolnicu()
{
    // beli deo zgrade
    glColor3f(0.961, 0.961, 0.961);

    glPushMatrix();
         glTranslatef(0,-600,10);
         glScalef(18,22,30);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(-130,-600,30);
         glScalef(18,22,10);
         glutSolidCube(10);
    glPopMatrix();

    // prelaz preko zgrade
    glColor3f(0.678, 0.678, 0.678);

    glPushMatrix();
         glTranslatef(0,-490,95);
         glScalef(18,0.1,0.5);
         glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.824, 0.824, 0.831);

    glPushMatrix();
         glTranslatef(0,-490,105);
         glScalef(18,0.1,0.5);
         glutSolidCube(10);
    glPopMatrix();

    // plavi okvir zgrade
    glColor3f(0.145, 0.671, 0.878);

    glPushMatrix();
         glTranslatef(0,-600,160);
         glScalef(19.5,23.5,1);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(-160,-600,80);
         glScalef(14,23,1);
         glutSolidCube(10);
    glPopMatrix();

    // crveni krst - bolnica
    glColor3f(0.878, 0.149, 0.149);

    glPushMatrix();
         glTranslatef(0,-490,130);
         glScalef(3,0.1,1);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(0,-490,130);
         glScalef(1,0.1,3);
         glutSolidCube(10);
    glPopMatrix();

    // okvir vrata od graže
    glColor3f(0.741, 0.737, 0.761);

    glPushMatrix();
         glTranslatef(-153,-490,20);
         glScalef(10.5,0.1,5.5);
         glutSolidCube(10);
    glPopMatrix();

    // vrata od graže
    glColor3f(0.259, 0.353, 0.361);

    glPushMatrix();
         glTranslatef(-153,-489,20);
         glScalef(9.5,0.1,4.5);
         glutSolidCube(10);
    glPopMatrix();

    // okvir vrata
    glColor3f(0.741, 0.737, 0.761);

    glPushMatrix();
         glTranslatef(0,-490,20);
         glScalef(8.5,0.1,5.5);
         glutSolidCube(10);
    glPopMatrix();

    // vrata - tamniji deo
    glColor3f(0.259, 0.353, 0.361);

    glPushMatrix();
         glTranslatef(0,-489,20);
         glScalef(7.5,0.1,4.5);
         glutSolidCube(10);
    glPopMatrix();

    // vrata - svetliji deo
    glColor3f(0.961, 0.961, 0.961);

    glPushMatrix();
         glTranslatef(18,-488,20);
         glScalef(3,0.1,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(-18,-488,20);
         glScalef(3,0.1,3.5);
         glutSolidCube(10);
    glPopMatrix();

    // nadstrešnica
    glColor3f(0.741, 0.737, 0.761);

    glPushMatrix();
         glTranslatef(0,-490,65);
         glScalef(11.5,10,0.8);
         glutSolidCube(10);
    glPopMatrix();

    // stube za nadstrešnicu
    glColor3f(0.259, 0.353, 0.361);

    glPushMatrix();
         glTranslatef(45,-450,15);
         glScalef(0.5,0.5,10);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(-45,-450,15);
         glScalef(0.5,0.5,10);
         glutSolidCube(10);
    glPopMatrix();

    // okvir prozora
    glColor3f(0.733, 0.784, 0.808);

    glPushMatrix();
         glTranslatef(90,-650,115);
         glScalef(0.1,4.5,4.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(90,-550,115);
         glScalef(0.1,4.5,4.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(90,-650,45);
         glScalef(0.1,4.5,4.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(90,-550,45);
         glScalef(0.1,4.5,4.5);
         glutSolidCube(10);
    glPopMatrix();

    // prozori
    glColor3f(0.259, 0.353, 0.361);

    glPushMatrix();
         glTranslatef(90.5,-650,115);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(90.5,-550,115);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(90.5,-650,45);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(90.5,-550,45);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();
}

void crtajSkolu()
{
    // zgrada škole
    glColor3f(0.812, 0.722, 0.667);

    glPushMatrix();
         glTranslatef(500,0,10);
         glScalef(10,35,30);
         glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.733, 0.408, 0.455);

    glPushMatrix();
         glTranslatef(500,0,30);
         glScalef(12,15,30);
         glutSolidCube(10);
    glPopMatrix();

    // nadstrešnica
    glColor3f(0.988, 0.988, 0.969);

    glPushMatrix();
         glTranslatef(435,-2,50);
         glScalef(8,10,0.5);
         glutSolidCube(10);
    glPopMatrix();

    // stube za nadstrešnicu
    glColor3f(0.239, 0.298, 0.329);

    glPushMatrix();
         glTranslatef(405,-40,17);
         glScalef(0.5,0.5,7);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(405,35,17);
         glScalef(0.5,0.5,7);
         glutSolidCube(10);
    glPopMatrix();

    // vrata škole
    glColor3f(0.812, 0.722, 0.667);

    glPushMatrix();
         glTranslatef(440,-1.5,17);
         glScalef(0.1,8,5);
         glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.239, 0.298, 0.329);

    glPushMatrix();
         glTranslatef(439,17.5,14);
         glScalef(0.1,3.5,5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(439,-21,14);
         glScalef(0.1,3.5,5);
         glutSolidCube(10);
    glPopMatrix();

    // prozor na vratima škole

    glColor3f(0.792, 0.867, 0.91);

    glPushMatrix();
         glTranslatef(438,17.5,30);
         glScalef(0.1,2.5,1);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(438,-21,30);
         glScalef(0.1,2.5,1);
         glutSolidCube(10);
    glPopMatrix();

    // kvaka na vratima

    glColor3f(0,0,0);

    glPushMatrix();
         glTranslatef(437,4,15);
         glScalef(0.7,0.7,0.7);
         glutSolidSphere(3,10,10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(437,-8,15);
         glScalef(0.7,0.7,0.7);
         glutSolidSphere(3,10,10);
    glPopMatrix();

    // prozori na crveni deo zgrade - škole

    glColor3f(0.69, 0.733, 0.773);

    glPushMatrix();
         glTranslatef(439,45,115);
         glScalef(0.1,3,5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(439,0,115);
         glScalef(0.1,3,5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(439,-45,115);
         glScalef(0.1,3,5);
         glutSolidCube(10);
    glPopMatrix();

    // okvir prozora na crveni deo zgrade - škole

    glColor3f(0, 0, 0);

    glPushMatrix();
         glTranslatef(440,45,115);
         glScalef(0.1,3.5,5.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(440,0,115);
         glScalef(0.1,3.5,5.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(440,-45,115);
         glScalef(0.1,3.5,5.5);
         glutSolidCube(10);
    glPopMatrix();

    // prozori na beli deo zgrade - škole

    glColor3f(0.69, 0.733, 0.773);

    glPushMatrix();
         glTranslatef(449,145,125);
         glScalef(0.1,3,3);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(449,100,125);
         glScalef(0.1,3,3);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(449,145,80);
         glScalef(0.1,3,3);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(449,100,80);
         glScalef(0.1,3,3);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(449,145,35);
         glScalef(0.1,3,3);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(449,100,35);
         glScalef(0.1,3,3);
         glutSolidCube(10);
    glPopMatrix();

    //-------------------------------------

    glPushMatrix();
         glTranslatef(449,-145,125);
         glScalef(0.1,3,3);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(449,-100,125);
         glScalef(0.1,3,3);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(449,-145,80);
         glScalef(0.1,3,3);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(449,-100,80);
         glScalef(0.1,3,3);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(449,-145,35);
         glScalef(0.1,3,3);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(449,-100,35);
         glScalef(0.1,3,3);
         glutSolidCube(10);
    glPopMatrix();

    // okvir prozora na beli deo zgrade - škole

    glColor3f(1, 1, 1);

    glPushMatrix();
         glTranslatef(450,145,125);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(450,100,125);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(450,145,80);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(450,100,80);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(450,145,35);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(450,100,35);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    //-------------------------------------

    glPushMatrix();
         glTranslatef(450,-145,125);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(450,-100,125);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(450,-145,80);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(450,-100,80);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(450,-145,35);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(450,-100,35);
         glScalef(0.1,3.5,3.5);
         glutSolidCube(10);
    glPopMatrix();
}

void crtajSto_za_stoni_tenis()
{
    // noge od stola za stoni tenis
    glColor3f(0.204, 0.216, 0.208);

    glPushMatrix();
         glTranslatef(670,100,2);
         glScalef(0.3,0.3,5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(720,100,2);
         glScalef(0.3,0.3,5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(670,50,2);
         glScalef(0.3,0.3,5);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(720,50,2);
         glScalef(0.3,0.3,5);
         glutSolidCube(10);
    glPopMatrix();

    // sto za stoni tenis
    glColor3f(0.278, 0.667, 0.624);

    glPushMatrix();
         glTranslatef(695,75,26);
         glScalef(7,8,0.3);
         glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.914, 0.925, 0.925);

    glPushMatrix();
         glTranslatef(695,75,27.2);
         glScalef(1,7.8,0.1);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(695,75,30);
         glScalef(6.8,0.3,1);
         glutSolidCube(10);
    glPopMatrix();

    // reket za stoni tenis
    glColor3f(0.976, 0.02, 0.051);

    glPushMatrix();
         glTranslatef(675,55,28);
         glScalef(1,1,0.1);
         glutSolidSphere(8,10,10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(715,92,28);
         glScalef(1,1,0.1);
         glutSolidSphere(8,10,10);
    glPopMatrix();

    glColor3f(0,0,0);

    glPushMatrix();
         glTranslatef(675,48,27.5);
         glScalef(0.2,1.8,0.1);
         glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
         glTranslatef(715,98,27.5);
         glScalef(0.2,1.8,0.1);
         glutSolidCube(10);
    glPopMatrix();
}

void crtajZgradu_1()
{
    // crvena zgrada
    glColor3f(0.508,0.184,0.1058);

    glPushMatrix();
        glTranslatef(-230,-100,10);
        glScalef(10,10,30);
        glutSolidCube(10);
    glPopMatrix();

    // sivi krov
    glColor3f(0.8,0.8,0.8);

    glPushMatrix();
        glTranslatef(-230,-100,160);
        glScalef(12,12,1);
        glutSolidCube(10);
    glPopMatrix();

    // okvir za prozore
    glColor3f(0.298,0.110,0.0745);

    glPushMatrix();
        glTranslatef(-250,-150,120);
        glScalef(2.8,0.1,3.8);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-210,-150,120);
        glScalef(2.8,0.1,3.8);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-250,-150,80);
        glScalef(2.8,0.1,3.8);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-210,-150,80);
        glScalef(2.8,0.1,3.8);
        glutSolidCube(10);
    glPopMatrix();

    // prozori
    glColor3f(0.337,0.608,0.839);

    glPushMatrix();
        glTranslatef(-250,-151,120);
        glScalef(2,0.1,3);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-210,-151,120);
        glScalef(2,0.1,3);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-250,-151,80);
        glScalef(2,0.1,3);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-210,-151,80);
        glScalef(2,0.1,3);
        glutSolidCube(10);
    glPopMatrix();

    // linije na prozoru
    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-250,-152,120);
        glScalef(0.1,0.1,3);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-210,-152,120);
        glScalef(0.1,0.1,3);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-250,-152,80);
        glScalef(0.1,0.1,3);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-210,-152,80);
        glScalef(0.1,0.1,3);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-250,-152,120);
        glScalef(2,0.1,0.1);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-210,-152,120);
        glScalef(2,0.1,0.1);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-250,-152,80);
        glScalef(2,0.1,0.1);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-210,-152,80);
        glScalef(2,0.1,0.1);
        glutSolidCube(10);
    glPopMatrix();

    // okvir vrata
    glColor3f(0.8,0.8,0.8);

    glPushMatrix();
        glTranslatef(-230,-150,22);
        glScalef(3,0.1,4);
        glutSolidCube(10);
    glPopMatrix();

    // vrata
    glColor3f(0.941, 0.314, 0.188);

    glPushMatrix();
        glTranslatef(-230,-151,20);
        glScalef(2,0.1,3.5);
        glutSolidCube(10);
    glPopMatrix();

    // prozor na vratima
    glColor3f(0.337,0.608,0.839);

    glPushMatrix();
        glTranslatef(-230,-152,29);
        glScalef(1.5,0.1,1);
        glutSolidCube(10);
    glPopMatrix();

    // kvaka na vratima
    glColor3f(0,0,0);

    glPushMatrix();
        glTranslatef(-235,-152,18);
        glScalef(1.5,0.1,1);
        glutSolidSphere(1.5,10,10);
    glPopMatrix();
}

void crtajZgradu_2()
{
    // plavi deo zgrade
    glColor3f(0.416, 0.663, 0.792);

    glPushMatrix();
        glTranslatef(70,-100,10);
        glScalef(12,10,10);
        glutSolidCube(10);
    glPopMatrix();

    // beli deo zgrade
    glColor3f(0.914, 0.843, 0.831);

    glPushMatrix();
        glTranslatef(70,-100,10);
        glScalef(10,8,40);
        glutSolidCube(10);
    glPopMatrix();

    // crveni krov
    glColor3f(0.62, 0.247, 0.157);

    glPushMatrix();
        glTranslatef(70,-100,206);
        glScalef(12,10,1);
        glutSolidCube(10);
    glPopMatrix();

    // okvir za prozore
    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(40,-140,170);
        glScalef(2.5,0.1,2.5);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(87,-140,170);
        glScalef(4.5,0.1,2.5);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(40,-140,100);
        glScalef(2.5,0.1,2.5);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(87,-140,100);
        glScalef(4.5,0.1,2.5);
        glutSolidCube(10);
    glPopMatrix();

    // okvir prozora sa druge (desne) strane
    glPushMatrix();
        glTranslatef(130,-100,30);
        glRotatef(90,0,0,1);
        glScalef(5.5,0.1,4);
        glutSolidCube(10);
    glPopMatrix();

    // prozor
    glColor3f(0.451, 0.451, 0.584);

    glPushMatrix();
        glTranslatef(40,-141,170);
        glScalef(2,0.1,2);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(87,-141,170);
        glScalef(4,0.1,2);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(40,-141,100);
        glScalef(2,0.1,2);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(87,-141,100);
        glScalef(4,0.1,2);
        glutSolidCube(10);
    glPopMatrix();

    // prozor sa druge (desne) strane
    glColor3f(0.302, 0.306, 0.322);

    glPushMatrix();
        glTranslatef(131,-100,40);
        glRotatef(90,0,0,1);
        glScalef(4.5,0.1,1.5);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(131,-100,20);
        glRotatef(90,0,0,1);
        glScalef(4.5,0.1,1.5);
        glutSolidCube(10);
    glPopMatrix();

    // okvir vrata
    glColor3f(0.8,0.8,0.8);

    glPushMatrix();
        glTranslatef(40,-150,22);
        glScalef(3,0.1,4);
        glutSolidCube(10);
    glPopMatrix();

    // vrata
    glColor3f(0.941, 0.314, 0.188);

    glPushMatrix();
        glTranslatef(40,-151,20);
        glScalef(2,0.1,3.5);
        glutSolidCube(10);
    glPopMatrix();

    // prozor na vratima
    glColor3f(0.337,0.608,0.839);

    glPushMatrix();
        glTranslatef(40,-152,29);
        glScalef(1.5,0.1,1);
        glutSolidCube(10);
    glPopMatrix();

    // kvaka na vratima
    glColor3f(0,0,0);

    glPushMatrix();
        glTranslatef(35,-152,18);
        glScalef(1.5,0.1,1);
        glutSolidSphere(1.5,10,10);
    glPopMatrix();
}

void crtajZgradu_3()
{
    // beli deo zgrade
    glColor3f(0.871, 0.875, 0.882);

    glPushMatrix();
        glTranslatef(2,80,10);
        glScalef(25,10,25);
        glutSolidCube(10);
    glPopMatrix();

    // crveni deo zgrade
    glColor3f(0.514, 0.173, 0.106);

    glPushMatrix();
        glTranslatef(2,80,10);
        glScalef(25.2,10.2,8);
        glutSolidCube(10);
    glPopMatrix();

    // sivi krov zgrade
    glColor3f(0.537, 0.541, 0.549);

    glPushMatrix();
        glTranslatef(2,80,140);
        glScalef(27,12,1);
        glutSolidCube(10);
    glPopMatrix();

    // okvir vrata
    glColor3f(0.8,0.8,0.8);

    glPushMatrix();
        glTranslatef(127.8,70,22);
        glRotatef(90,0,0,1);
        glScalef(3,0.1,4);
        glutSolidCube(10);
    glPopMatrix();

    // vrata
    glColor3f(0.941, 0.314, 0.188);

    glPushMatrix();
        glTranslatef(128.2,70,20);
        glRotatef(90,0,0,1);
        glScalef(2,0.1,3.5);
        glutSolidCube(10);
    glPopMatrix();

    // prozor na vratima
    glColor3f(0.337,0.608,0.839);

    glPushMatrix();
        glTranslatef(128.4,70,29);
        glRotatef(90,0,0,1);
        glScalef(1.5,0.1,1);
        glutSolidCube(10);
    glPopMatrix();

    // kvaka na vratima
    glColor3f(0,0,0);

    glPushMatrix();
        glTranslatef(128.8,75,18);
        glRotatef(90,0,0,1);
        glScalef(1.5,0.1,1);
        glutSolidSphere(1.5,10,10);
    glPopMatrix();

    // okvir za prozore
    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(-60,30,100);
        glScalef(6,0.1,2.5);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(60,30,100);
        glScalef(6,0.1,2.5);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-60,29,50);
        glScalef(6,0.1,2.5);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(60,29,50);
        glScalef(6,0.1,2.5);
        glutSolidCube(10);
    glPopMatrix();

    // prozori
    glColor3f(0.443, 0.451, 0.58);

    glPushMatrix();
        glTranslatef(-72,29.5,100);
        glScalef(2,0.1,2);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-47,29.5,100);
        glScalef(2,0.1,2);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(48,29.5,100);
        glScalef(2,0.1,2);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(73,29.5,100);
        glScalef(2,0.1,2);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-72,28.5,50);
        glScalef(2,0.1,2);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(-47,28.5,50);
        glScalef(2,0.1,2);
        glutSolidCube(10);
    glPopMatrix();
        glPushMatrix();
        glTranslatef(48,28.5,50);
        glScalef(2,0.1,2);
        glutSolidCube(10);
    glPopMatrix();
    glPushMatrix();
        glTranslatef(73,28.5,50);
        glScalef(2,0.1,2);
        glutSolidCube(10);
    glPopMatrix();
}

void crtajBandere()
{
    // sivi stub
    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(-260,-170,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    // zeleni okvir stuba
    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(-260,-170,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    // okvir sijalica
    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(-260,-170,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    // sijalica
    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(-260,-170,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    //--------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(-100,-170,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(-100,-170,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(-100,-170,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(-100,-170,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    //----------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(60,-170,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(60,-170,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(60,-170,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(60,-170,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    // --------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(170,-170,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(170,-170,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(170,-170,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(170,-170,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    // --------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(170,-50,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(170,-50,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(170,-50,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(170,-50,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    // --------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(170,80,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(170,80,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(170,80,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(170,80,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    // --------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(170,220,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(170,220,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(170,220,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(170,220,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    // --------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(320,220,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(320,220,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(320,220,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(320,220,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    // --------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(320,80,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(320,80,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(320,80,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(320,80,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    // --------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(320,-80,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(320,-80,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(320,-80,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(320,-80,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    // --------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(320,-240,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(320,-240,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(320,-240,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(320,-240,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    // --------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(320,-325,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(320,-325,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(320,-325,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(320,-325,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    // --------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(320,-780,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(320,-780,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(320,-780,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(320,-780,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    //--------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(-250,-330,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(-250,-330,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(-250,-330,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(-250,-330,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    //--------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(-70,-330,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(-70,-330,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(-70,-330,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(-70,-330,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();

    //--------------------------------------

    glColor3f(0.5,0.5,0.5);

    glPushMatrix();
        glTranslatef(50,-330,5);
        glScalef(0.3,0.3,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.086, 0.561, 0.22);

    glPushMatrix();
        glTranslatef(50,-330,5);
        glScalef(0.4,0.4,5);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1, 1, 1);

    glPushMatrix();
        glTranslatef(50,-330,60);
        glScalef(2,2,2);
        glutWireSphere(3,10,10);
    glPopMatrix();

    glColor3f(1, 0.98, 0);

    glPushMatrix();
        glTranslatef(50,-330,58);
        glScalef(2,2,2);
        glutSolidSphere(2,10,10);
    glPopMatrix();
}

void crtajDrvece()
{
    // stablo
    glColor3f(0.678, 0.361, 0.263);

    glPushMatrix();
        glTranslatef(0,250,5);
        glScalef(0.5,0.5,10);
        glutSolidCube(10);
    glPopMatrix();

    // krošnja
    glColor3f(0.129, 0.651, 0.278);

    glPushMatrix();
        glTranslatef(0,250,20);
        glScalef(7,5,10);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    glColor3f(0.176, 0.831, 0.361);

    glPushMatrix();
        glTranslatef(0,250,35);
        glScalef(7,5,8);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    //---------------------------------------

    glColor3f(0.678, 0.361, 0.263);

    glPushMatrix();
        glTranslatef(-150,250,5);
        glScalef(0.5,0.5,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.129, 0.651, 0.278);

    glPushMatrix();
        glTranslatef(-150,250,20);
        glScalef(7,5,10);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    glColor3f(0.176, 0.831, 0.361);

    glPushMatrix();
        glTranslatef(-150,250,35);
        glScalef(7,5,8);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    //---------------------------------------

    glColor3f(0.678, 0.361, 0.263);

    glPushMatrix();
        glTranslatef(-270,150,5);
        glScalef(0.5,0.5,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.129, 0.651, 0.278);

    glPushMatrix();
        glTranslatef(-270,150,20);
        glScalef(7,5,10);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    glColor3f(0.176, 0.831, 0.361);

    glPushMatrix();
        glTranslatef(-270,150,35);
        glScalef(7,5,8);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    //--------------------------------

    glColor3f(0.678, 0.361, 0.263);

    glPushMatrix();
        glTranslatef(-270,20,5);
        glScalef(0.5,0.5,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.129, 0.651, 0.278);

    glPushMatrix();
        glTranslatef(-270,20,20);
        glScalef(7,5,10);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    glColor3f(0.176, 0.831, 0.361);

    glPushMatrix();
        glTranslatef(-270,20,35);
        glScalef(7,5,8);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    //--------------------------------

    glColor3f(0.678, 0.361, 0.263);

    glPushMatrix();
        glTranslatef(-100,-80,5);
        glScalef(0.5,0.5,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.129, 0.651, 0.278);

    glPushMatrix();
        glTranslatef(-100,-80,20);
        glScalef(7,5,10);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    glColor3f(0.176, 0.831, 0.361);

    glPushMatrix();
        glTranslatef(-100,-80,35);
        glScalef(7,5,8);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    //--------------------------------

    for(int i=-350; i>=-740; i-=130)
    {
        glColor3f(0.678, 0.361, 0.263);

        glPushMatrix();
            glTranslatef(155,i,5);
            glScalef(0.5,0.5,10);
            glutSolidCube(10);
        glPopMatrix();

        glColor3f(0.129, 0.651, 0.278);

        glPushMatrix();
            glTranslatef(155,i,20);
            glScalef(7,5,10);
            glutSolidCone(3,4,10,10);
        glPopMatrix();

        glColor3f(0.176, 0.831, 0.361);

        glPushMatrix();
            glTranslatef(155,i,35);
            glScalef(7,5,8);
            glutSolidCone(3,4,10,10);
        glPopMatrix();
    }

    //--------------------------------

    glColor3f(0.678, 0.361, 0.263);

    glPushMatrix();
        glTranslatef(400,-270,5);
        glScalef(0.5,0.5,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.129, 0.651, 0.278);

    glPushMatrix();
        glTranslatef(400,-270,20);
        glScalef(7,5,10);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    glColor3f(0.176, 0.831, 0.361);

    glPushMatrix();
        glTranslatef(400,-270,35);
        glScalef(7,5,8);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    //--------------------------------

    glColor3f(0.678, 0.361, 0.263);

    glPushMatrix();
        glTranslatef(550,-270,5);
        glScalef(0.5,0.5,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.129, 0.651, 0.278);

    glPushMatrix();
        glTranslatef(550,-270,20);
        glScalef(7,5,10);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    glColor3f(0.176, 0.831, 0.361);

    glPushMatrix();
        glTranslatef(550,-270,35);
        glScalef(7,5,8);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    //--------------------------------

    glColor3f(0.678, 0.361, 0.263);

    glPushMatrix();
        glTranslatef(700,-270,5);
        glScalef(0.5,0.5,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.129, 0.651, 0.278);

    glPushMatrix();
        glTranslatef(700,-270,20);
        glScalef(7,5,10);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    glColor3f(0.176, 0.831, 0.361);

    glPushMatrix();
        glTranslatef(700,-270,35);
        glScalef(7,5,8);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    //--------------------------------

    glColor3f(0.678, 0.361, 0.263);

    glPushMatrix();
        glTranslatef(400,260,5);
        glScalef(0.5,0.5,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.129, 0.651, 0.278);

    glPushMatrix();
        glTranslatef(400,260,20);
        glScalef(7,5,10);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    glColor3f(0.176, 0.831, 0.361);

    glPushMatrix();
        glTranslatef(400,260,35);
        glScalef(7,5,8);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    //--------------------------------

    glColor3f(0.678, 0.361, 0.263);

    glPushMatrix();
        glTranslatef(550,260,5);
        glScalef(0.5,0.5,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.129, 0.651, 0.278);

    glPushMatrix();
        glTranslatef(550,260,20);
        glScalef(7,5,10);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    glColor3f(0.176, 0.831, 0.361);

    glPushMatrix();
        glTranslatef(550,260,35);
        glScalef(7,5,8);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    //--------------------------------

    glColor3f(0.678, 0.361, 0.263);

    glPushMatrix();
        glTranslatef(700,260,5);
        glScalef(0.5,0.5,10);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(0.129, 0.651, 0.278);

    glPushMatrix();
        glTranslatef(700,260,20);
        glScalef(7,5,10);
        glutSolidCone(3,4,10,10);
    glPopMatrix();

    glColor3f(0.176, 0.831, 0.361);

    glPushMatrix();
        glTranslatef(700,260,35);
        glScalef(7,5,8);
        glutSolidCone(3,4,10,10);
    glPopMatrix();
}

void crtajOgradu()
{
    // Ograda za zgrade

    // crvena - smedja boja
    glColor3f(0.322, 0.098, 0.067);

    // deblji stubovi ograde (leva strana)
    for(int i=-145; i<=205; i+=70)
    {
        glPushMatrix();
            glTranslatef(-165,i,15);
            glScalef(0.5,0.5,3);
            glutSolidCube(10);
        glPopMatrix();
    }

    // deblji stubovi ograde (zadnja strana)
    for(int i=-165; i<=123; i+=72)
    {
        glPushMatrix();
            glTranslatef(i,205,15);
            glScalef(0.5,0.5,3);
            glutSolidCube(10);
        glPopMatrix();
    }

    // tanji stubovi ograde (leva strana)
    for(int i=-135; i<=-85; i+=10)
    {
        glPushMatrix();
            glTranslatef(-165,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }

    for(int i=-65; i<=-15; i+=10)
    {
        glPushMatrix();
            glTranslatef(-165,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }

    for(int i=5; i<=55; i+=10)
    {
        glPushMatrix();
            glTranslatef(-165,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }

    for(int i=75; i<=125; i+=10)
    {
        glPushMatrix();
            glTranslatef(-165,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }

    for(int i=145; i<=195; i+=10)
    {
        glPushMatrix();
            glTranslatef(-165,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }

    // tanji stubovi ograde (zadnja strana)
    for(int i=-155; i<=-105; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,205,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=-82; i<=-32; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,205,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=-10; i<=40; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,205,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=63; i<=113; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,205,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }

    // horizontalna stuba (leva strana)
    glPushMatrix();
        glTranslatef(-165,30,15);
        glScalef(0.1,35,0.8);
        glutSolidCube(10);
    glPopMatrix();

    // horizontalna stuba (zadnja strana)
    glPushMatrix();
        glTranslatef(-20,205,15);
        glScalef(29,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    // siva boja
    glColor3f(0.8, 0.8, 0.8);

    // deblji stubovi ograde
    for(int i=-155; i<=-95; i+=60)
    {
        glPushMatrix();
            glTranslatef(i,-145,15);
            glScalef(0.5,0.5,3);
            glutSolidCube(10);
        glPopMatrix();
    }

    for(int i=-55; i<=5; i+=60)
    {
        glPushMatrix();
            glTranslatef(i,-145,15);
            glScalef(0.5,0.5,3);
            glutSolidCube(10);
        glPopMatrix();
    }

    // tanji stubovi ograde
    for(int i=-145; i<=-105; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,-145,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }

    for(int i=-45; i<=-5; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,-145,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }

    // horizontalna stuba
    glPushMatrix();
        glTranslatef(-125,-145,15);
        glScalef(7,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-25,-145,15);
        glScalef(7,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    // Ograda za školu

    // crvena - smedja boja
    glColor3f(0.322, 0.098, 0.067);

    // deblji stubovi ograde (leva strana)
    for(int i=365; i<=855; i+=70)
    {
        glPushMatrix();
            glTranslatef(i,312,15);
            glScalef(0.5,0.5,3);
            glutSolidCube(10);
        glPopMatrix();
    }

    // tanji stubovi ograde (leva strana)
    for(int i=375; i<=425; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,312,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=445; i<=495; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,312,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=515; i<=565; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,312,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=585; i<=635; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,312,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=655; i<=705; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,312,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=725; i<=775; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,312,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=795; i<=845; i+=10)
    {
        glPushMatrix();
            glTranslatef(i,312,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }

    // horizontalni stub (leva strana)
    glPushMatrix();
        glTranslatef(605,312,15);
        glScalef(50,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    // deblji stubovi ograde (zadnja strana)
    for(int i=312; i>=-313; i-=69.5)
    {
        glPushMatrix();
            glTranslatef(855,i,15);
            glScalef(0.5,0.5,3);
            glutSolidCube(10);
        glPopMatrix();
    }

    // tanji stubovi ograde (zadnja strana)
    for(int i=302; i>=252; i-=10)
    {
        glPushMatrix();
            glTranslatef(855,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=232; i>=182; i-=10)
    {
        glPushMatrix();
            glTranslatef(855,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=162; i>=112; i-=10)
    {
        glPushMatrix();
            glTranslatef(855,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=92; i>=42; i-=10)
    {
        glPushMatrix();
            glTranslatef(855,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=22; i>=-28; i-=10)
    {
        glPushMatrix();
            glTranslatef(855,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=-48; i>=-98; i-=10)
    {
        glPushMatrix();
            glTranslatef(855,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=-114; i>=-164; i-=10)
    {
        glPushMatrix();
            glTranslatef(855,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=-184; i>=-234; i-=10)
    {
        glPushMatrix();
            glTranslatef(855,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=-254; i>=-304; i-=10)
    {
        glPushMatrix();
            glTranslatef(855,i,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }

    // horizontalni stub (zadnja strana)
    glPushMatrix();
        glTranslatef(855,0,15);
        glScalef(0.1,62,0.8);
        glutSolidCube(10);
    glPopMatrix();

    // deblji stubovi ograde (desna strana)
    for(int i=855; i>=365; i-=70)
    {
        glPushMatrix();
            glTranslatef(i,-313,15);
            glScalef(0.5,0.5,3);
            glutSolidCube(10);
        glPopMatrix();
    }

    // tanji stubovi ograde (desna strana)
    for(int i=845; i>=795; i-=10)
    {
        glPushMatrix();
            glTranslatef(i,-313,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=775; i>=725; i-=10)
    {
        glPushMatrix();
            glTranslatef(i,-313,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=705; i>=655; i-=10)
    {
        glPushMatrix();
            glTranslatef(i,-313,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=635; i>=585; i-=10)
    {
        glPushMatrix();
            glTranslatef(i,-313,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=565; i>=515; i-=10)
    {
        glPushMatrix();
            glTranslatef(i,-313,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=495; i>=445; i-=10)
    {
        glPushMatrix();
            glTranslatef(i,-313,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }
    for(int i=425; i>=375; i-=10)
    {
        glPushMatrix();
            glTranslatef(i,-313,15);
            glScalef(0.3,0.3,5);
            glutSolidCube(10);
        glPopMatrix();
    }

    // horizontalni stub (desna strana)
    glPushMatrix();
        glTranslatef(605,-313,15);
        glScalef(50,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();
}

void crtajZuta_kola()
{
    // zuti deo
    glColor3f(0.886, 0.804, 0.204);

    glPushMatrix();
        glTranslatef(-240,-280,15);
        glScalef(5,3,2.5);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-230,-280,7);
        glScalef(4,3,1);
        glutSolidCube(10);
    glPopMatrix();

    // crni prozori spreda
    glColor3f(0, 0, 0);

    glPushMatrix();
        glTranslatef(-253,-295,20);
        glScalef(1.5,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-230,-295,20);
        glScalef(1.5,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    // crni prozori pozadi

    glPushMatrix();
        glTranslatef(-253,-265,20);
        glScalef(1.5,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-230,-265,20);
        glScalef(1.5,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    // točkovi sa prednje strane
    glPushMatrix();
        glTranslatef(-253,-295,4);
        glutSolidSphere(4.5,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-220,-295,4);
        glutSolidSphere(4.5,10,10);
    glPopMatrix();

    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-253,-298,4);
        glutSolidSphere(2.5,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-220,-298,4);
        glutSolidSphere(2.5,10,10);
    glPopMatrix();

    // točkovi pozadi

    glColor3f(0,0,0);

    glPushMatrix();
        glTranslatef(-253,-265,4);
        glutSolidSphere(4.5,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-220,-265,4);
        glutSolidSphere(4.5,10,10);
    glPopMatrix();

    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-253,-262,4);
        glutSolidSphere(2.5,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-220,-262,4);
        glutSolidSphere(2.5,10,10);
    glPopMatrix();

    // prozor spreda
    glColor3f(0,0,0);

    glPushMatrix();
        glTranslatef(-229,-280,17);
        glScalef(3,2,1);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-226,-280,17);
        glScalef(2.5,1.5,0.5);
        glutSolidCube(10);
    glPopMatrix();

    // branik
    glColor3f(0.341, 0.749, 0.2);

    glPushMatrix();
        glTranslatef(-210,-280,7);
        glScalef(0.1,3,1);
        glutSolidCube(10);
    glPopMatrix();

    // prednja svetla
    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-209,-288,7);
        glScalef(0.1,1,1);
        glutSolidSphere(3,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-209,-273,7);
        glScalef(0.1,1,1);
        glutSolidSphere(3,10,10);
    glPopMatrix();
}

void crtajCrvena_kola()
{
    // crveni deo
    glColor3f(0.749, 0, 0);

    glPushMatrix();
        glTranslatef(-240,-280,15);
        glScalef(5,3,2.5);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-230,-280,7);
        glScalef(4,3,1);
        glutSolidCube(10);
    glPopMatrix();

    // crni prozori spreda
    glColor3f(0, 0, 0);

    glPushMatrix();
        glTranslatef(-253,-295,20);
        glScalef(1.5,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-230,-295,20);
        glScalef(1.5,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    // crni prozori pozadi

    glPushMatrix();
        glTranslatef(-253,-265,20);
        glScalef(1.5,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-230,-265,20);
        glScalef(1.5,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    // točkovi sa prednje strane
    glPushMatrix();
        glTranslatef(-253,-295,4);
        glutSolidSphere(4.5,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-220,-295,4);
        glutSolidSphere(4.5,10,10);
    glPopMatrix();

    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-253,-298,4);
        glutSolidSphere(2.5,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-220,-298,4);
        glutSolidSphere(2.5,10,10);
    glPopMatrix();

    // točkovi pozadi

    glColor3f(0,0,0);

    glPushMatrix();
        glTranslatef(-253,-265,4);
        glutSolidSphere(4.5,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-220,-265,4);
        glutSolidSphere(4.5,10,10);
    glPopMatrix();

    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-253,-262,4);
        glutSolidSphere(2.5,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-220,-262,4);
        glutSolidSphere(2.5,10,10);
    glPopMatrix();

    // prozor spreda
    glColor3f(0,0,0);

    glPushMatrix();
        glTranslatef(-229,-280,17);
        glScalef(3,2,1);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-226,-280,17);
        glScalef(2.5,1.5,0.5);
        glutSolidCube(10);
    glPopMatrix();

    // branik
    glColor3f(0.341, 0.749, 0.2);

    glPushMatrix();
        glTranslatef(-210,-280,7);
        glScalef(0.1,3,1);
        glutSolidCube(10);
    glPopMatrix();

    // prednja svetla
    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-209,-288,7);
        glScalef(0.1,1,1);
        glutSolidSphere(3,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-209,-273,7);
        glScalef(0.1,1,1);
        glutSolidSphere(3,10,10);
    glPopMatrix();
}

void crtajPlava_kola()
{
    // plavi deo
    glColor3f(0, 0.384, 0.749);

    glPushMatrix();
        glTranslatef(-240,-280,15);
        glScalef(5,3,2.5);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-230,-280,7);
        glScalef(4,3,1);
        glutSolidCube(10);
    glPopMatrix();

    // crni prozori spreda
    glColor3f(0, 0, 0);

    glPushMatrix();
        glTranslatef(-253,-295,20);
        glScalef(1.5,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-230,-295,20);
        glScalef(1.5,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    // crni prozori pozadi

    glPushMatrix();
        glTranslatef(-253,-265,20);
        glScalef(1.5,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-230,-265,20);
        glScalef(1.5,0.1,0.8);
        glutSolidCube(10);
    glPopMatrix();

    // točkovi sa prednje strane
    glPushMatrix();
        glTranslatef(-253,-295,4);
        glutSolidSphere(4.5,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-220,-295,4);
        glutSolidSphere(4.5,10,10);
    glPopMatrix();

    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-253,-298,4);
        glutSolidSphere(2.5,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-220,-298,4);
        glutSolidSphere(2.5,10,10);
    glPopMatrix();

    // točkovi pozadi

    glColor3f(0,0,0);

    glPushMatrix();
        glTranslatef(-253,-265,4);
        glutSolidSphere(4.5,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-220,-265,4);
        glutSolidSphere(4.5,10,10);
    glPopMatrix();

    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-253,-262,4);
        glutSolidSphere(2.5,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-220,-262,4);
        glutSolidSphere(2.5,10,10);
    glPopMatrix();

    // prozor spreda
    glColor3f(0,0,0);

    glPushMatrix();
        glTranslatef(-229,-280,17);
        glScalef(3,2,1);
        glutSolidCube(10);
    glPopMatrix();

    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-226,-280,17);
        glScalef(2.5,1.5,0.5);
        glutSolidCube(10);
    glPopMatrix();

    // branik
    glColor3f(0.341, 0.749, 0.2);

    glPushMatrix();
        glTranslatef(-210,-280,7);
        glScalef(0.1,3,1);
        glutSolidCube(10);
    glPopMatrix();

    // prednja svetla
    glColor3f(1,1,1);

    glPushMatrix();
        glTranslatef(-209,-288,7);
        glScalef(0.1,1,1);
        glutSolidSphere(3,10,10);
    glPopMatrix();

    glPushMatrix();
        glTranslatef(-209,-273,7);
        glScalef(0.1,1,1);
        glutSolidSphere(3,10,10);
    glPopMatrix();
}

// Osvetljenje
void lights()
{
    glEnable(GL_LIGHTING);
    glEnable(GL_NORMALIZE);
    glEnable(GL_COLOR_MATERIAL);
    glDisable(GL_LIGHT0);
    glEnable(GL_LIGHTING);

    GLfloat lmodel_ambient[] = { 0.0, 0.0, 0.0, 1.0 };
    GLfloat light1_diffuse[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light1_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat light_positionSunce[] = { -15.0, -15.0, 15.0, 0.0 };
    GLfloat light_position1[] = { -7, -8.7, 3.2, 0.0 };//-7, -8.7, 4.2
    GLfloat light_position2[] = { -7, 0.1, 3.2, 0.0 };//-7, 0.1, 4.2
    GLfloat light_position3[] = { 0.5, 8, 3.2, 0.0 };//0.5, 8, 4.2

    glLightfv(GL_LIGHT0,GL_AMBIENT,lmodel_ambient);
    glLightfv(GL_LIGHT0,GL_DIFFUSE,light1_diffuse);
    glLightfv(GL_LIGHT0,GL_SPECULAR,light1_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_positionSunce);

    glLightfv(GL_LIGHT1,GL_AMBIENT,lmodel_ambient);
    glLightfv(GL_LIGHT1,GL_DIFFUSE,light1_diffuse);
    glLightfv(GL_LIGHT1,GL_SPECULAR,light1_specular);
    glLightfv(GL_LIGHT1, GL_POSITION, light_position1);

    glLightfv(GL_LIGHT2,GL_AMBIENT,lmodel_ambient);
    glLightfv(GL_LIGHT2,GL_DIFFUSE,light1_diffuse);
    glLightfv(GL_LIGHT2,GL_SPECULAR,light1_specular);
    glLightfv(GL_LIGHT2, GL_POSITION, light_position2);

    glLightfv(GL_LIGHT3,GL_AMBIENT,lmodel_ambient);
    glLightfv(GL_LIGHT3,GL_DIFFUSE,light1_diffuse);
    glLightfv(GL_LIGHT3,GL_SPECULAR,light1_specular);
    glLightfv(GL_LIGHT3, GL_POSITION, light_position3);

    GLfloat mat_amb_diff[] = { 0.7, 0.7, 0.7, 1.0 };
    GLfloat mat_diffuse[] = { 0.8, 0.8, 0.8, 1.0 };
    GLfloat mat_specular[] = { 1.0, 1.0, 1.0, 1.0 };
    GLfloat low_shininess[] = { 10.0 };

    glMaterialfv(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE, mat_amb_diff);

    glMaterialfv(GL_FRONT_AND_BACK, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT_AND_BACK, GL_SHININESS, low_shininess);

    glMatrixMode(GL_MODELVIEW);
}

// Obrada dogadjaja (unos sa tastature)
void lightoff(unsigned char key, int x, int y) {

//    key = tolower(key);
    if (key == 'a') {
        glDisable(GL_LIGHT0);
    }
    if (key == 's') {
        glEnable(GL_LIGHT0);
    }

    if (key == 'o') {
        glDisable(GL_LIGHT1);
    }
    if (key == 'p') {
        glEnable(GL_LIGHT1);
    }

    if (key == 'n') {
        glDisable(GL_LIGHT2);
    }
    if (key == 'm') {
        glEnable(GL_LIGHT2);
    }

    glutPostRedisplay();
}

void renderScene(void)
{
	int i, j;

	// Clear color and depth buffers
	glClearColor(0.0, 0.7, 1.0, 0.4); // sky color is light blue
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Reset transformations
	glLoadIdentity();

	// Set the camera centered at (x,y,1) and looking along directional
	// vector (lx, ly, 0), with the z-axis pointing up
	gluLookAt(
            x,      y,      z,
			x + lx, y + ly, z,
			0.0,    0.0,    1.0);

	// Draw ground - 5000x5000 square colored green
	glColor3f(0.0, 0.6, 0.0);
	glBegin(GL_QUADS);
		glVertex3f(-2500.0, -2500.0, 0.0);
		glVertex3f(-2500.0,  2500.0, 0.0);
		glVertex3f( 2500.0,  2500.0, 0.0);
		glVertex3f( 2500.0, -2500.0, 0.0);
	glEnd();

   //********************************************************

   crtajPod();
   crtajZgradu_1();
   crtajZgradu_2();
   crtajZgradu_3();
   crtajBandere();
   crtajDrvece();
   crtajOgradu();
   crtajZuta_kola();
   crtajSkolu();
   crtajBolnicu();
   crtajSuperMarket();

   crtajSto_za_stoni_tenis();
   glPushMatrix();
        glTranslatef(0,-200,0);
        crtajSto_za_stoni_tenis();
   glPopMatrix();

   glPushMatrix();
        glTranslatef(495,-200,0);
        glRotatef(-90,0,0,1);
        crtajCrvena_kola();
   glPopMatrix();

   glPushMatrix();
        glTranslatef(5,-300,0);
        glRotatef(-270,0,0,1);
        crtajPlava_kola();
   glPopMatrix();

   // Texture
   trava();
   beton();

    glutSwapBuffers(); // Make it all visible
}

void processNormalKeys(unsigned char key, int xx, int yy)
{
	if (key == ESC || key == 'q' || key == 'Q') exit(0);
}

void pressSpecialKey(int key, int xx, int yy)
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 8.0; break;
		case GLUT_KEY_DOWN : deltaMove = -8.0; break;
	}
}

void releaseSpecialKey(int key, int x, int y)
{
	switch (key) {
		case GLUT_KEY_UP : deltaMove = 0.0; break;
		case GLUT_KEY_DOWN : deltaMove = 0.0; break;
	}
}

void mouseMove(int x, int y)
{
	if (isDragging) { // only when dragging
		// update the change in angle
		deltaAngle = (x - xDragStart) * 0.005;

		// camera's direction is set to angle + deltaAngle
		lx = -sin(angle + deltaAngle);
		ly = cos(angle + deltaAngle);
	}
}

void mouseButton(int button, int state, int x, int y)
{
	if (button == GLUT_LEFT_BUTTON) {
		if (state == GLUT_DOWN) { // left mouse button pressed
			isDragging = 1; // start dragging
			xDragStart = x; // save x where button first pressed
		}
		else  { /* (state = GLUT_UP) */
			angle += deltaAngle; // update camera turning angle
			isDragging = 0; // no longer dragging
		}
	}
}

//----------------------------------------------------------------------
// Main program  - standard GLUT initializations and callbacks
//----------------------------------------------------------------------

// Meni za osvetljenje
void menu(int b)
{
     if(b==1)
     {
        glEnable(GL_LIGHT0);
     }
     if(b==2)
     {
        glEnable(GL_LIGHT1);
     }
     if(b==3)
     {
        glEnable(GL_LIGHT2);
     }

     glutPostRedisplay();
}

void kreirajMeni()
{
     glutCreateMenu(menu);
     glutAddMenuEntry("Svetlo br. 1", 1);
     glutAddMenuEntry("Svetlo br. 2", 2);
     glutAddMenuEntry("Svetlo br. 3", 3);
     glutAttachMenu(GLUT_RIGHT_BUTTON);
}
int main(int argc, char **argv)
{
	printf("\n\
-----------------------------------------------------------------------\n\
  OpenGL Sample Program:\n\
  - Drag mouse left-right to rotate camera\n\
  - Hold up-arrow/down-arrow to move camera forward/backward\n\
  - q or ESC to quit\n\
-----------------------------------------------------------------------\n");

	// general initializations
	glutInit(&argc, argv);
	glutInitDisplayMode(GLUT_DEPTH | GLUT_DOUBLE | GLUT_RGBA);
	glutInitWindowPosition(100, 100);
	glutInitWindowSize(1000, 500);
	glutCreateWindow("3D Mini City - projekat RG | Alen Dolicanin");

	//Osvetljenje
	//lights();

	// Meni za osvetljenje
	kreirajMeni();

	// register callbacks
	glutReshapeFunc(changeSize); // window reshape callback
	glutDisplayFunc(renderScene); // (re)display callback
	glutIdleFunc(update); // incremental update
	glutIgnoreKeyRepeat(1); // ignore key repeat when holding key down
	glutMouseFunc(mouseButton); // process mouse button push/release
	glutMotionFunc(mouseMove); // process mouse dragging motion
	//glutKeyboardFunc(processNormalKeys); // process standard key clicks
	glutSpecialFunc(pressSpecialKey); // process special key pressed
						// Warning: Nonstandard function! Delete if desired.
	glutSpecialUpFunc(releaseSpecialKey); // process special key release

	// Obrada dogadjaja (unos sa tastature)
	glutKeyboardFunc(lightoff);

	// Pozivanje texture
	texture1=LoadTexture("trava.bmp", 768, 360);
	texture2=LoadTexture("beton.bmp", 315, 315);

	// OpenGL init
	glEnable(GL_DEPTH_TEST);

	// enter GLUT event processing cycle
	glutMainLoop();

	return 0; // this is just to keep the compiler happy
}
