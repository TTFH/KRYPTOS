#ifndef _TRANSPOSITION_H
#define _TRANSPOSITION_H

#include "utils.h"

enum Direction {
	CW, CCW
};

class Transposition {
protected:
	unsigned int size = 0;
	unsigned int cols = 0;
	char* grid = nullptr;
	void ResizeProxy(unsigned int cols);
public:
	Transposition(unsigned int size);
	void FromRows(const string& text);
	void FromColumns(const string& text);
	string FetchByRows() const;
	string FetchByColumns() const;
	void PrintGrid() const;
	~Transposition();
};

class RotatingTransposition : public Transposition {
public:
	RotatingTransposition(unsigned int size);
	void Resize(unsigned int cols);
	void Rotate(Direction dir);
};

class ColumnarTransposition : public Transposition {
private:
	string keyword;
public:
	ColumnarTransposition(unsigned int size, const string& keyword);
	void Encode();
	void Decode();
};

#endif
