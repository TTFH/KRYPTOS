#ifndef _K1_H
#define _K1_H

#include <stdexcept>
#include "../quagmire.h"

void DecodeK1() {
	const string ciphertext =
	"EMUFPHZLRFAXYUSDJKZLDKRNSHGNFIVJ"
	"YQTQUXQBQVYUVLLTREVJYQTMKYRDMFD";

	const string plaintext = Normalize(
	"Between subtle shading and the absence of light lies the nuance of iqlusion.");

	const QuagmireS cipher = QuagmireS::QuagmireIII("KRYPTOS", "PALIMPSEST");

	const string encoded = cipher.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("K1 encoding failed.");

	const string decoded = cipher.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("K1 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
