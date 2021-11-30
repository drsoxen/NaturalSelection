#pragma once

#include <iostream>
#include <math.h>
#include "Genome.h"
#include "Brain.h"
#include "Geometry.h"
#include "Utils.h"

#define _USE_MATH_DEFINES

using namespace std;

class Creature
{
public:
	Vector2 m_startPosition;
	Vector2 m_position;
	Vector3 m_colour;
	Genome m_genome;
	Brain m_brain;

	Vector2 m_mapDimensions;

	double OscillatingValue = RandomRange(0,100);
	double m_speed = 2;
	double m_rotation = ((double)rand()/RAND_MAX) * 2*M_PI;

	Creature(Vector2 mapDimensions, Vector2 position, Vector3 colour);
	Creature *  Mitosis();

	void Act();
	void GetInputs();

	void MoveRandom();
	void RotateR();
	void RotateL();
	void MoveForward();

};