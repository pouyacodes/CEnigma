#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define ROTOR_RIGHT_SEQ 10
#define ROTOR_MIDDLE_SEQ 2
#define ROTOR_LEFT_SEQ 9

struct Rotor;

void rotor_init(struct Rotor*, size_t);
void rotor_rotate(struct Rotor*, size_t);
char rotor_getc(struct Rotor*, char);
char rotor_getcr(struct Rotor*, char);
void rotors_rotation(size_t);
char reflector(char);
char encodec(char);
void encodes(const char*, size_t, char*);


struct Rotor {

	char sequences[26];
	size_t rotations;

} rotors[3];

void rotor_init(struct Rotor* rotor, size_t init_rotation) {
	
	for (char c = 'a'; c <= 'z'; ++c)
		rotor->sequences[c - 97] = c;
	
	rotor_rotate(rotor, init_rotation);
}
	
void rotor_rotate(struct Rotor* rotor, size_t rotate_count) {
	
	rotor->rotations = rotate_count;

	for (size_t i = 0; i < rotate_count; ++i) {

		char first = rotor->sequences[0];

		for (size_t j = 0; j < 25; ++j)
			rotor->sequences[j] = rotor->sequences[j + 1];
		
		rotor->sequences[25] = first;
	}

}

char rotor_getc(struct Rotor* rotor, char c) {
	return rotor->sequences[c - 97];
}

char rotor_getcr(struct Rotor* rotor, char c) {

	for (size_t i = 0; i < 26; ++i) {

		if (rotor->sequences[i] == c)
			return i + 97;
	}

}

void rotors_rotation(size_t rotor_no) {

	if (rotor_no >= 3) {

		for (size_t i = 0; i < 3; ++i)
			rotor_rotate(&rotors[i], 0);
		
		return;
	}
	

	struct Rotor *rotor = &rotors[rotor_no];
	if (rotor->rotations == 25)
		rotors_rotation(rotor_no + 1);
	else {
		rotor_rotate(rotor, rotor->rotations + 1);
		return;
	}

}

char reflector(char c) {
	return 'z' - c + 'a';
}

char encodec(char c) {
	char v = tolower(c);
	
	for (size_t i = 0; i < 3; ++i)
		v = rotor_getc(&rotors[i], v);

	v = reflector(v);
	
	for (size_t i = 2; i >= 0; --i)
		v = rotor_getcr(&rotors[i], v);
	
	rotors_rotation(0);
	
	return islower(c) ? v : toupper(v);
}

void encodes(const char* plain, size_t lenght, char* cipher) { 

	for (size_t i = 0; i < lenght; ++i)
		cipher[i] = isalpha(plain[i]) ? encodec(plain[i]) : plain[i];
	
	cipher[lenght] = '\0';
}

int main(int argc, const char* argv[]) {
	
	rotor_init(&rotors[0], ROTOR_RIGHT_SEQ);
	rotor_init(&rotors[1], ROTOR_MIDDLE_SEQ);
	rotor_init(&rotors[2], ROTOR_LEFT_SEQ);

	const char* plain = (argc > 1 ? argv[1] : "Hello, world!");
	size_t plain_lenght = strlen(plain);
	char* cipher = (char*) malloc(plain_lenght + 1);
	encodes(plain, plain_lenght, cipher);
	puts(cipher);

	return 0;
}