#ifndef _BEAUFORT_H
#define _BEAUFORT_H

#include "utils.h"

class Beaufort {
private:
	string key;
	string alphabet;
	string Process(const string& text) const;
public:
	Beaufort(const string& key, const string& alphabet_key = "");
	string Encode(const string& plaintext) const;
	string Decode(const string& ciphertext) const;
	const string GetKey() const;
};

#endif
