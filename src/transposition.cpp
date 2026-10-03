#include <string.h>
#include <vector>
#include <stdexcept>

#include "transposition.h"

static vector<int> GetLetterOrder(const string& word) {
	const int n = word.size();
	for (int i = 0; i < n; i++)
		for (int j = i + 1; j < n; j++)
			if (word[i] == word[j])
				throw invalid_argument("Keyword must not contain duplicate letters.");

	vector<int> order(n);
	for (int i = 0; i < n; i++) {
		int rank = 0;
		for (int j = 0; j < n; j++)
			if (word[j] < word[i])
				rank++;
		order[i] = rank;
	}
	return order;
}

void Transposition::ResizeProxy(unsigned int cols) {
	if (size % cols != 0)
		throw invalid_argument("Grid size must be divisible by column count.");
	this->cols = cols;
}

Transposition::Transposition(unsigned int size) : size(size), cols(size) {
	grid = new char[size];
	memset(grid, '-', size);
}

void Transposition::FromRows(const string& text) {
	if (text.length() != size)
		throw invalid_argument("Text length does not match grid size.");
	strncpy(grid, text.c_str(), size);
}

void Transposition::FromColumns(const string& text) {
	if (text.length() != size)
		throw invalid_argument("Text length does not match grid size.");
	const unsigned int rows = size / cols;
	for (unsigned int col = 0; col < cols; col++)
		for (unsigned int row = 0; row < rows; row++)
			grid[row * cols + col] = text[col * rows + row];
}

string Transposition::FetchByRows() const {
	return string(grid, size);
}

string Transposition::FetchByColumns() const {
	string text;
	text.reserve(size);
	const unsigned int rows = size / cols;
	for (unsigned int col = 0; col < cols; col++)
		for (unsigned int row = 0; row < rows; row++)
			text += grid[row * cols + col];
	return text;
}

void Transposition::PrintGrid() const {
	const unsigned int rows = size / cols;
	for (unsigned int row = 0; row < rows; row++) {
		for (unsigned int col = 0; col < cols; col++)
			printf("%c ", grid[row * cols + col]);
		printf("\n");
	}
	printf("\n");
}

Transposition::~Transposition() {
	delete[] grid;
}

RotatingTransposition::RotatingTransposition(unsigned int size, unsigned int width) : Transposition(size), width(width) {
}

void RotatingTransposition::Resize(unsigned int cols) {
	ResizeProxy(cols);
}

void RotatingTransposition::Rotate(Direction dir) {
	char* new_grid = new char[size];
	const unsigned int rows = size / cols;
	for (unsigned int row = 0; row < cols; row++)
		for (unsigned int col = 0; col < rows; col++)
			new_grid[row * rows + col] = dir == CW ?
			grid[(rows - col - 1) * cols + row] :
			grid[col * cols + (cols - row - 1)];
	delete[] grid;
	grid = new_grid;
	cols = rows;
}

string RotatingTransposition::Encode(const string& plaintext) {
	Resize(width);
	FromRows(plaintext);
	Rotate(CW);
	return FetchByRows();
}

string RotatingTransposition::Decode(const string& ciphertext) {
	Resize(size / width);
	FromRows(ciphertext);
	Rotate(CCW);
	return FetchByRows();
}

ColumnarTransposition::ColumnarTransposition(unsigned int size, const string& keyword) : Transposition(size), keyword(keyword) {
	ResizeProxy(keyword.length());
}

void ColumnarTransposition::SwapColumns(bool encode) {
	if (keyword.length() != cols)
		throw invalid_argument("Keyword length does not match grid column count.");
	const vector<int> order = GetLetterOrder(keyword);
	char* new_grid = new char[size];
	const unsigned int rows = size / cols;
	for (unsigned int row = 0; row < rows; row++)
		for (unsigned int col = 0; col < cols; col++) {
			unsigned int x = encode ? order[col] : col;
			unsigned int y = encode ? col : order[col];
			new_grid[row * cols + x] = grid[row * cols + y];
		}
	delete[] grid;
	grid = new_grid;
}

string ColumnarTransposition::Encode(const string& plaintext) {
	FromRows(plaintext);
	SwapColumns(true);
	return FetchByColumns();
}

string ColumnarTransposition::Decode(const string& ciphertext) {
	FromColumns(ciphertext);
	SwapColumns(false);
	return FetchByRows();
}

typedef pair<unsigned int, unsigned int> Coord;

static vector<Coord> spiralCoords(int rows, int cols) {
	const int moves[4][2] = { { 1, 0 }, { 0, -1 }, { -1, 0 }, { 0, 1 } }; // down, left, up, right
	const unsigned int size = rows * cols;

	vector<Coord> order;
	order.reserve(size);
	bool* seen = new bool[size]();

	int r = 0;
	int c = cols - 1;
	unsigned int d = 0;

	for (unsigned int i = 0; i < size; i++) {
		order.push_back(Coord(r, c));
		seen[r * cols + c] = true;

		int nr = r + moves[d][0];
		int nc = c + moves[d][1];

		if (nr < 0 || nr >= rows || nc < 0 || nc >= cols || seen[nr * cols + nc]) {
			d = (d + 1) % 4;
			nr = r + moves[d][0];
			nc = c + moves[d][1];
		}

		r = nr;
		c = nc;
	}

	delete[] seen;
	return order;
}

SpiralTransposition::SpiralTransposition(unsigned int size, unsigned int width) : Transposition(size) {
	ResizeProxy(width);
}

string SpiralTransposition::Encode(const string& plaintext) {
	FromRows(plaintext);
	string text;
	text.reserve(size);
	unsigned int rows = plaintext.length() / cols;
	const vector<Coord> order = spiralCoords(rows, cols);
	for (unsigned int i = 0; i < size; i++)
		text += grid[order[i].first * cols + order[i].second];
	return text;
}

string SpiralTransposition::Decode(const string& ciphertext) {
	unsigned int rows = ciphertext.length() / cols;
	const vector<Coord> order = spiralCoords(rows, cols);
	for (unsigned int i = 0; i < size; i++)
		grid[order[i].first * cols + order[i].second] = ciphertext[i];
	return FetchByRows();
}
