#include <stdio.h>

#include <io.h>
#include <fcntl.h>
#include <windows.h>

#include "src/aca/Q1.h"
#include "src/aca/Q2.h"
#include "src/aca/Q3.h"
#include "src/aca/Q4.h"

#include "src/jim/K1.h"
#include "src/jim/K2.h"
#include "src/jim/K3.h"
#include "src/jim/K4.h"
#include "src/jim/K5.h"

#include "src/jim/CP1.h"
#include "src/jim/CP2.h"
/*
#include "src/ctf/PK1.h"
#include "src/ctf/PK2.h"
#include "src/ctf/PK3.h"
#include "src/ctf/PK4.h"
#include "src/ctf/PK5.h"
#include "src/ctf/PK6.h"
#include "src/ctf/PK7.h"
#include "src/ctf/PK8.h"
*/
int main() {
	DecodeQ1();
	DecodeQ2();
	DecodeQ3();
	DecodeQ4();

	DecodeK1();
	DecodeK2();
	DecodeK3();
	DecodeK4();
	DecodeK5();
/*
	DecodePK1();
	DecodePK2();
	DecodePK3();
	DecodePK4();
	DecodePK5();
	DecodePK6();
	DecodePK7();
	DecodePK8();
*/
	_setmode(_fileno(stdout), _O_U16TEXT);
	DecodeCP1();
	DecodeCP2();
	return 0;
}
