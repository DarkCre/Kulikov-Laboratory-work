#pragma once


class Pipe
{
private:
	double _PipeLength; // Длина трубы
	double _PipeDia;   //  Диаметр трубы
	bool _PipeStatus; //   Статус трубы (в ремонте или нет)
	static int _PipeID;
public:
	Pipe();

	void Set(double PipeLength, double PipeDia, bool PipeStatus);
	void Set();

	double GetPipeLength() const;
	double GetPipeDia() const;
	bool GetPipeStatus() const;
	void Get() const;
	int GetPipeID() const;

	void InputPipeStatusCheck();
	
};

