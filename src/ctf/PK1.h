#ifndef _PK1_H
#define _PK1_H

#include <stdexcept>
#include "../quagmire.h"

void DecodePK1() {
	const string ciphertext =
	"MQRALWVSJIMSXGJSVWQPHJMDIN"
	"KXGIMHNKYUTXTTGJCYIABTJUMQ"
	"EOFBITNBMONGVWETDLAIJPQYMZ"
	"IKBQVRXZHUIJVDJLTQHIQYHEQK"
	"FTPTJYCONAFXYWQIBONAYXGWJF"
	"FIQMVXNVQYQFMWKFEJQYZFBWKX"
	"BKDQLJRELWGWDKHECRSFBKOVQJ"
	"CPYDNKXYHE";

	const string plaintext = Normalize(
	"Investigation log, item eight: knot, tightly-wound, its thread inscribed with letters."
	"The accession log says once unraveled it reveals the route to the lost archive of Pellegrin."
	"Twelve prior archivists tried to unravel it. All failed.");

	const QuagmireS cipher = QuagmireS::QuagmireIII("KRYPTOS", "PROVENANCE");

	const string encoded = cipher.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("PK1 encoding failed.");

	const string decoded = cipher.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("PK1 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
