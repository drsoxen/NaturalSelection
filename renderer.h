#pragma once
#include <vector>
#include <iostream>
#include "Creature.h"
#include "rendererGeometry.h"

using namespace std;

void render(Vector2 mapDimensions, int index, int generation, vector<Creature> &creatures) {

    Vector3 clearColour = Vector3(0,0,0);
	std::vector<Vec3f> framebuffer(mapDimensions.x*mapDimensions.y,Vec3f(clearColour.x,clearColour.y,clearColour.z));


    int size = mapDimensions.x/15;
    for(int x = 0; x <= mapDimensions.x; x++)
    {
        for(int y = 0; y <= mapDimensions.y; y++)
        {
            if(Vector2(x,y).pythagoreanDistance(Vector2(mapDimensions.x/2, mapDimensions.y/2)) < size+1 && Vector2(x,y).pythagoreanDistance(Vector2(mapDimensions.x/2, mapDimensions.y/2)) > size-1)
            {
                framebuffer[x+y*mapDimensions.x] = Vec3f(0,255,0);
            }
        }
    }

	for(int i = 0; i < creatures.size(); i++)
	{
		framebuffer[(int)creatures[i].m_position.x+(int)creatures[i].m_position.y*mapDimensions.x] = Vec3f(creatures[i].m_colour.x,creatures[i].m_colour.y,creatures[i].m_colour.z);
	}

    // int size = mapDimensions.x/10;
    // Vector2 startPoint = Vector2((mapDimensions.x/2)-(size/2), (mapDimensions.y/2)-(size/2));

    // for(int x = startPoint.x; x <= startPoint.x + size; x++)
    // {
    //     for(int y = startPoint.y; y <= startPoint.y + size; y++)
    //     {
    //         if((x == startPoint.x || x == startPoint.x + size || y == startPoint.y || y == startPoint.y + size))
    //         {
    //             framebuffer[x+y*mapDimensions.x] = Vec3f(0,255,0);
    //         }
    //     }
    // }



    std::ofstream ofs;
    string path = "output/out";
    if(index < 10)
    {
    	path.append("0");
    }
    if(index < 100)
    {
    	path.append("0");
    }
    if(index < 1000)
    {
        path.append("0");
    }
    if(index < 10000)
    {
        path.append("0");
    }
    path.append(to_string(index));
    path.append(".ppm");
    ofs.open(path);
    ofs << "P6\n" << mapDimensions.x << " " << mapDimensions.y << "\n255\n";
    for (size_t i = 0; i < mapDimensions.y*mapDimensions.x; ++i) {
        Vec3f &c = framebuffer[i];
        float max = std::max(c[0], std::max(c[1], c[2]));
        if (max>1) c = c*(1./max);
        for (size_t j = 0; j<3; j++) {
            ofs << (char)(255 * std::max(0.f, std::min(1.f, framebuffer[i][j])));
        }
    }
    ofs.close();
}