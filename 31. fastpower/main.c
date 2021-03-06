#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h> 
#include <time.h> 


void skip_garbage() {
	int ch;
	do {
		ch = getchar();
	} while (ch != '\n');
}

int read_int(const char * request) {
	for (;;) {
		printf("%s", request);
		int num;
		int res = scanf("%d", &num);
		skip_garbage();
		if (res == 1) {
			return num;
		}
	}
}

double read_double(const char * request) {
	for (;;) {
		printf("%s", request);
		double num;
		int res = scanf("%lg", &num);
		skip_garbage();
		if (res == 1) {
			return num;
		}
	}
}

double fastpow(double x, int n){
	if (x == 0){
		return 0;
	}
	if (n < 0){
		return 1/fastpow(x, -n);
	}
	double result = 1.0;
	while (n != 0){
		if (n % 2 == 1){
			result *= x;
		}
		x *= x;
		n /= 2;
	}
	return result;
}

int main(){
	printf("Fast power\n");
	double x = read_double("Base is ");
	int n = read_int("Power is ");
	if ((n <= 0) && (x == 0)){
		printf("WAT??\n");
		return 0;
	}

	printf("%g^%d=%g\n", x, n, fastpow(x, n));

	for (int i = 0; i < 10; i++) {
		printf("2^%d: %g\n", i, fastpow(2, i));
	}

	return 0;
}