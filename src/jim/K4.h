#ifndef _K4_H
#define _K4_H

#include <map>
#include <stdexcept>
#include "../quagmire.h"

// This part has been left unsolved as an exercise for the reader.
void DecodeK4() {
	const string ciphertext =
	"OBKR"
	"UOXOGHULBSOLIFBBWFLRVQQPRNGKSSO"
	"TWTQSJQSSEKZZWATJKLUDIAWINFBNYP"
	"VTTMZFPKWGDKZXTJCDIGKUHUAUEKCAR";

	const map<string, string> clues = {
		{"EASTNORTHEAST", "FLRVQQPRNGKSS"},
		{"BERLINCLOCK", "NYPVTTMZFPK"},
	};
	string decoded = string(ciphertext.length(), '-');
	for (const auto& [pt, ct] : clues) {
		const size_t pos = ciphertext.find(ct);
		if (pos != string::npos)
			for (size_t i = 0; i < ct.length(); i++)
				decoded[pos + i] = pt[i];
	}
	printf("%s\n\n", decoded.c_str());
}

#endif
