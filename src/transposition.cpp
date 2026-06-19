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

Transposition::Transposition(unsigned int size) : size(size), cols(size) {
	grid = new char[size];
	memset(grid, '-', size);
}

void Transposition::Resize(unsigned int cols) {
	if (size % cols != 0)
		throw invalid_argument("Grid size must be divisible by column count.");
	const string text = FetchByRows();
	this->cols = cols;
	FromRows(text);
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

void Transposition::Encode(const string& keyword) {
	if (keyword.length() != cols)
		throw invalid_argument("Keyword length does not match grid column count.");
	const vector<int> order = GetLetterOrder(keyword);
	char* new_grid = new char[size];
	const unsigned int rows = size / cols;
	for (unsigned int row = 0; row < rows; row++)
		for (unsigned int col = 0; col < cols; col++)
			new_grid[row * cols + order[col]] = grid[row * cols + col];
	delete[] grid;
	grid = new_grid;
}

void Transposition::Decode(const string& keyword) {
	if (keyword.length() != cols)
		throw invalid_argument("Keyword length does not match grid column count.");
	const vector<int> order = GetLetterOrder(keyword);
	char* new_grid = new char[size];
	const unsigned int rows = size / cols;
	for (unsigned int row = 0; row < rows; row++)
		for (unsigned int col = 0; col < cols; col++)
			new_grid[row * cols + col] = grid[row * cols + order[col]];
	delete[] grid;
	grid = new_grid;
}

void Transposition::Rotate(Direction dir) {
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
