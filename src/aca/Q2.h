#ifndef _Q2_H
#define _Q2_H

#include <stdexcept>
#include "../quagmire.h"

// https://www.cryptogram.org/downloads/aca.info/ciphers/QuagmireII.pdf
void DecodeQ2() {
	const string ciphertext =
	"JICICOSLYKILFVCHEBDXCCORJIOEWAFMWKKTXBGWHRJIBKEDBJWZABUXWHEHUXOXCU";

	const string plaintext = Normalize(
	"In the Quag Two a straight plain alphabet is run against a keyed cipher alphabet.");

	const QuagmireS cipher = QuagmireS::QuagmireII("SPRINGFEVER", "FLOWER");

	const string encoded = cipher.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("Q2 encoding failed.");

	const string decoded = cipher.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("Q2 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
