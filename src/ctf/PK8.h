#ifndef _PK8_H
#define _PK8_H

#include <stdexcept>
#include "../pipeline.h"
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

	QuagmireIII cipher1("KRYPTOS", "METE");
	QuagmireIII cipher2("KRYPTOS", "METER");
	QuagmireIII cipher3("KRYPTOS", "METIER");
	QuagmireIII cipher4("KRYPTOS", "MASTERY");
	Pipeline pipeline({&cipher1, &cipher2, &cipher3, &cipher4});

	const string encoded = pipeline.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("PK8 encoding failed.");

	const string decoded = pipeline.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("PK8 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
