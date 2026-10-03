#ifndef _PK5_H
#define _PK5_H

#include <stdexcept>
#include "PK4.h"
#include "../pipeline.h"
#include "../quagmire.h"
#include "../transposition.h"

void DecodePK5() {
	const string ciphertext =
	"IJQUVJJINKWMJBNJHKZZMTVTUB"
	"FHXZJIUHOVONZNXKFUALEMYWTN"
	"NNILTRNVSXIXIQCLOSFZVZGTHQ"
	"KZFJJHJMJTSEPAMKNMTGPVFWSW"
	"SBSIHOJWNFXDIJPJNOVBWWXJYU"
	"VVAFTIDZISJNCIGHXKLNFEQRDV"
	"YIXUXQIZFNXAKYXIUEVGRBMHWR"
	"FDZSMMDPMKIZNUQUJNXVZTGHCN"
	"AUVIYZCLRAVMJKAOIBOPZTJUPA"
	"CSTFFLERTGBFFNCYTAVIRXXYOX"
	"HCDWHWWKAMQO";

	const string plaintext = Normalize(
	"Fourteen days in the barn. I worked in the manner of an archivist:"
	"lifting each bale onto a cloth and examining the straws in rows."
	"The Whitesmith brought food and water but no counsel."
	"This morning, I felt the needle prick my finger, so fine that it drew no blood."
	"I carried it to the Whitesmith, and he took it from me and opened the inner door.");

	Pipeline pipeline({
		new ColumnarTransposition(ciphertext.length(), "TWOYEARS"),
		new QuagmireIII("KRYPTOS", PK4),
	});

	const string encoded = pipeline.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("PK5 encoding failed.");

	const string decoded = pipeline.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("PK5 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
