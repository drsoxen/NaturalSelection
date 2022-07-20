#include "Creature.h"
#include <chrono>
#include "Utils.h"

Creature::Creature(Vector2 mapDimensions, Vector2 position, Vector3 colour) : m_mapDimensions(mapDimensions), m_position(position), m_colour(colour), m_startPosition(position)
{

}

Creature * Creature::Mitosis(int targetRadius)
{
	if(m_position.pythagoreanDistance(Vector2(m_mapDimensions.x/2, m_mapDimensions.y/2)) < m_mapDimensions.x/targetRadius && m_startPosition != m_position)
	{
		Creature *daughter = new Creature(m_mapDimensions, Vector2(rand()%((int)m_mapDimensions.x-1)+1, rand()%((int)m_mapDimensions.y-1)+1), m_colour);
		daughter->m_brain.InheritConnections(&m_brain);
		return daughter;
	}

	return nullptr;
}

void Creature::Act()
{
	switch(m_brain.MakeDecision()) 
	{
	  	case OutputType::RotateR:
	  		RotateR();
	    	break;
	    case OutputType::RotateL:
	  		RotateL();
	    	break;
	  	case OutputType::MoveForward:
	  		MoveForward();
	    	break;
	    default:
	    	break;
	}

	m_brain.Forget();
}

void Creature::GetInputs()
{

	m_brain.GetInputNeuronByType(InputType::CenterAngle)->m_value = Normalize(atan2(m_mapDimensions.y/2 - m_position.y, m_mapDimensions.x/2 - m_position.x), 0, 2*M_PI);

	m_brain.GetInputNeuronByType(InputType::Oscillator)->m_value = sin(OscillatingValue);

	m_brain.GetInputNeuronByType(InputType::Rotation)->m_value = Normalize(m_rotation, -1 , 1);

	m_brain.Process();

	OscillatingValue +=0.2;
}

void Creature::RotateR()
{
	m_rotation +=0.4;
	if(m_rotation > 2*M_PI) m_rotation = 0;
}

void Creature::RotateL()
{
	m_rotation -=0.4;
	if(m_rotation < 0) m_rotation = 0;
}

void Creature::MoveForward()
{
	m_position.x += m_speed * cos( m_rotation );
	m_position.y += m_speed * sin( m_rotation );

	if(m_position.x > m_mapDimensions.x-1)
		m_position.x = m_mapDimensions.x-1;
	if(m_position.y > m_mapDimensions.y-1)
		m_position.y = m_mapDimensions.y-1;
	if(m_position.x < 0)
		m_position.x = 0;
	if(m_position.y < 0)
		m_position.y = 0;
}
