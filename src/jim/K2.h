#ifndef _K2_H
#define _K2_H

#include <stdexcept>
#include "../quagmire.h"

void DecodeK2() {
	const string ciphertext =
	"VFPJUDEEHZWETZYVGWHKKQETGFQJNCE"
	"GGWHKK?DQMCPFQZDQMMIAGPFXHQRLG"
	"TIMVMZJANQLVKQEDAGDVFRPJUNGEUNA"
	"QZGZLECGYUXUEENJTBJLBQCRTBJDFHRR"
	"YIZETKZEMVDUFKSJHKFWHKUWQLSZFTI"
	"HHDDDUVH?DWKBFUFPWNTDFIYCUQZERE"
	"EVLDKFEZMOQQJLTTUGSYQPFEUNLAVIDX"
	"FLGGTEZ?FKZBSFDQVGOGIPUFXHHDRKF"
	"FHQNTGPUAECNUVPDJMQCLQUMUNEDFQ"
	"ELZZVRRGKFFVOEEXBDMVPNFQXEZLGRE"
	"DNQFMPNZGLFLPMRJQYALMGNUVPDXVKP"
	"DQUMEBEDMHDAFMJGZNUPLGESWJLLAETG";

	const string plaintext = Normalize(
	"It was totally invisible, How's that possible? They used the Earths magnetic field X"
	"The information was gathered and transmitted undergruund to an unknown location X"
	"Does Langley know about this? They should. It's buried out there somewhere X"
	"Who knows the exact location? Only W.W. This was his last message: X"
	"Thirty eight degrees fifty seven minutes six point five seconds north"
	"seventy seven degrees eight minutes forty four seconds west X"
	"Layer two.");

	QuagmireIII cipher("KRYPTOS", "ABSCISSA");

	const string encoded = cipher.Encode(plaintext);
	if (encoded != ciphertext)
		throw runtime_error("K2 encoding failed.");

	const string decoded = cipher.Decode(ciphertext);
	if (decoded != plaintext)
		throw runtime_error("K2 decoding failed.");

	printf("%s\n\n", decoded.c_str());
}

#endif
