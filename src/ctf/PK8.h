#ifndef _PK8_H
#define _PK8_H

#include <stdexcept>
#include "../quagmire.h"

void DecodePK8() {
	const string ciphertext =
	"COPVEJJVSVURTVIPYOTPLHGBTM"
	"AUCCPESIWIGZBWSJPKTRPUEKQF"
	"IFCLHMXTHIMHWOYIGURBOMPARC"
	"VXVKBDDVBVHDRHGCVNWWVLBMYW"
	"MWHICFIXZWBVZYCQGNOGJGUMLN"
	"PUTHQCXNWPQZOIRJZGSWVPY";

	const string plaintext = Normalize(
	"I leave at midnight. Before going, I pick up one needle from the gutter."
	"I am grateful to my teacher, but the archive is my true calling, and the knot awaits."
	"I leave the Whitesmith a short letter.");

	const QuagmireS cipher1 = QuagmireS::QuagmireIII("KRYPTOS", "METE");
	const QuagmireS cipher2 = QuagmireS::QuagmireIII("KRYPTOS", "METER");
	const QuagmireS cipher3 = QuagmireS::QuagmireIII("KRYPTOS", "METIER");
	const QuagmireS cipher4 = QuagmireS::QuagmireIII("KRYPTOS", "MASTERY");

	const string encoded1 = cipher1.Encode(plaintext);
	const string encoded2 = cipher2.Encode(encoded1);
	const string encoded3 = cipher3.Encode(encoded2);
	const string encoded4 = cipher4.Encode(encoded3);
	if (encoded4 != ciphertext)
		throw runtime_error("PK8 encoding failed.");

	const string decoded4 = cipher4.Decode(ciphertext);
	const string decoded3 = cipher3.Decode(decoded4);
	const string decoded2 = cipher2.Decode(decoded3);
	const string decoded1 = cipher1.Decode(decoded2);
	if (decoded1 != plaintext)
		throw runtime_error("PK8 decoding failed.");

	printf("%s\n\n", decoded1.c_str());
}

#endif
