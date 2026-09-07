#ifndef _PK3_H
#define _PK3_H

#include <stdexcept>
#include "../quagmire.h"

void DecodePK3() {
	const string ciphertext =
	"HWZTRPPVHZLHRBQBQOMZBACNOT"
	"HLYGBATBTKHERQHRVZWWXCTZLR"
	"RVZCROHCIOTBVJKCALNKFJHEIM"
	"KUHJPFNVBCGQYNZMOHGBUTDPTJ"
	"TDSUBOLYPLSKIEMANXMFNDBCTN"
	"RTLLVQOXUBPAXQUVDNXUMCIFOG"
	"ETZWHJDIWDBWQFXAOMWBBCQXYZ"
	"FZBTRIQMYOFFMVWSFLPTHFFQUI"
	"NGLAMSQJOPUESPIQGZZCTJVRLQ"
	"MIIRROOGBWNPQMXFQDVFTCVGNR"
	"IXQKUYYKBRTWPCDHLAWC";

	const string plaintext = Normalize(
	"Seventh month. I wrote to fifteen correspondents in six countries,"
	"seeking any word of the item. Most knew nothing."
	"A few had heard legends of a needle fine enough to split a hair or pierce glass."
	"At last a Viennese anatomist said he saw such an instrument used at a surgical demonstration in Bern."
	"I wrote to his address. No answer came. I wrote again.");

	const QuagmireS cipher1 = QuagmireS::QuagmireIII("KRYPTOS", "PENTIMENTO");
	const QuagmireS cipher2 = QuagmireS::QuagmireIII("KRYPTOS", "ORDINATE");

	const string encoded1 = cipher1.Encode(plaintext);
	const string encoded2 = cipher2.Encode(encoded1);
	if (encoded2 != ciphertext)
		throw runtime_error("PK3 encoding failed.");

	const string decoded2 = cipher2.Decode(ciphertext);
	const string decoded1 = cipher1.Decode(decoded2);
	if (decoded1 != plaintext)
		throw runtime_error("PK3 decoding failed.");

	printf("%s\n\n", decoded1.c_str());
}

#endif
