#ifndef _K3_H
#define _K3_H

#include <stdexcept>
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

	Transposition cipher(ciphertext.length());

	cipher.Resize(42);
	cipher.FromRows(plaintext);
	//cipher.PrintGrid();
	cipher.Rotate(CW);
	cipher.Resize(14);
	//cipher.PrintGrid();
	cipher.Rotate(CW);
	const string encoded = cipher.FetchByRows();
	if (encoded != ciphertext)
		throw runtime_error("K3 encoding failed.");

	cipher.Resize(24);
	cipher.FromRows(ciphertext);
	cipher.Rotate(CCW);
	cipher.Resize(8);
	cipher.Rotate(CCW);
	const string decoded = cipher.FetchByRows();
	if (decoded != plaintext)
		throw runtime_error("K3 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
