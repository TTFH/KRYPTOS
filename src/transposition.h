#ifndef _TRANSPOSITION_H
#define _TRANSPOSITION_H

#include "utils.h"

enum Direction {
	CW, CCW
};

class Transposition {
private:
	unsigned int size = 0;
	unsigned int cols = 0;
	char* grid = nullptr;
public:
	Transposition(unsigned int size);
	void Resize(unsigned int cols);
	void FromRows(const string& text);
	void FromColumns(const string& text);

	// Swap columns
	void Encode(const string& keyword);
	void Decode(const string& keyword);

	void Rotate(Direction dir);

	string FetchByRows() const;
	string FetchByColumns() const;
	void PrintGrid() const;
	~Transposition();
};

#endif
