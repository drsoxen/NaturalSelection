#pragma once
#include <vector>
using namespace std;

enum class InputType {Oscillator, CenterAngle, Rotation, COUNT};
enum class OutputType {RotateR, RotateL, MoveForward, COUNT};
static const int NumberOfHidden = 3;

class Connection;

class Neuron
{
public:
	double m_value = 0;
	vector<Connection> m_connections;
};

class Connection
{
public:
	double m_weight = 0;
	Neuron * m_next = nullptr;
	Connection(double weight, Neuron * next);
};

class Output : public Neuron
{
public:
	OutputType m_type;
	Output(OutputType type);
};

class Hidden : public Neuron
{
public:
	Hidden(double bias);
};

class Input : public Neuron
{
public:
	InputType m_type;
	Input(InputType type);
};


class Brain
{
	vector<Input> m_inputNeurons;
	vector<Hidden> m_hiddenNeurons;
	vector<Output> m_outputNeurons;

public:
	Brain();

	void RandomConnections();
	double Mutate(double value);
	void InheritConnections(Brain *parentBrain);
	Neuron * GetInputNeuronByType(InputType type);
	OutputType MakeDecision();
	void Process();
	void Forget();
};




















