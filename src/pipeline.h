#ifndef _PIPELINE_H
#define _PIPELINE_H

#include <string>
#include <vector>

#include "utils.h"

class ICipher {
public:
	virtual ~ICipher() = default;
	virtual string Encode(const string& plaintext) = 0;
	virtual string Decode(const string& ciphertext) = 0;
};

class Pipeline {
private:
	vector<ICipher*> ciphers;
public:
	Pipeline(initializer_list<ICipher*> ciphers_list) : ciphers(ciphers_list) {}
	string Encode(const string& plaintext) const {
		string result = plaintext;
		for (vector<ICipher*>::const_iterator it = ciphers.begin(); it != ciphers.end(); it++)
			result = (*it)->Encode(result);
		return result;
	}
	string Decode(const string& ciphertext) const {
		string result = ciphertext;
		for (reverse_iterator<vector<ICipher*>::const_iterator> it = ciphers.rbegin(); it != ciphers.rend(); it++)
			result = (*it)->Decode(result);
		return result;
	}
};

#endif
