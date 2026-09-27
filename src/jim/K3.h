#ifndef _K3_H
#define _K3_H

#include <stdexcept>
#include "../pipeline.h"
#include "../transposition.h"

void DecodeK3() {
	const string ciphertext =
	"ENDYAHROHNLSRHEOCPTEOIBIDYSHNAIA"
	"CHTNREYULDSLLSLLNOHSNOSMRWXMNE"
	"TPRNGATIHNRARPESLNNELEBLPIIACAE"
	"WMTWNDITEENRAHCTENEUDRETNHAEOE"
	"TFOLSEDTIWENHAEIOYTEYQHEENCTAYCR"
	"EIFTBRSPAMHHEWENATAMATEGYEERLB"
	"TEEFOASFIOTUETUAEOTOARMAEERTNRTI"
	"BSEDDNIAAHTTMSTEWPIEROAGRIEWFEB"
	"AECTDDHILCEIHSITEGOEAOSDDRYDLORIT"
	"RKLMLEHAGTDHARDPNEOHMGFMFEUHE"
	"ECDMRIPFEIMEHNLSSTTRTVDOHW";

	const string plaintext = Normalize(
	"Slowly, desparatly slowly,"
	"the remains of passage debris that encumbered the lower part of the doorway was removed."
	"With trembling hands I made a tiny breach in the upper left-hand corner."
	"And then, widening the hole a little, I inserted the candle and peered in."
	"The hot air escaping from the chamber caused the flame to flicker,"
	"but presently details of the room within emerged from the mist. X"
	"Can you see anything Q");

	RotatingTransposition cipher1(ciphertext.length(), 42);
	RotatingTransposition cipher2(ciphertext.length(), 14);
	Pipeline pipeline({&cipher1, &cipher2});

	const string encoded = pipeline.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("K3 encoding failed.");

	const string decoded = pipeline.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("K3 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
