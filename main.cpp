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
#include "Geometry.h"
#include "renderer.h"
using namespace std;

const Vector2 mapDimensions(500, 500);

const int initialPopulation = 1000;
int lifeLength = 500;

int generation = 0;
const int targetGeneration = 100;

vector<Creature> creatures;

int main()
{
	srand(time(0));

	do
	{
		generation = 0;

		for(int i = 0; i < initialPopulation; i++)
		{
			Creature creature = Creature(mapDimensions, Vector2(rand()%((int)mapDimensions.x-1)+1, rand()%((int)mapDimensions.y-1)+1), Vector3(rand()%256,rand()%256,rand()%256));
			//Creature creature = Creature(mapDimensions, Vector2(64, 64), Vector3(rand()%256,0,0));
			creature.m_brain.RandomConnections();
			creatures.emplace_back(move(creature));
		}

		auto start = chrono::steady_clock::now();
		do
		{
			cout << "Generation: " << generation << " Creatures: " << creatures.size() << endl;

			if(generation == targetGeneration)
			{
				lifeLength *= 2;
			}

			for(int i = 0; i < lifeLength; i++)//game loop
			{

				for(int j = 0; j < creatures.size(); j++)
				{
					//Input
					creatures[j].GetInputs();

					//Output
					creatures[j].Act();
				}

				if(generation == targetGeneration)
				{
					auto end = chrono::steady_clock::now();
					chrono::duration<double> elapsed_seconds = end - start;
					//cout << "elapsed time: " << elapsed_seconds.count() << "s\n";
					render(mapDimensions, i, generation, creatures);

					if(i == lifeLength-1)
					{
						LOGS("Print Net");
						creatures[0].m_brain.PrintNeuralNet();
					}
				}
			}


			vector<Creature> babies;

			//breed
			for(int i = 0; i < creatures.size(); i++)
			{


				Creature * creature = creatures[i].Mitosis();
				if(creature)
				{
					babies.emplace_back(move(*creature));
				}
				if(creatures.size() < initialPopulation)
				{
					Creature * creature2 = creatures[i].Mitosis();
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


		} while(generation-1 < targetGeneration && creatures.size() > 0);

		if(creatures.size() == 0)
		{
			LOGS("Everyone Died");
		}

	} while(generation-1 != targetGeneration);



}























