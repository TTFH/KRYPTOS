#ifndef _PK5_H
#define _PK5_H

#include <stdexcept>
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

	const string PK4 = Normalize(
	"Two years in. The needle's trail led me to a craftsman named the Whitesmith."
	"On the road to his Alpine workshop I reread his perfunctory letters."
	"He met me at the gates and led me to a stone barn stacked with winter fodder."
	"One of his needles is hidden in the barn. I have begun to work.");

	const string plaintext = Normalize(
	"Fourteen days in the barn. I worked in the manner of an archivist:"
	"lifting each bale onto a cloth and examining the straws in rows."
	"The Whitesmith brought food and water but no counsel."
	"This morning, I felt the needle prick my finger, so fine that it drew no blood."
	"I carried it to the Whitesmith, and he took it from me and opened the inner door.");

	ColumnarTransposition cipher1(ciphertext.length(), "TWOYEARS");
	const QuagmireS cipher2 = QuagmireS::QuagmireIII("KRYPTOS", PK4);

	cipher1.FromRows(plaintext);
	cipher1.Encode();
	const string encoded1 = cipher1.FetchByColumns();
	const string encoded2 = cipher2.Encode(encoded1);
	if (encoded2 != ciphertext)
		throw runtime_error("PK5 encoding failed.");

	const string decoded2 = cipher2.Decode(ciphertext);
	cipher1.FromColumns(decoded2);
	cipher1.Decode();
	const string decoded1 = cipher1.FetchByRows();
	if (decoded1 != plaintext)
		throw runtime_error("PK5 decoding failed.");

	printf("%s\n\n", decoded1.c_str());
}

#endif
