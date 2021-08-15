#include <GLFW\glfw3.h>
#include "linmath.h"
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
using namespace std;


struct vec2d {
	float x, y;
};

struct vec3d {
	float x, y, z;
};


vec3d Rotate(vec3d Point, vec3d Origin, vec3d rotation) 
{
	const float DEG2RAD = 3.14159 / 180;
	vec3d moved;
	moved.x = Point.x - Origin.x;
	moved.y = Point.y - Origin.y;
	moved.z = Point.z - Origin.z;

	vec3d rot;
	rot.x = rotation.x * DEG2RAD;
	rot.y = rotation.y * DEG2RAD;
	rot.z = rotation.z * DEG2RAD;

	

	float x1 = moved.x * cos(rot.x) - moved.y * sin(rot.x);
	float y1 = moved.x * sin(rot.x) + moved.y * cos(rot.x);
	float z1 = moved.z;

	float x2 = x1 * cos(rot.y) - z1 * sin(rot.y);
	float z2 = x1 * sin(rot.y) + z1 * cos(rot.y);
	float y2 = y1;

	float y3 = y2 * cos(rot.z) - z2 * sin(rot.z);
	float z3 = y2 * sin(rot.z) + z2 * cos(rot.z);
	float x3 = x2;

	vec3d temp = { x3 + Origin.x, y3 + Origin.y, z3 + Origin.z};

	return temp;
}





vec2d Convert(float x, float y, vec2d resolution)
{
	vec2d output;
	output.x = (x - (resolution.x / 2)) / (resolution.x / 2);
	output.y = (y - (resolution.y / 2)) / (resolution.y / 2);
	return output;
}

vec3d Convert(float x, float y, float z, vec3d resolution)
{
	vec3d output;
	output.x = (x - (resolution.x / 2)) / (resolution.x / 2);
	output.y = (y - (resolution.y / 2)) / (resolution.y / 2);
	output.z = (z - (resolution.z / 2)) / (resolution.z / 2);
	return output;
}

int main(void)
{
	if (!glfwInit())
	{
		exit(EXIT_FAILURE);
	}
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 2);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 0);

	vec3d res;
	res.x = 1000;
	res.y = 1000;
	res.z = 1000;

	vector<vector<vec3d>> objectstorender;
	objectstorender.clear();
	//objectstorender.push_back({ {-50,-50,0}, {0,50,50}, {50,-50,0} });

	//objectstorender.push_back({ {-50,-50,0}, {0,50,0}, {50,50,0} });


	//objectstorender.push_back({ {-40,-50,50}, {10,50,0}, {60,-50,50} });
	
    objectstorender.push_back({ {-10,0,-10 }, {-10,10,10}, {10,0,10}, {10,0,-10} });

	objectstorender.push_back({ {30,0,-10 }, {30,0,10}, {70,0,10}, {70,0,-10} });

	GLFWwindow* window = glfwCreateWindow(res.x, res.y, "OpenGL Example", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		exit(555);
	}
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);

	const float DEG2RAD = 3.14159 / 180;
	float radius = 50;
	float radius2 = 40;
	float r = 0.0;
	float g = 0.3;
	float b = 0.6;
	float r2 = 0.0;
	float g2 = 0.3;
	float b2 = 0.6;


	vec3d cam_pos = {0,0,0};//{ res.x / 2,  res.y / 2,  res.z / 2, };
	vec3d cam_rot = {0,0,90};

	bool ballLeft = true;
	bool ballDown = true;
	glEnable(GL_DEPTH_TEST);
	glDepthMask(GL_TRUE);
	glDepthFunc(GL_LEQUAL);
	glDepthRange(-1.0f, 1.0f);
	while (!glfwWindowShouldClose(window))
	{
		float ratio;
		int width, height;
		glfwGetFramebufferSize(window, &width, &height);
		ratio = width / (float)height;
		glViewport(0, 0, width, height);
		glClear(GL_COLOR_BUFFER_BIT);
			
		glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
		glClearDepth(1.0f);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		float mov_speed = 0.2;

		if (glfwGetKey(window, GLFW_KEY_UP))
		{
			cam_pos.y += mov_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_DOWN))
		{
			cam_pos.y -= mov_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_RIGHT))
		{
			cam_pos.x += mov_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_LEFT))
		{
			cam_pos.x -= mov_speed;
		}

		if (glfwGetKey(window, GLFW_KEY_W))
		{
			cam_pos.z += mov_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_S))
		{
			cam_pos.z -= mov_speed;
		}

		cam_rot.x = fmod(cam_rot.x, 360);
		cam_rot.y = fmod(cam_rot.y, 360);
		cam_rot.z = fmod(cam_rot.z, 360);

		float rot_speed = 0.2;

		if (glfwGetKey(window, GLFW_KEY_1))
		{
			cam_rot.x += rot_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_2))
		{
			cam_rot.x -= rot_speed;
		}

		if (glfwGetKey(window, GLFW_KEY_3))
		{
			cam_rot.y += rot_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_4))
		{
			cam_rot.y -= rot_speed;
		}

		if (glfwGetKey(window, GLFW_KEY_5))
		{
			cam_rot.z += rot_speed;
		}
		if (glfwGetKey(window, GLFW_KEY_6))
		{
			cam_rot.z -= rot_speed;
		}


		//r = fmod(r + 0.01, 1);
		//g = fmod(g + 0.03, 1);
		//b = fmod(b + 0.02, 1);

		r2 = r;
		g2 = g;
		b2 = b;

		for (int i = 0; i < objectstorender.size(); i++)
		{
			r2 = fmod(r2 + 0.4, 1);
			g2 = fmod(g2 + 0.7, 1);
			b2 = fmod(b2 + 0.5, 1);
			glColor3f(r2, g2, b2);
			glBegin(GL_POLYGON);
			for (int i2 = 0; i2 < objectstorender[i].size(); i2++)
			{
				vec3d temp = Convert(objectstorender[i][i2].x + cam_pos.x + (res.x / 2), objectstorender[i][i2].y + cam_pos.y + (res.y / 2), objectstorender[i][i2].z + cam_pos.z + (res.z / 2), res);
				temp = Rotate(temp, cam_pos, cam_rot);
				//printf("\ntest %i %f %f %f", i2, temp.x, temp.y, temp.z);
				glVertex3f(temp.x, temp.y, temp.z);
			}
			glEnd();
			/*cout << "test ";
			cout << objectstorender[i][0].x + x;
			cout << " - ";
			cout << objectstorender[i][0].y + y;
			cout << " - ";
			cout << objectstorender[i][0].z + z;
			cout << "\n";*/
		}

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	glfwDestroyWindow(window);
	glfwTerminate;
	exit(EXIT_SUCCESS);
}