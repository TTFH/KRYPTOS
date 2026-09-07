#ifndef _PK7_H
#define _PK7_H

#include <stdexcept>
#include "../quagmire.h"
#include "../hill_cipher.h"

void DecodePK7() {
	const string ciphertext =
	"FNRHTKRHSEDEJMBOWBDSCSDDXL"
	"ICXULMBYQXWTGUIVNDYZBEQLVH"
	"FFFIDAKDCCJKWGOOUESCYELYMR"
	"AKIUJCUSEAXUQTYKOBVYDYMRBY"
	"WOTQEESCQSMDYDQJNPSWRSUOFM"
	"FJDYXSHCXNHVJVBYMZOZOATHTE"
	"OVLOQWZITHTEAFMKGLASTBZRDM"
	"FRJPKWJOXZXPJCBOVAZEPKAEJP"
	"PSIUJODXTXERWTLTTYMRENBJGT"
	"NMLBDJMYJDDLRCXCQCHYMJMHBE"
	"OLXEUFNJKBPRSHTEYXB";

	const string plaintext = Normalize(
	"Three weeks in. We rise before the sun, and each needle is done by noon."
	"The Whitesmith shows me his technique for purifying his metal before drawing it into a fine wire."
	"He has me repeat the same step four times, with slight variations. Still my hand falters."
	"I am patient, but I know this is not my calling. I have made peace with it and will go home soon.");

	const QuagmireS cipher1 = QuagmireS::QuagmireIII("KRYPTOS", "ANNEAL");
	const HillCipher cipher2("KRYPTOS", "ALCHEMIST");

	const string encoded1 = cipher1.Encode(plaintext);
	const string encoded2 = cipher2.Encode(encoded1);
	if (encoded2 != ciphertext)
		throw runtime_error("PK7 encoding failed.");

	const string decoded2 = cipher2.Decode(ciphertext);
	const string decoded1 = cipher1.Decode(decoded2);
	if (decoded1 != plaintext)
		throw runtime_error("PK7 decoding failed.");

	printf("%s\n\n", decoded1.c_str());
}

#endif
