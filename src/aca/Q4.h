#ifndef _Q4_H
#define _Q4_H

#include <stdexcept>
#include "../quagmire.h"

// https://www.cryptogram.org/downloads/aca.info/ciphers/QuagmireIV.pdf
void DecodeQ4() {
	const string ciphertext =
	"VBMRFCYISPMPBRRHEICXRREIGDX";

	const string plaintext = Normalize(
	"This one employs three keywords");

	const QuagmireS cipher = QuagmireS::QuagmireIV("SENORY", "PERCEPTION", "EXTRA");

	const string encoded = cipher.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("Q4 encoding failed.");

	const string decoded = cipher.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("Q4 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
