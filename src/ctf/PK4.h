#ifndef _PK4_H
#define _PK4_H

#include <stdexcept>
#include "../pipeline.h"
#include "../quagmire.h"
#include "../transposition.h"

const string PK4 = Normalize(
	"Two years in. The needle's trail led me to a craftsman named the Whitesmith."
	"On the road to his Alpine workshop I reread his perfunctory letters."
	"He met me at the gates and led me to a stone barn stacked with winter fodder."
	"One of his needles is hidden in the barn. I have begun to work.");

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

	const string plaintext = PK4;

	Pipeline pipeline({
		new ColumnarTransposition(ciphertext.length(), "UNDERLAY"),
		new QuagmireIII("KRYPTOS", "OCHRE"),
		new QuagmireIII("KRYPTOS", "VERDIGRIS"),
	});

	const string encoded = pipeline.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("PK4 encoding failed.");

	const string decoded = pipeline.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("PK4 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
