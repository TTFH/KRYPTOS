#ifndef _QUAGMIRE_H
#define _QUAGMIRE_H

#include "pipeline.h"
#include "utils.h"

template <typename StringT, typename CharT>
class Quagmire {
private:
	StringT key;
	StringT top_alphabet;
	StringT rep_alphabet;

	static int WrapIndex(int n, int base);
	static StringT Deduplicate(const StringT& text);
	static StringT Complement(const StringT& alphabet, const StringT& subset);
	StringT Process(const StringT& text, bool encode) const;
	Quagmire(const StringT& key, const StringT& top_alphabet, const StringT& rep_alphabet);
public:
	static Quagmire QuagmireI(const StringT& top_key, const StringT& key);
	static Quagmire QuagmireII(const StringT& rep_key, const StringT& key);
	static Quagmire QuagmireIII(const StringT& rep_key, const StringT& key);
	static Quagmire QuagmireIV(const StringT& top_key, const StringT& rep_key, const StringT& key);
	static Quagmire QuagmireIV(const StringT& rep_key, const StringT& key);
	StringT Encode(const StringT& plaintext);
	StringT Decode(const StringT& ciphertext);
};

extern template class Quagmire<string, char>;
extern template class Quagmire<wstring, wchar_t>;

typedef Quagmire<string, char> QuagmireS;
typedef Quagmire<wstring, wchar_t> QuagmireW;

class QuagmireIII : public ICipher {
private:
	QuagmireS cipher;
public:
	QuagmireIII(const string& rep_key, const string& key) :
	cipher(QuagmireS::QuagmireIII(rep_key, key)) {}
	string Encode(const string& plaintext) override {
		return cipher.Encode(plaintext);
	}
	string Decode(const string& ciphertext) override {
		return cipher.Decode(ciphertext);
	}
};

#endif
