#ifndef _B1_H
#define _B1_H

#include <stdexcept>
#include "../beaufort.h"

// https://www.cryptogram.org/downloads/aca.info/ciphers/Beaufort.pdf
void DecodeB1() {
	const string ciphertext =
	"PAMOPGWSODEKKT";

	const string plaintext = Normalize(
	"C equals K minus P.");

	const Beaufort cipher("RECIPROCAL");

	const string encoded = cipher.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("B1 encoding failed.");

	const string decoded = cipher.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("B1 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
