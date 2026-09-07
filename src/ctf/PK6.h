#ifndef _PK6_H
#define _PK6_H

#include <stdexcept>
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

	ColumnarTransposition cipher1(ciphertext.length(), "HANDIWORK");
	ColumnarTransposition cipher2(ciphertext.length(), "SMITHWORK");
	const QuagmireS cipher3 = QuagmireS::QuagmireIII("KRYPTOS", "PORTAL");

	cipher1.FromRows(plaintext);
	cipher1.Encode();
	const string encoded1 = cipher1.FetchByColumns();

	cipher2.FromRows(encoded1);
	cipher2.Encode();
	const string encoded2 = cipher2.FetchByColumns();

	const string encoded3 = cipher3.Encode(encoded2);
	if (encoded3 != ciphertext)
		throw runtime_error("PK6 encoding failed.");

	const string decoded3 = cipher3.Decode(ciphertext);

	cipher2.FromColumns(decoded3);
	cipher2.Decode();
	const string decoded2 = cipher2.FetchByRows();

	cipher1.FromColumns(decoded2);
	cipher1.Decode();
	const string decoded1 = cipher1.FetchByRows();

	if (decoded1 != plaintext)
		throw runtime_error("PK6 decoding failed.");

	printf("%s\n\n", decoded1.c_str());
}

#endif
