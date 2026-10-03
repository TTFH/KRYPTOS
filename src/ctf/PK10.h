#ifndef _PK10_H
#define _PK10_H

#include <stdexcept>
#include "PK4.h"
#include "../pipeline.h"
#include "../quagmire.h"
#include "../transposition.h"

void DecodePK10() {
	const string ciphertext =
	"UBINFYJSFQXQVRLJJAJDGBXIWK"
	"DMAREZTGSHQWRXCHEPCLYSDNGY"
	"RRBTCVOZJYVLYWREJTCDOYVEYC"
	"JJVZKRMKTRPGVHRWMJSRCSHXZM"
	"JEVQKJYJJAYZKDFQBGRSWXATJM"
	"EXKFXAXKSIZXOERFESNVCGCNRH"
	"EOBCNCBUPXTJJRCIMDMRUVZWRD"
	"RRFXAPGPIGSPLILFIZSTDZYOVQ"
	"GGDFUFZPUOJPJVWREUVRQIYPCE"
	"HGYUZUKWTFXELUNOKBANZFTFRM"
	"XZSXXQSBGPCWGXPFSCANSVUYLM"
	"TZIRCCCJJPBQAEPWVCDIMLOPOX"
	"QEGJKVQIVHEFAPQMVCYSQAFKCT"
	"YTPAOOJZCWIPGDPAFTINBFFHVX"
	"YEQXCEIDJJOUABBAHSWKHGMLJB"
	"XDSQEFBBDLTLJPLZPIPPTRGDRZ"
	"IZPUPYJODOCSOYCZZWTKYWMBQT"
	"FMFEQZWVPQYLJTMEYKYBNOPEPU"
	"MHCFJSLFWOISWLKFFABTYFQDTE"
	"QBDELIEOZQ";

	const string plaintext = Normalize(
	"I have not read the strand."
	"The needle was as fine as promised, but my hand was not fit to wield it, and the knot refused to yield."
	"Pellegrin and the Whitesmith tried to teach me, but when the test came I failed them both."
	"Had I stayed with the Whitesmith and learned the discipline he taught,"
	"those years would have shaped my hands into instruments worthy of the needle and the knot,"
	"and at last given me the location of the archive."
	"Pellegrin hid it for only such a successor, through patience, discipline, and true craft."
	"To you who have unraveled my messages, your hand is the needle I have finally forged, and I leave the knot to you.");

	Pipeline pipeline({
		new QuagmireIII("KRYPTOS", "PROVENANCE"),

		new ColumnarTransposition(ciphertext.length(), "MARGINS"),

		new QuagmireIII("KRYPTOS", "ORDINATE"),
		new QuagmireIII("KRYPTOS", "PENTIMENTO"),

		new ColumnarTransposition(ciphertext.length(), "UNDERLAY"),
		new QuagmireIII("KRYPTOS", "OCHRE"),
		new QuagmireIII("KRYPTOS", "VERDIGRIS"),

		new ColumnarTransposition(ciphertext.length(), "TWOYEARS"),
		new QuagmireIII("KRYPTOS", PK4),

		new ColumnarTransposition(ciphertext.length(), "HANDIWORK"),
		new ColumnarTransposition(ciphertext.length(), "SMITHWORK"),
		new QuagmireIII("KRYPTOS", "PORTAL"),

		new QuagmireIII("KRYPTOS", "ANNEAL"),
		new HillCipher("KRYPTOS", "ALCHEMIST"),

		new QuagmireIII("KRYPTOS", "METE"),
		new QuagmireIII("KRYPTOS", "METER"),
		new QuagmireIII("KRYPTOS", "METIER"),
		new QuagmireIII("KRYPTOS", "MASTERY"),

		new QuagmireIII("KRYPTOS", "CLEPSYDRA"),
		new SpiralTransposition(ciphertext.length(), 12),
		new ColumnarTransposition(ciphertext.length(), "BEAMWORK"),
	});

	const string encoded = pipeline.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("PK10 encoding failed.");

	const string decoded = pipeline.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("PK10 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
