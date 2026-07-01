#include <stdexcept>

#include "hill_cipher.h"

static int WrapIndex(int n, int base) {
	return ((n % base) + base) % base;
}

static int ModInverse(int a, int m) {
	a = WrapIndex(a, m);
	for (int x = 1; x < m; x++)
		if (WrapIndex(a * x, m) == 1)
			return x;
	return 0;
}

static string Deduplicate(const string& text) {
	string result;
	result.reserve(text.size());
	for (char c : text)
		if (result.find(c) == string::npos)
			result += c;
	return result;
}

int HillCipher::CharToIndex(char c) const {
	return alphabet.find(c);
}

char HillCipher::IndexToChar(int idx) const {
	return alphabet[WrapIndex(idx, alphabet_size)];
}

static int at(const mat3& mat, int row, int col) {
	return round(mat[col][row]);
}

static int determinant(const mat3& mat) {
	int a = at(mat, 0, 0), b = at(mat, 0, 1), c = at(mat, 0, 2);
	int d = at(mat, 1, 0), e = at(mat, 1, 1), f = at(mat, 1, 2);
	int g = at(mat, 2, 0), h = at(mat, 2, 1), i = at(mat, 2, 2);
	return a * (e * i - f * h) - b * (d * i - f * g) + c * (d * h - e * g);
}

static mat3 adjugate(const mat3& mat) {
	int a = at(mat, 0, 0), b = at(mat, 0, 1), c = at(mat, 0, 2);
	int d = at(mat, 1, 0), e = at(mat, 1, 1), f = at(mat, 1, 2);
	int g = at(mat, 2, 0), h = at(mat, 2, 1), i = at(mat, 2, 2);

	int A =  (e * i - f * h), B = -(d * i - f * g), C = (d * h - e * g);
	int D = -(b * i - c * h), E = (a * i - c * g), F = -(a * h - b * g);
	int G =  (b * f - c * e), H = -(a * f - c * d), I = (a * e - b * d);

	mat3 adj;
	adj[0][0] = A; adj[1][0] = D; adj[2][0] = G;
	adj[0][1] = B; adj[1][1] = E; adj[2][1] = H;
	adj[0][2] = C; adj[1][2] = F; adj[2][2] = I;
	return adj;
}

void HillCipher::ComputeInverseMatrix() {
	int det = WrapIndex(determinant(key_matrix), alphabet_size);
	int det_inv = ModInverse(det, alphabet_size);
	mat3 adj = adjugate(key_matrix);
	for (int col = 0; col < 3; col++)
		for (int row = 0; row < 3; row++)
			inv_key_matrix[col][row] = WrapIndex(at(adj, row, col) * det_inv, alphabet_size);
}

ivec3 HillCipher::MultiplyVec(const mat3& matrix, const ivec3& v) const {
	vec3 result = matrix * vec3(v);
	return ivec3(WrapIndex(round(result.x), alphabet_size),
				 WrapIndex(round(result.y), alphabet_size),
				 WrapIndex(round(result.z), alphabet_size));
}

string HillCipher::Process(const string& text, const mat3& matrix) const {
	string result;
	result.reserve(text.size());

	for (size_t i = 0; i < text.size(); i += 3) {
		ivec3 v(CharToIndex(text[i]), CharToIndex(text[i + 1]), CharToIndex(text[i + 2]));
		ivec3 r = MultiplyVec(matrix, v);
		result += IndexToChar(r.x);
		result += IndexToChar(r.y);
		result += IndexToChar(r.z);
	}
	return result;
}

HillCipher::HillCipher(const string& prefix, const string& keyword) {
	alphabet = Deduplicate(prefix + "ABCDEFGHIJKLMNOPQRSTUVWXYZ");
	alphabet_size = alphabet.size();

	int idx[9];
	for (int i = 0; i < 9; i++)
		idx[i] = CharToIndex(keyword[i]);

	for (int row = 0; row < 3; row++)
		for (int col = 0; col < 3; col++)
			key_matrix[col][row] = idx[row * 3 + col];

	ComputeInverseMatrix();
}

string HillCipher::Encode(const string& plaintext) const {
	return Process(plaintext, key_matrix);
}

string HillCipher::Decode(const string& ciphertext) const {
	return Process(ciphertext, inv_key_matrix);
}
