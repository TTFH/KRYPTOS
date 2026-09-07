#ifndef _PK2_H
#define _PK2_H

#include <stdexcept>
#include "../transposition.h"

void DecodePK2() {
	const string ciphertext =
	"HNETIOCOIOISNNENEELOWYTTLQ"
	"UBDBTHTEOTRRASAHCDSEETONVR"
	"CESHRRETUPCITEWIGNIUNIGANL"
	"HJRAHMSRUINHERAEEAEAJEEEEK"
	"EEDATIIAONIXRNRHCNTLGLOIIU"
	"NSEESEGNBANTVTCSFREDIUROTN"
	"ENHMRIIEROLTLSDAOOAEQIEOAP"
	"UHITHAIKHTIEUHGSLAFFSNVRSR"
	"HNNSMASTIPIAHAOEEUDESSOEON"
	"CDHAOTOOEOTSEECLADNHNTOUVS"
	"GAGTATSNEWHSATEUEETEURTRNE"
	"OGITREHMPPROBEOETOERICETGS"
	"MTEITENNSGSDRNOVTTFBTTATML"
	"OSOPLSTARATE";

	const string plaintext = Normalize(
	"I have found references to the knot in seven other records in our archive."
	"The most intriguing is a passing comment in a treatise on textiles,"
	"written in Pellegrin's own hand, which says: un ago tanto sottile da leggere qualunque nodo."
	"I believed this to be just a turn of phrase, but the other mentions,"
	"scattered through marginalia in books that share no other topic,"
	"have led me to suspect the passage refers to a real object, a needle.");

	ColumnarTransposition cipher(ciphertext.length(), "MARGINS");

	cipher.FromRows(plaintext);
	cipher.Encode();
	const string encoded = cipher.FetchByColumns();
	if (encoded != ciphertext)
		throw runtime_error("PK2 encoding failed.");

	cipher.FromColumns(ciphertext);
	cipher.Decode();
	const string decoded = cipher.FetchByRows();
	if (decoded != plaintext)
		throw runtime_error("PK2 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
