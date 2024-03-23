#ifndef _X_UTILS
#define _X_UTILS

#define ARRAY_LEN(a) (sizeof(a)/sizeof(*a))

static wchar_t sample_values[] = L"abcd";
static Sequence sample = { .values = sample_values, .len = ARRAY_LEN(sample_values) - 1 };

#endif // _X_UTILS
