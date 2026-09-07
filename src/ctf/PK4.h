#ifndef _PK4_H
#define _PK4_H

#include <stdexcept>
#include "../quagmire.h"
#include "../transposition.h"

void DecodePK4() {
	const string ciphertext =
	"YOVISYUAFKUQNRJQLZTAZTMQOU"
	"KELJKCYUWIDSPSWRJRUEZNIFPU"
	"MUHQFFVBGOBEPWNTZGKVUTOVFS"
	"ADUJUAYGWKQYOGNKHZVQMEWHSJ"
	"GJFOBPHXKAPEXPWRJTSPSIJLCS"
	"XYTLDFBNZNPUAZNBZPKRFCUZDD"
	"ZHZULZVPVWCXSIUVSCCFATGSJP"
	"NIGCJVTMUPTCGRTOFRXWCYKOMX"
	"OJKCECRUCKBDCIYJ";

	const string plaintext = Normalize(
	"Two years in. The needle's trail led me to a craftsman named the Whitesmith."
	"On the road to his Alpine workshop I reread his perfunctory letters."
	"He met me at the gates and led me to a stone barn stacked with winter fodder."
	"One of his needles is hidden in the barn. I have begun to work.");

	ColumnarTransposition cipher1(ciphertext.length(), "UNDERLAY");
	const QuagmireS cipher2 = QuagmireS::QuagmireIII("KRYPTOS", "OCHRE");
	const QuagmireS cipher3 = QuagmireS::QuagmireIII("KRYPTOS", "VERDIGRIS");

	cipher1.FromRows(plaintext);
	cipher1.Encode();
	const string encoded1 = cipher1.FetchByColumns();
	const string encoded2 = cipher2.Encode(encoded1);
	const string encoded3 = cipher3.Encode(encoded2);
	if (encoded3 != ciphertext)
		throw runtime_error("PK4 encoding failed.");

	const string decoded3 = cipher3.Decode(ciphertext);
	const string decoded2 = cipher2.Decode(decoded3);
	cipher1.FromColumns(decoded2);
	cipher1.Decode();
	const string decoded1 = cipher1.FetchByRows();
	if (decoded1 != plaintext)
		throw runtime_error("PK4 decoding failed.");

	printf("%s\n\n", decoded1.c_str());
}

#endif
