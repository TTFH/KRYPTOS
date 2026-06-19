#include <math.h>
#include <stdio.h>

#include "utils.h"

void PrintFactors(int n) {
	printf("%d: ", n);
	for (int i = 1; i <= sqrt(n); i++)
		if (n % i == 0)
			printf("%s%d x %d", (i > 1) ? ", " : "", i, n / i);
	printf("\n\n");
}

string Normalize(const string& text) {
	string result;
	result.reserve(text.size());
	for (char c : text) {
		if (isalpha(c))
			result += toupper(c);
		else if (c == '?')
			result += c;
	}
	return result;
}

wstring NormalizeW(const wstring& text) {
	wstring result;
	result.reserve(text.length());
	for (wchar_t c : text) {
		if ((c >= L'A' && c <= L'Z') || (c >= L'a' && c <= L'z'))
			result += towupper(c);
		else if (c >= L'\u0410' && c <= L'\u042F')
			result += c;
		else if (c >= L'\u0430' && c <= L'\u044F')
			result += c - L'\u0430' + L'\u0410';
	}
	return result;
}
