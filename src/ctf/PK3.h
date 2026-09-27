#ifndef _PK3_H
#define _PK3_H

#include <stdexcept>
#include "../pipeline.h"
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

	QuagmireIII cipher1("KRYPTOS", "ORDINATE");
	QuagmireIII cipher2("KRYPTOS", "PENTIMENTO");
	Pipeline pipeline({&cipher1, &cipher2});

	const string encoded = pipeline.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("PK3 encoding failed.");

	const string decoded = pipeline.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("PK3 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
