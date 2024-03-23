#ifndef _X_UTILS
#define _X_UTILS

#define SAMPLE_SEQUENCE L"thequickbrownfoxjumpsoverlazydog"
#define STR_LEN(str) ((sizeof(str)/sizeof(str[0])) - 1)

static Sequence sample = { SAMPLE_SEQUENCE, STR_LEN(SAMPLE_SEQUENCE) };

#endif // _X_UTILS
