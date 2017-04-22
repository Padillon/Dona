/*
	Copyright 2015 Ludwin Hernández
    This program is free software: you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation, either version 3 of the License, or
    (at your option) any later version.
    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.
    You should have received a copy of the GNU General Public License
    along with this program.  If not, see <http://www.gnu.org/licenses/>.
    Crear cubo.
*/

#include <stdio.h>
#include <GL/gl.h>
#include <GL/glut.h>

//Definimos variables
double rotate_y=0;
double rotate_x=0;
double rotate_z=0;

GLfloat X = 0.0f;
GLfloat Y = 0.0f;
GLfloat Z = 0.0f;
GLfloat scale = 1.0f;
GLfloat light_position[] = { 0.0, -0.3, -0.3, 0.0 };

int id_menu[2]; // vector donde almacenaremos el id de la imagen a imprimir

void piramide(float a, float b, float c, float d, float e, float f, float g, float h, float i, float j){
    // Propiedades del material
        GLfloat mat_ambient[] = { a, b,c,1.0f };
        GLfloat mat_diffuse[] = { d, e, f, 1.0f };
        GLfloat mat_specular[] = {g, h, i, 1.0f };
        GLfloat shine[] = {j};

    // "Limpiamos" el frame buffer con el color de "Clear", en este
    // caso negro.
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glMatrixMode( GL_MODELVIEW_MATRIX );// Resetear transformaciones

    glLoadIdentity();

    //setMaterial
     glMaterialfv(GL_FRONT, GL_AMBIENT, mat_ambient);
     glMaterialfv(GL_FRONT, GL_DIFFUSE, mat_diffuse);
     glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
     glMaterialfv(GL_FRONT, GL_SHININESS, shine);

    // Rotar en el eje X,Y y Z
    glRotatef( rotate_x, 1.0, 0.0, 0.0 );
    glRotatef( rotate_y, 0.0, 1.0, 0.0 );
    glRotatef( rotate_z, 0.0, 0.0, 1.0 );
    glTranslatef(X, Y, Z); 	// Transladar en los 3 ejes
    // Otras transformaciones
    glScalef(scale, scale, scale);

    //color blanco para reflejar la luz
    glColor3f(1.0f,1.0f,1.0f);

    // BASE
    glBegin(GL_POLYGON);
    glNormal3f(0.5, -0.5, -0.5 );
    glVertex3f(0.5, -0.5, -0.5 );
    glNormal3f(0.5, -0.5,  0.5 );
    glVertex3f(0.5, -0.5,  0.5 );
    glNormal3f(-0.5, -0.5,  0.5 );
    glVertex3f(-0.5, -0.5,  0.5 );
    glNormal3f(-0.5, -0.5, -0.5 );
    glVertex3f(-0.5, -0.5, -0.5 );
    glEnd();

    //CARAS LATERALES
    glBegin(GL_TRIANGLES);
    glNormal3f(0.5, -0.5, -0.5 );
    glVertex3f(0.5, -0.5, -0.5 );
    glNormal3f(0.0, 0.0,  0.0 );
    glVertex3f(0.0, 0.0,  0.0 );
    glNormal3f(-0.5, -0.5,  -0.5 );
    glVertex3f(-0.5, -0.5,  -0.5 );
    glEnd();

    //CARA DERECHA:
    glBegin(GL_TRIANGLES);
    glNormal3f(0.5, -0.5, 0.5 );
    glVertex3f(0.5, -0.5, 0.5 );
    glNormal3f(0.0, 0.0,  0.0 );
    glVertex3f(0.0, 0.0,  0.0 );
    glNormal3f(-0.5,-0.5, 0.5 );
    glVertex3f(-0.5,-0.5, 0.5 );
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(-0.5, -0.5, 0.5 );
    glVertex3f(-0.5, -0.5, 0.5 );
    glNormal3f(0.0, 0.0,  0.0 );
    glVertex3f(0.0, 0.0,  0.0 );
    glNormal3f(-0.5,-0.5, -0.5 );
    glVertex3f(-0.5,-0.5, -0.5 );
    glEnd();

    glBegin(GL_TRIANGLES);
    glNormal3f(0.5, -0.5, -0.5 );
    glVertex3f(0.5, -0.5, -0.5 );
    glNormal3f(0.0, 0.0,  0.0 );
    glVertex3f(0.0, 0.0,  0.0 );
    glNormal3f(0.5,-0.5, 0.5 );
    glVertex3f(0.5,-0.5, 0.5 );
    glEnd();

    glFlush();
    glutSwapBuffers();

}

void init (void){
    glClearColor (0.0, 0.0, 0.0, 0.0);
    glShadeModel(GL_SMOOTH);
    glLightfv(GL_LIGHT0,GL_POSITION,light_position);
    // Activamos la fuente de luz
    glEnable(GL_LIGHTING);
    glEnable(GL_LIGHT0); //Activamos las luces en 0
    glDepthFunc(GL_LESS); //comparación de profundidad
    glEnable(GL_DEPTH_TEST); //activa GL_DEPTH_TEST
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}

void reshape(int w, int h){
    glViewport(0, 0, (GLsizei) w, (GLsizei) h);
    // Activamos la matriz de proyeccion.
    glMatrixMode(GL_PROJECTION);
    // "limpiamos" esta con la matriz identidad.
    glLoadIdentity();
    // Usamos proyeccion ortogonal
    glOrtho(-1.0, 1.0, -1.0, 1.0, -1.0, -1.0);
    // Activamos la matriz de modelado/visionado.
    glMatrixMode(GL_MODELVIEW);
    // "Limpiamos" la matriz
    glLoadIdentity();
}

// Función para controlar teclas especiales
void specialKeys( int key, int x, int y ){

    //  Flecha derecha: aumentar rotación 7 grados
    if (key == GLUT_KEY_RIGHT)
        rotate_y += 7;

    //  Flecha izquierda: rotación en eje Y negativo 7 grados
    else if (key == GLUT_KEY_LEFT)
        rotate_y -= 7;
    //  Flecha arriba: rotación en eje X positivo 7 grados
    else if (key == GLUT_KEY_UP)
        rotate_x += 7;
    //  Flecha abajo: rotación en eje X negativo 7 grados
    else if (key == GLUT_KEY_DOWN)
        rotate_x -= 7;
    //  Tecla especial F2 : rotación en eje Z positivo 7 grados
    else if (key == GLUT_KEY_F1)
        rotate_z += 7;
    //  Tecla especial F2 : rotación en eje Z negativo 7 grados
    else if (key == GLUT_KEY_F2)
        rotate_z -= 7;
    else if (key == GLUT_KEY_F3)
            scale+= 0.5f;
    else if (key == GLUT_KEY_F4)
            scale-= 0.5f;



    //  Solicitar actualización de visualización
    glutPostRedisplay();

}

// Función para controlar teclas normales del teclado.
void keyboard(unsigned char key, int x, int y){
    //control de teclas que hacen referencia a Escalar y transladar el cubo en los ejes X,Y,Z.
    id_menu[1]=key; // En el vector VF, en su campo 1, se almacenara el id de la imagen
    switch (key)
    {
    case '1':
        piramide(0.135,0.2225,0.1575,0.54,0.89,0.63,0.316228,0.316228,0.316228,0.1);
        break;
    case '2':
        piramide(0.05375, 0.05, 0.06625, 0.18275, 0.17, 0.22525, 0.532741, 0.528634, 0.546435, 56.3);
        break;
    case '3':
        piramide(0.329412,0.223529,0.027451,0.780392,0.568627,0.113725,0.992157,0.941176,0.807843,0.21794872);
        break;
    case '4':
        piramide(0.0, 0.1, 0.06, 0.0, 0.50980392, 0.50980392, 0.50196078, 0.50196078, 0.50196078, 57.25);
        break;
    case '5':
        piramide(0.05,0.0,0.0,0.5,0.4,0.4,0.7,0.04,0.04,0.078125);
        break;
    case 'x' :
        X += 0.1f;
        break;
    case 'X' :
        X -= 0.1f;
        break;
    case 'y' :
        Y += 0.1f;
        break;
    case 'Y' :
        Y -= 0.1f;
        break;
    case 'z':
        Z -= 0.1f;
        break;
    case 'Z':
        Z += 0.1f;
        break;
    case 'q':
        exit(0);			// exit
    }
    glutPostRedisplay();
}


// METODO QUE RE DIBUJA LA PANTALLA
void redraw( void ){
    //Limpiando la pantalla
    glClear(GL_COLOR_BUFFER_BIT);
    // Haciendo uso del metodo menu, pasandoles como paramentro el id
    keyboard(id_menu[1],X,Y);
	glutSwapBuffers();
}

int main(int argc, char* argv[])
{

    //  Inicializar los parámetros GLUT y de usuario proceso
    glutInit(&argc,argv);

    // Solicitar ventana con color real y doble buffer con Z-buffer
    glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH);
    glutInitWindowSize (800, 600);
    glutInitWindowPosition (0, 0);
    // Crear ventana
    glutCreateWindow("PIRAMIDE");

    // Habilitar la prueba de profundidad de Z-buffer
    glEnable(GL_DEPTH_TEST);
  // Funciones de retrollamada
    init();
    glutDisplayFunc(redraw);
    glutKeyboardFunc(keyboard);
    glutSpecialFunc(specialKeys);
    glutReshapeFunc(reshape);
    // Pasar el control de eventos a GLUT
    glutMainLoop();
    return 0;

}
