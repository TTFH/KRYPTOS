#ifndef _BEAUFORT_H
#define _BEAUFORT_H

#include "utils.h"
#include "pipeline.h"

class Beaufort: public ICipher {
private:
	string key;
	string alphabet;
	string Process(const string& text) const;
public:
	Beaufort(const string& key, const string& alphabet_key = "");
	string Encode(const string& plaintext) override;
	string Decode(const string& ciphertext) override;
};

#endif
