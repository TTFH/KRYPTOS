#ifndef _PK7_H
#define _PK7_H

#include <stdexcept>
#include "../pipeline.h"
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

	QuagmireIII cipher1("KRYPTOS", "ANNEAL");
	HillCipher cipher2("KRYPTOS", "ALCHEMIST");
	Pipeline pipeline({&cipher1, &cipher2});

	const string encoded = pipeline.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("PK7 encoding failed.");

	const string decoded = pipeline.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("PK7 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
