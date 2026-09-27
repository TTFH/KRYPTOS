#ifndef _Q1_H
#define _Q1_H

#include <stdexcept>
#include "../quagmire.h"

// https://www.cryptogram.org/downloads/aca.info/ciphers/QuagmireI.pdf
void DecodeQ1() {
	const string ciphertext =
	"QPMGQRBUJUYIFDMPYAIFQYYJJJHJYCJLUUTPIDVWYMFSGAESDWHIZRBLIRVCFCZPELBPZYYJJJHWLJJLPUP";

	const string plaintext = Normalize(
	"The Quag One is a periodic cipher with a keyed plain alphabet run against a straight cipher alphabet.");

	QuagmireS cipher = QuagmireS::QuagmireI("SPRINGFEVER", "FLOWER");

	const string encoded = cipher.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("Q1 encoding failed.");

	const string decoded = cipher.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("Q1 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
