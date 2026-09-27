#ifndef _Q3_H
#define _Q3_H

#include <stdexcept>
#include "../quagmire.h"

// https://www.cryptogram.org/downloads/aca.info/ciphers/QuagmireIII.pdf
void DecodeQ3() {
	const string ciphertext =
	"KRSLWMITJDVIABMRGQMTMLLIVIFUIXRHTNYONVRHHIIIRMCAOVEI";

	const string plaintext = Normalize(
	"The same keyed alphabet is used for plain and cipher alphabets");

	QuagmireS cipher = QuagmireS::QuagmireIII("AUTOMOBILE", "HIGHWAY");

	const string encoded = cipher.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("Q3 encoding failed.");

	const string decoded = cipher.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("Q3 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
