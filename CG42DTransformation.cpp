#include <GL/glut.h>
#include <iostream>
#include <cmath>
const int MAX_VERTICES = 10;
class Point {
public:
float x, y;
Point() : x(0.0f), y(0.0f) {}
Point(float _x, float _y) : x(_x), y(_y) {}
Point operator+(const Point& other) {
return Point(x + other.x, y + other.y);
}
Point operator-(const Point& other) {
return Point(x - other.x, y - other.y);
}
Point operator*(const float scale) {
return Point(x * scale, y * scale);
}
Point operator*(const Point& other) {
return Point(x * other.x, y * other.y);
}
Point rotate(float angle) {
float s = sin(angle);
float c = cos(angle);
float newX = x * c - y * s;
float newY = x * s + y * c;
return Point(newX, newY);
}
};
int numVertices;
Point vertices[MAX_VERTICES];
void display() {
glClear(GL_COLOR_BUFFER_BIT);
glColor3f(1.0f, 0.0f, 0.0f);
glBegin(GL_POLYGON);
for (int i = 0; i < numVertices; i++) {
glVertex2f(vertices[i].x, vertices[i].y);
}
glEnd();
glFlush();
}
void translate(const Point& translation) {
for (int i = 0; i < numVertices; i++) {
vertices[i] = vertices[i] + translation;
}
glutPostRedisplay();
}
void rotate(float angle) {
Point centroid;
for (int i = 0; i < numVertices; i++) {
centroid = centroid + vertices[i];
}
centroid = centroid * (1.0f / numVertices);
for (int i = 0; i < numVertices; i++) {
vertices[i] = centroid + (vertices[i] - centroid).rotate(angle);
}
glutPostRedisplay();
}
void scale(const Point& scaling) {
Point centroid;
for (int i = 0; i < numVertices; i++) {
centroid = centroid + vertices[i];
}
centroid = centroid * (1.0f / numVertices);
for (int i = 0; i < numVertices; i++) {
vertices[i] = centroid + (vertices[i] - centroid) * scaling;
}
glutPostRedisplay();
}
void menu(int option) {
switch (option) {
case 1:
float tx, ty;
std::cout << "Enter translation values (dx dy): ";
std::cin >> tx >> ty;
translate(Point(tx, ty));
break;
case 2:
float angle;
std::cout << "Enter rotation angle (degrees): ";
std::cin >> angle;
angle = angle * M_PI / 180.0f;
rotate(angle);
break;
case 3:
float sx, sy;
std::cout << "Enter scaling factors (sx sy): ";
std::cin >> sx >> sy;
scale(Point(sx, sy));
break;
case 4:
exit(0);
break;
}
}
int main(int argc, char** argv) {
glutInit(&argc, argv);
glutInitDisplayMode(GLUT_SINGLE | GLUT_RGB);
glutInitWindowSize(800, 600);
glutCreateWindow("2D Transformations");
std::cout << "Enter the number of vertices: ";
std::cin >> numVertices;
if (numVertices < 3 || numVertices > MAX_VERTICES) {
std::cout << "Invalid number of vertices. Exiting." << std::endl;
return 1;
}
for (int i = 0; i < numVertices; i++) {
std::cout << "Enter vertex " << i + 1 << " (x y): ";
std::cin >> vertices[i].x >> vertices[i].y;
}
glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
glutDisplayFunc(display);
glutCreateMenu(menu);
glutAddMenuEntry("Translate", 1);
glutAddMenuEntry("Rotate", 2);
glutAddMenuEntry("Scale", 3);
glutAddMenuEntry("Exit", 4);
glutAttachMenu(GLUT_RIGHT_BUTTON);
glutMainLoop();
return 0;
}
