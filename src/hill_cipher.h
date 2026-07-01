#ifndef _HILL_CIPHER_H
#define _HILL_CIPHER_H

#include "utils.h"

#include <glm/glm.hpp>

using namespace glm;

class HillCipher {
private:
	string alphabet;
	int alphabet_size;
	mat3 key_matrix;
	mat3 inv_key_matrix;

	int CharToIndex(char c) const;
	char IndexToChar(int idx) const;
	void ComputeInverseMatrix();
	ivec3 MultiplyVec(const mat3& matrix, const ivec3& v) const;
	string Process(const string& text, const mat3& matrix) const;
public:
	HillCipher(const string& prefix, const string& keyword);
	string Encode(const string& plaintext) const;
	string Decode(const string& ciphertext) const;
};

#endif
