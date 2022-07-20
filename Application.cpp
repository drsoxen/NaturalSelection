#define GL_SILENCE_DEPRECATION
#include <time.h>
#include <limits>
#include <cmath>
#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <fstream>
#include <string>
#include <chrono>
#include <GLFW/glfw3.h> 

#include "Creature.h"
#include "Geometry.h"
#include "Application.h"
#include "imgui.h"

using namespace std;

const Vector2 mapDimensions(500, 500);

const int initialPopulation = 5000;

int lifeLength = 500;
int age = 0;
int targetRadius = 0;
int generation = 0;
GLuint image_texture = 0;

vector<Creature> creatures;

namespace MyApp
{
	int counter = 0;

	void Init()
	{
		srand(time(0));

	    glGenTextures(1, &image_texture);
	    glBindTexture(GL_TEXTURE_2D, image_texture);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);

		generation = 0;
		targetRadius = 5;

		for(int i = 0; i < initialPopulation; i++)
		{
			Creature creature = Creature(mapDimensions, Vector2(rand()%((int)mapDimensions.x-1)+1, rand()%((int)mapDimensions.y-1)+1), Vector3(255,255,255/*rand()%256,rand()%256,rand()%256*/));
			creature.m_brain.RandomConnections();
			creatures.emplace_back(move(creature));
		}
	}

	void Update()
	{
		for(int j = 0; j < creatures.size(); j++)
		{
			//Input
			creatures[j].GetInputs();

			//Output
			creatures[j].Act();
		}

		age++;

		if(lifeLength == age)
		{

			if(generation % 10 == 0)
			{
				targetRadius ++;
			}

			age = 0;

			vector<Creature> babies;

			//breed
			for(int i = 0; i < creatures.size(); i++)
			{
				Creature * creature = creatures[i].Mitosis(targetRadius);
				if(creature)
				{
					babies.emplace_back(move(*creature));
				}
				if(creatures.size() < initialPopulation)
				{
					Creature * creature2 = creatures[i].Mitosis(targetRadius);
					if(creature)
					{
						babies.emplace_back(move(*creature2));
					}
				}
			}

			creatures.clear();

			for(int i = 0; i < babies.size(); i++)
			{
				creatures.emplace_back(move(babies[i]));
			}

			babies.clear();

			generation++;

			if(creatures.size() == 0)
			{
				Init();
			}
		}
	}

	void Render()
	{
		Vector3 clearColour = Vector3(0,0,0);
		std::vector<Vector3> framebuffer(mapDimensions.x*mapDimensions.y,Vector3(clearColour.x,clearColour.y,clearColour.z));

		int size = mapDimensions.x/targetRadius;
	    for(int x = 0; x <= mapDimensions.x; x++)
	    {
	        for(int y = 0; y <= mapDimensions.y; y++)
	        {
	            if(Vector2(x,y).pythagoreanDistance(Vector2(mapDimensions.x/2, mapDimensions.y/2)) < size+1 && Vector2(x,y).pythagoreanDistance(Vector2(mapDimensions.x/2, mapDimensions.y/2)) > size-1)
	            {
	                framebuffer[x+y*mapDimensions.x] = Vector3(0,255,0);
	            }
	        }
	    }

		for(int i = 0; i < creatures.size(); i++)
		{
			framebuffer[(int)creatures[i].m_position.x+(int)creatures[i].m_position.y*mapDimensions.x] = Vector3(creatures[i].m_colour.x,creatures[i].m_colour.y,creatures[i].m_colour.z);
		}

		unsigned char* image_data = new unsigned char[(static_cast<int>(mapDimensions.x)*static_cast<int>(mapDimensions.y))*4];

		for(int i = 0; i < framebuffer.size(); i++)
		{
			image_data[i*4] = framebuffer[i].x;
			image_data[i*4+1] = framebuffer[i].y;
			image_data[i*4+2] = framebuffer[i].z;
			image_data[i*4+3] = 255;
		}

	    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, mapDimensions.x, mapDimensions.y, 0, GL_RGBA, GL_UNSIGNED_BYTE, image_data);

	    ImGui::Begin(" ");
		ImGui::Image((void*)(intptr_t)image_texture, ImVec2(mapDimensions.x*1.5, mapDimensions.y*1.5));
	    ImGui::Text("Generation: %d Creatures: %lu Age: %d/%d",generation, creatures.size(), age, lifeLength);
	    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
	    ImGui::End();

	    delete[] image_data;
	}
}



