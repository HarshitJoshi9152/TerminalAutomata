#include <wchar.h>
#include <locale.h>
#include <stdint.h>
int main() {
    setlocale(LC_CTYPE, "");
    wprintf(L"%lc", L'█');
    wprintf(L"%zu\n", sizeof(long));
    wprintf(L"%zu\n", sizeof(wchar_t));
    wprintf(L"\x1b[91mHarhsit\n");
	wprintf(L"\x1b[%d;%dH", (uint32_t)10,(uint32_t)10);
}

// learn about
/*
    wchar_t usecase !!! (wide characters [16 bit usually])
    size_t
    ptrdiff_t
        setlocale
        wprintf
            used with L"" (wchar_t strings)
    %q and %zu and they are more format specifiers
*/