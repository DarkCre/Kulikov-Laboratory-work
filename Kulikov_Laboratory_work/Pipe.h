#pragma once


class Pipe
{
private:
	double _PipeLength; // ����� �����
	double _PipeDia;   //  ������� �����
	bool _PipeStatus; //   ������ ����� (� ������� ��� ���)
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

