#ifndef _TRANSPOSITION_H
#define _TRANSPOSITION_H

#include "utils.h"
#include "pipeline.h"

enum Direction {
	CW, CCW
};

class Transposition: public ICipher {
protected:
	unsigned int size = 0;
	unsigned int cols = 0;
	char* grid = nullptr;
	void ResizeProxy(unsigned int cols);
	Transposition(unsigned int size);
	void FromRows(const string& text);
	void FromColumns(const string& text);
	string FetchByRows() const;
	string FetchByColumns() const;
	void PrintGrid() const;
public:
	~Transposition();
};

class RotatingTransposition: public Transposition {
private:
	unsigned int width;
	void Resize(unsigned int cols);
	void Rotate(Direction dir);
public:
	RotatingTransposition(unsigned int size, unsigned int width);
	string Encode(const string& plaintext) override;
	string Decode(const string& ciphertext) override;
};

class ColumnarTransposition: public Transposition {
private:
	string keyword;
	void SwapColumns(bool encode);
public:
	ColumnarTransposition(unsigned int size, const string& keyword);
	string Encode(const string& plaintext) override;
	string Decode(const string& ciphertext) override;
};

class SpiralTransposition: public Transposition {
public:
	SpiralTransposition(unsigned int size, unsigned int width);
	string Encode(const string& plaintext) override;
	string Decode(const string& ciphertext) override;
};

#endif
