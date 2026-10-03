#include "beaufort.h"

const string ENGLISH = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

static int WrapIndex(int n, int base) {
	return ((n % base) + base) % base;
}

static string Deduplicate(const string& text) {
	string result;
	result.reserve(text.size());
	for (char c : text)
		if (result.find(c) == string::npos)
			result += c;
	return result;
}

string Beaufort::Process(const string& text) const {
	string output;
	output.reserve(text.length());
	const size_t base = alphabet.length();
	const size_t key_len = key.length();
	size_t key_pos = 0;

	for (char c : text) {
		const size_t input_idx = alphabet.find(c);
		if (input_idx == string::npos) {
			output += c;
			continue;
		}
		const char key_char = key[key_pos++ % key_len];
		const size_t key_idx = alphabet.find(key_char);
		output += alphabet[WrapIndex(key_idx - input_idx, base)];
	}
	return output;
}

Beaufort::Beaufort(const string& key, const string& alphabet_key) : key(key) {
	alphabet = Deduplicate(alphabet_key + ENGLISH);
}

string Beaufort::Encode(const string& plaintext) {
	return Process(plaintext);
}

string Beaufort::Decode(const string& ciphertext) {
	return Process(ciphertext);
}
