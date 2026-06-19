#include "quagmire.h"

template<typename CharT>
struct Alphabet;

template<>
struct Alphabet<char> {
	static constexpr const char* value =
		"ABCDEFGHIJKLMNOPQRSTUVWXYZ";
};

template<>
struct Alphabet<wchar_t> {
	static constexpr const wchar_t* value =
		L"АБВГДЕЖЗИЙКЛМНОПРСТУФХЦЧШЩЪЫЬЭЮЯ";
};

template<typename CharT>
struct CustomAlphabet;

template<>
struct CustomAlphabet<char> {
	static constexpr const char* value =
		"KRYPTOSABCDEFGHIJLMNQUVWXZ";
};

template<>
struct CustomAlphabet<wchar_t> {
	static constexpr const wchar_t* value =
		L"АБВГДЕЖЗИЙКЛМНОПРСТУФХШЦЧЩЪЫЬЭЮЯ";
};

template<typename StringT, typename CharT>
int Quagmire<StringT, CharT>::WrapIndex(int n, int base) {
	return ((n % base) + base) % base;
}

template<typename StringT, typename CharT>
StringT Quagmire<StringT, CharT>::Deduplicate(const StringT& text) {
	StringT result;
	result.reserve(text.size());
	for (CharT c : text)
		if (result.find(c) == StringT::npos)
			result += c;
	return result;
}

template<typename StringT, typename CharT>
StringT Quagmire<StringT, CharT>::Complement(const StringT& alphabet, const StringT& subset) {
	StringT result;
	result.reserve(alphabet.size());
	for (CharT c : alphabet)
		if (subset.find(c) == StringT::npos)
			result += c;
	return result;
}

template<typename StringT, typename CharT>
StringT Quagmire<StringT, CharT>::Process(const StringT& text, bool encode) const {
	StringT output;
	output.reserve(text.length());
	const size_t base = top_alphabet.length();
	const size_t key_len = key.length();
	size_t key_pos = 0;

	for (CharT c : text) {
		const size_t input_idx = encode
			? top_alphabet.find(c)
			: rep_alphabet.find(c);
		if (input_idx == StringT::npos) {
			output += c;
			continue;
		}
		const CharT key_char = key[key_pos++ % key_len];
		const size_t key_idx = rep_alphabet.find(key_char);
		const int shift = encode ? key_idx : -key_idx;
		output += encode
			? rep_alphabet[WrapIndex(input_idx + shift, base)]
			: top_alphabet[WrapIndex(input_idx + shift, base)];
	}
	return output;
}

// I got a bit carried away with the abstraction here

template<typename StringT, typename CharT>
Quagmire<StringT, CharT>::Quagmire(const StringT& key, const StringT& top_alphabet, const StringT& rep_alphabet)
	: key(key), top_alphabet(top_alphabet), rep_alphabet(rep_alphabet) {
}

template<typename StringT, typename CharT>
Quagmire<StringT, CharT> Quagmire<StringT, CharT>::QuagmireI(const StringT& top_key, const StringT& key) {
	const StringT ALPHABET = Alphabet<CharT>::value;
	const StringT dedup_top_key = Deduplicate(top_key);
	const StringT top_alphabet = Complement(ALPHABET, dedup_top_key) + dedup_top_key;
	return Quagmire(key, top_alphabet, ALPHABET);
}

template<typename StringT, typename CharT>
Quagmire<StringT, CharT> Quagmire<StringT, CharT>::QuagmireII(const StringT& rep_key, const StringT& key) {
	const StringT ALPHABET = Alphabet<CharT>::value;
	const StringT rep_alphabet = Deduplicate(rep_key + ALPHABET);
	return Quagmire(key, ALPHABET, rep_alphabet);
}

template<typename StringT, typename CharT>
Quagmire<StringT, CharT> Quagmire<StringT, CharT>::QuagmireIII(const StringT& rep_key, const StringT& key) {
	const StringT ALPHABET = Alphabet<CharT>::value;
	const StringT rep_alphabet = Deduplicate(rep_key + ALPHABET);
	return Quagmire(key, rep_alphabet, rep_alphabet);
}

template<typename StringT, typename CharT>
Quagmire<StringT, CharT> Quagmire<StringT, CharT>::QuagmireIV(const StringT& top_key, const StringT& rep_key, const StringT& key) {
	const StringT ALPHABET = Alphabet<CharT>::value;
	const StringT top_alphabet = Deduplicate(top_key + ALPHABET);
	const StringT rep_alphabet = Deduplicate(rep_key + ALPHABET);
	return Quagmire(key, top_alphabet, rep_alphabet);
}

template<typename StringT, typename CharT>
Quagmire<StringT, CharT> Quagmire<StringT, CharT>::QuagmireIV(const StringT& rep_key, const StringT& key) {
	const StringT ALPHABET = Alphabet<CharT>::value;
	const StringT custom_alphabet = CustomAlphabet<CharT>::value;
	const StringT rep_alphabet = Deduplicate(rep_key + custom_alphabet);

	StringT encoded_key;
	encoded_key.reserve(key.length());
	for (CharT c : key) {
		const size_t key_idx = ALPHABET.find(c);
		encoded_key += rep_alphabet[key_idx];
	}
	return Quagmire(encoded_key, ALPHABET, rep_alphabet);
}

template<typename StringT, typename CharT>
StringT Quagmire<StringT, CharT>::Encode(const StringT& plaintext) const {
	return Process(plaintext, true);
}

template<typename StringT, typename CharT>
StringT Quagmire<StringT, CharT>::Decode(const StringT& ciphertext) const {
	return Process(ciphertext, false);
}

template class Quagmire<string, char>;
template class Quagmire<wstring, wchar_t>;
