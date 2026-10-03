#ifndef _PK6_H
#define _PK6_H

#include <stdexcept>
#include "../pipeline.h"
#include "../quagmire.h"
#include "../transposition.h"

void DecodePK6() {
	const string ciphertext =
	"BXFIVOAJFNMLKEVEHDFJQCMVLM"
	"GNVOHCJNBOAEVRRWIJFMCWMNOO"
	"MMOSRNKYOCFRYWKHBNMYCYHDEC"
	"QCFNTOXNOBKBHWBOMNHFIIZDBJ"
	"RNXBABFRCBLIIBLDCINOHNLXSB"
	"KVMSBNVOFVNBFYDJEVUGMNOBML"
	"CQACBLGNABEBCJXBEYUIBDTFOS"
	"OULYCQHBXUHSEYMCBJIIHWDCFS"
	"EVLDMMUOVFADHUMKXCGUCQIRGB"
	"CEIJFYIXOEJYHDJHMXTDIEXNDA"
	"FBMOJMYAEYBVYNFSCXBWNYOVFD"
	"XDHWFCERDEBWZUKDIJTUGCJMMV"
	"QII";

	const string plaintext = Normalize(
	"The Whitesmith's workshop is filled with the old tools of his trade."
	"My eyes are drawn to the gutter along the wall, which is strewn with exquisite needles."
	"The Whitesmith says he makes one every day, and lost count long ago."
	"I ask what he does with them, and he says they are only the residue of his practice."
	"He tells me that if I study under him for ten years, he will let me take one of my own making.");

	Pipeline pipeline({
		new ColumnarTransposition(ciphertext.length(), "HANDIWORK"),
		new ColumnarTransposition(ciphertext.length(), "SMITHWORK"),
		new QuagmireIII("KRYPTOS", "PORTAL"),
	});

	const string encoded = pipeline.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("PK6 encoding failed.");

	const string decoded = pipeline.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("PK6 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
