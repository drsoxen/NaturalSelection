#include "Brain.h"
#include <iostream>
#include <chrono>
#include <fstream>
#include "Utils.h"

using namespace std;

Brain::Brain()
{
	//Build Neurons
	for(int i = 0; i < static_cast<int>(InputType::COUNT); i++)
	{
		m_inputNeurons.push_back(Input(static_cast<InputType>(i)));
	}

	for(int i = 0; i < NumberOfHidden; i++)
	{
		m_hiddenNeurons.push_back(Hidden(1));
	}

	for(int i = 0; i < static_cast<int>(OutputType::COUNT); i++)
	{
		m_outputNeurons.push_back(Output(static_cast<OutputType>(i)));
	}
}

void Brain::RandomConnections()
{
	//Build Connections
	for(int i = 0; i < m_inputNeurons.size(); i++)
	{
		for(int j = 0; j < m_hiddenNeurons.size(); j++)
		{
			m_inputNeurons[i].m_connections.push_back(Connection((double)rand()/RAND_MAX, &m_hiddenNeurons[j]));
		}
	}

	for(int i = 0; i < m_hiddenNeurons.size(); i++)
	{
		for(int j = 0; j < m_outputNeurons.size(); j++)
		{
			m_hiddenNeurons[i].m_connections.push_back(Connection((double)rand()/RAND_MAX, &m_outputNeurons[j]));
		}
	}
}

double Brain::Mutate(double value)
{
	if(rand()%1000 == 42)
	{
		//LOGS("MUTATE");

		return value += RandomRange(-1,1);
	}

	return value;
}

void Brain::InheritConnections(Brain *parentBrain)
{
	//Build Connections
	for(int i = 0; i < m_inputNeurons.size(); i++)
	{
		for(int j = 0; j < m_hiddenNeurons.size(); j++)
		{
			m_inputNeurons[i].m_connections.push_back(Connection(Mutate(parentBrain->m_inputNeurons[i].m_connections[j].m_weight), &m_hiddenNeurons[j]));
		}
	}

	for(int i = 0; i < m_hiddenNeurons.size(); i++)
	{
		for(int j = 0; j < m_outputNeurons.size(); j++)
		{
			m_hiddenNeurons[i].m_connections.push_back(Connection(Mutate(parentBrain->m_hiddenNeurons[i].m_connections[j].m_weight), &m_outputNeurons[j]));
		}
	}
}

Neuron * Brain::GetInputNeuronByType(InputType type)
{
	for(int i = 0; i < m_inputNeurons.size(); i++)
	{
		if(m_inputNeurons[i].m_type == type)
		{
			return &m_inputNeurons[i];
		}
	}
	return nullptr;
}


void Brain::Process()
{
	for(int i = 0; i < m_inputNeurons.size(); i++)
	{
		for(int j = 0; j < m_inputNeurons[i].m_connections.size(); j++)
		{
			for(int k = 0; k < m_inputNeurons[i].m_connections[j].m_next->m_connections.size(); k++)
			{
				double count = 1;
				count *= m_inputNeurons[i].m_value;
				count *= m_inputNeurons[i].m_connections[j].m_weight;
				//count *= m_inputNeurons[i].m_connections[j].m_next->m_value;
				count *= m_inputNeurons[i].m_connections[j].m_next->m_connections[k].m_weight;
				m_inputNeurons[i].m_connections[j].m_next->m_connections[k].m_next->m_value += count;

				//m_inputNeurons[i].m_connections[j].m_next->m_connections[k].m_next->m_value = Normalize(m_inputNeurons[i].m_connections[j].m_next->m_connections[k].m_next->m_value, 0, 3);
			}
		}
	}
}

OutputType Brain::MakeDecision()
{
	OutputType currentHighest = OutputType::COUNT;
	double highest = 0;
	for(int i = 0; i < m_outputNeurons.size(); i++)
	{
		if(m_outputNeurons[i].m_value > highest)
		{
			currentHighest = m_outputNeurons[i].m_type;
			highest = m_outputNeurons[i].m_value;
		}
	}

	return currentHighest;
}

void Brain::Forget()
{
	for(int i = 0; i < m_outputNeurons.size(); i++)
	{
		m_outputNeurons[i].m_value = 0;
	}
}

Connection::Connection(double weight, Neuron * next)
{
	m_weight = weight;
	m_next = next;
}

Output::Output(OutputType type)
{
	m_type = type;
	m_value = 0;
}

Hidden::Hidden(double bias)
{
	m_value = bias;
}

Input::Input(InputType type)
{
	m_type = type;
	m_value = 0;
}













