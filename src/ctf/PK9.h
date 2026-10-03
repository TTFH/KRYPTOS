#ifndef _PK9_H
#define _PK9_H

#include <stdexcept>
#include "../pipeline.h"
#include "../quagmire.h"
#include "../transposition.h"

void DecodePK9() {
	const string ciphertext =
	"KSYAWFEYYOISZGEUFBLYATAIBY"
	"FAQBQYYVDWJKLJXMYIEPIFVHPQ"
	"NHZGSUHUUDXLEHRHUMALHEGLHX"
	"SJMUXGNUIVBXGUJHZRZGUSVHML"
	"SCTSUQXHSUMQQIFUQGKHJGUQGL"
	"HDKEWSKAMHIJXD";

	const string plaintext = Normalize(
	"I spent the past month with the needle and knot,"
	"and at last Pellegrin's final message has been revealed to me."
	"I will now seal it for you under every cipher I used in this testament.");

	Pipeline pipeline({
		new QuagmireIII("KRYPTOS", "CLEPSYDRA"),
		new SpiralTransposition(ciphertext.length(), 12),
		new ColumnarTransposition(ciphertext.length(), "BEAMWORK"),
	});

	const string encoded = pipeline.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("PK9 encoding failed.");

	const string decoded = pipeline.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("PK9 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
