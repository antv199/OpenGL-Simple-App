#include <GL/freeglut.h>
#include <math.h>
#include <stdio.h>

// Global variables
int currentShape = 4; // Default shape: Cube
float rotationAngle = 0.0f;
float scale = 1.0f;
float translationX = 0.0f, translationY = 0.0f;
int isRotating = 0;                  // Rotation state
float color[3] = {0.0f, 1.0f, 1.0f}; // Default color: Cyan

float *getColorFunc(int index)
{
    static float outColor[3];
    switch (index)
    {
    case 1: // Cyan
        outColor[0] = 0.0f;
        outColor[1] = 1.0f;
        outColor[2] = 1.0f;
        break;
    case 2: // Red
        outColor[0] = 1.0f;
        outColor[1] = 0.0f;
        outColor[2] = 0.0f;
        break;
    case 3: // Green
        outColor[0] = 0.0f;
        outColor[1] = 1.0f;
        outColor[2] = 0.0f;
        break;
    case 4: // Orange
        outColor[0] = 1.0f;
        outColor[1] = 0.5f;
        outColor[2] = 0.0f;
        break;
    case 5: // Iridescent
        outColor[0] = (float)rand() / RAND_MAX;
        outColor[1] = (float)rand() / RAND_MAX;
        outColor[2] = (float)rand() / RAND_MAX;
        break;
    default: // White
        outColor[0] = 1.0f;
        outColor[1] = 1.0f;
        outColor[2] = 1.0f;
        break;
    }
    return outColor;
}

// Συναρτήσεις σχεδίασης σχημάτων
// -----------------------------------------------------
void drawCube()
{
    glColor3f(color[0], color[1], color[2]);
    glutWireCube(1.0);
}

void drawSphere()
{
    glColor3f(color[0], color[1], color[2]);
    glutWireSphere(0.5, 20, 20);
}

void drawPyramid()
{
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLES);
    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);

    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.0, -0.5, 0.5);

    glVertex3f(0.0, 0.5, 0.0);
    glVertex3f(0.0, -0.5, 0.5);
    glVertex3f(-0.5, -0.5, -0.5);

    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.0, -0.5, 0.5);
    glEnd();
}

void drawRectangularPrism()
{
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_QUADS);
    glVertex3f(-0.5, -0.5, -0.5);
    glVertex3f(0.5, -0.5, -0.5);
    glVertex3f(0.5, 0.5, -0.5);
    glVertex3f(-0.5, 0.5, -0.5);
    glEnd();
}

void drawHexagon()
{
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_POLYGON);
    for (int i = 0; i < 6; i++)
    {
        float angle = 2.0f * M_PI * i / 6;
        glVertex2f(cos(angle) * 0.5, sin(angle) * 0.5);
    }
    glEnd();
}

void drawCircle()
{
    glColor3f(color[0], color[1], color[2]);
    glBegin(GL_TRIANGLE_FAN);
    glVertex2f(0.0, 0.0);
    for (int i = 0; i <= 100; i++)
    {
        float angle = 2.0f * M_PI * i / 100;
        glVertex2f(cos(angle) * 0.5, sin(angle) * 0.5);
    }
    glEnd();
}

void drawText(const char *text, float x, float y)
{
    glMatrixMode(GL_PROJECTION);
    glPushMatrix();
    glLoadIdentity();
    gluOrtho2D(0, 800, 0, 800); // Διαστάσεις παραθύρου

    glMatrixMode(GL_MODELVIEW);
    glPushMatrix();
    glLoadIdentity();

    glColor3f(1, 1, 1); // Λευκό χρώμα
    glRasterPos2f(x, y);
    for (const char *c = text; *c != '\0'; c++)
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, *c);

    glPopMatrix();
    glMatrixMode(GL_PROJECTION);
    glPopMatrix();
    glMatrixMode(GL_MODELVIEW);
}

// Γενικές συνάρτησεις GLUT
// -----------------------------------------------------
void display()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glLoadIdentity(); // Reset the modelview matrix

    // Position the camera
    gluLookAt(0.0, 0.0, 5.0,  // Camera position (x, y, z)
              0.0, 0.0, 0.0,  // Look-at point (x, y, z)
              0.0, 1.0, 0.0); // Up vector (x, y, z)

    glPushMatrix();

    glTranslatef(translationX, translationY, 0.0);
    glScalef(scale, scale, scale);
    if (isRotating)
    {
        // Αν το σχήμα είναι 2D, περιστροφή γύρω από τον άξονα Y
        if (currentShape >= 4) 
        {
            glRotatef(rotationAngle, 0.0, 1.0, 0.0);
        }
        // Αν το σχήμα είναι 3D, περιστροφή γύρω από τον άξονα Z
        else
        {
            glRotatef(rotationAngle, 0.0, 0.0, 1.0);
        }
    }

    // Ενεργοποίηση φωτισμού μόνο για 3Δ αντικείμενα
    if (currentShape == 1 || currentShape == 4 || currentShape == 5 || currentShape == 6)
    {
        glEnable(GL_LIGHTING);
    }
    else
    {
        glDisable(GL_LIGHTING);
    }

    switch (currentShape)
    {
    case 1:
        drawRectangularPrism();
        break;
    case 2:
        drawHexagon();
        break;
    case 3:
        drawCircle();
        break;
    case 4:
        drawCube();
        break;
    case 5:
        drawPyramid();
        break;
    case 6:
        drawSphere();
        break;
    }

    glDisable(GL_LIGHTING); // Απενεργοποίηση για ό,τι ακολουθεί (π.χ. κείμενο)
    glPopMatrix();

    // Draw text at the top center
    drawText("ANTONIOS VATOUSIS 2404", 0, 780);

    glutSwapBuffers();
}

void reshape(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluPerspective(45.0, (float)width / (float)height, 1.0, 100.0);
    glMatrixMode(GL_MODELVIEW);
}

void idle()
{
    if (isRotating)
    {
        rotationAngle += 1.0f;
        if (rotationAngle > 360.0f)
            rotationAngle -= 360.0f;
        glutPostRedisplay();
    }
}

void keyboard(unsigned char key, int x, int y)
{
    switch (key)
    {
    // ESC για έξοδο
    case 27:
        exit(0);
        break;

    // Αλλαγή χρώματος
    case '1':
    {
        float *c = getColorFunc(1);
        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
        break;
    }
    case '2':
    {
        float *c = getColorFunc(2);
        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
        break;
    }
    case '3':
    {
        float *c = getColorFunc(3);
        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
        break;
    }
    case '4':
    {
        float *c = getColorFunc(4);
        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
        break;
    }
    case '5':
    {
        float *c = getColorFunc(5);
        color[0] = c[0];
        color[1] = c[1];
        color[2] = c[2];
        break;
    }

    // Μεγένθυση και σμίκρυνση
    case '+':
        scale += 0.1f;
        break;
    case '-':
        scale -= 0.1f;
        break;
    case ' ':
        isRotating = !isRotating;
        if (isRotating)
            glutIdleFunc(idle);
        else
            glutIdleFunc(NULL);
        break;
    }
    glutPostRedisplay();
}

void specialKeys(int key, int x, int y)
{
    switch (key)
    {
    // 
    case GLUT_KEY_F1:
        currentShape = 1;
        break;
    case GLUT_KEY_F2:
        currentShape = 2;
        break;
    case GLUT_KEY_F3:
        currentShape = 3;
        break;
    case GLUT_KEY_F4:
        currentShape = 4;
        break;
    case GLUT_KEY_F5:
        currentShape = 5;
        break;
    case GLUT_KEY_F6:
        currentShape = 6;
        break;
    case GLUT_KEY_LEFT:
        translationX -= 0.1f;
        break;
    case GLUT_KEY_RIGHT:
        translationX += 0.1f;
        break;
    case GLUT_KEY_UP:
        translationY += 0.1f;
        break;
    case GLUT_KEY_DOWN:
        translationY -= 0.1f;
        break;
    }
    glutPostRedisplay();
}

void menuShape(int value)
{
    currentShape = value;
    glutPostRedisplay();
}

void menuColor(int value)
{
    switch (value)
    {
    case 1:
    case 2:
    case 3:
    case 4:
    case 5:
        {
            float *c = getColorFunc(value);
            color[0] = c[0];
            color[1] = c[1];
            color[2] = c[2];
            break;
        }
    }
    glutPostRedisplay();
}

// Δημιουργία μενού
void createMenus()
{
    // Μενου χρωμάτων
    int colorMenu = glutCreateMenu(menuColor);
    glutAddMenuEntry("Cyan", 1);
    glutAddMenuEntry("Red", 2);
    glutAddMenuEntry("Green", 3);
    glutAddMenuEntry("Orange", 4);
    glutAddMenuEntry("Iridescent", 5);

    // Μενού σχημάτων
    int shapeMenu = glutCreateMenu(menuShape);
    glutAddMenuEntry("Rectangular Prism", 1);
    glutAddMenuEntry("Hexagon", 2);
    glutAddMenuEntry("Circle", 3);
    glutAddMenuEntry("Cube", 4);
    glutAddMenuEntry("Pyramid", 5);
    glutAddMenuEntry("Sphere", 6);

    // Κύριο μενού
    int mainMenu = glutCreateMenu(NULL);
    glutAddSubMenu("Change Color", colorMenu);
    glutAddSubMenu("Change Shape", shapeMenu);

    // Συναψη μενού στο δεξί κλικ
    glutAttachMenu(GLUT_RIGHT_BUTTON);
}

void init()
{
    glEnable(GL_DEPTH_TEST);
    glClearColor(0.1f, 0.1f, 0.1f, 1.0f);

    // Lighting σετ
    GLfloat light_ambient[] = {0.2f, 0.2f, 0.2f, 1.0f};
    GLfloat light_diffuse[] = {0.8f, 0.8f, 0.8f, 1.0f};
    GLfloat light_specular[] = {1.0f, 1.0f, 1.0f, 1.0f};
    GLfloat light_position[] = {2.0f, 2.0f, 2.0f, 1.0f};


    glLightfv(GL_LIGHT0, GL_AMBIENT, light_ambient);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_diffuse);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_specular);
    glLightfv(GL_LIGHT0, GL_POSITION, light_position);

    glEnable(GL_LIGHT0); // Ενεργοποίηση φωτισμού
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT_AND_BACK, GL_AMBIENT_AND_DIFFUSE);
}

int main(int argc, char **argv)
{
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize(800, 800);
    glutCreateWindow("3D Scene");

    init();

    glutDisplayFunc(display);
    glutReshapeFunc(reshape); 
    glutKeyboardFunc(keyboard); // Αλλαγή χρώματος και μεγέθους
    glutSpecialFunc(specialKeys); // Χειρισμός ειδικών πλήκτρων για τα σχήματα και μετακίνηση
    createMenus(); // Το μενού

    glutMainLoop();

    return 0;
}