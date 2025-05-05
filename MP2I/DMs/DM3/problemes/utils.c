#include <string.h>
#include <stdlib.h>
#include <assert.h>
// #include <stdio.h>

void write_f(char* f, char* s, int* k){
	int j = *k;
	for (int i = 0; s[i] != '\0'; i++){
		f[j + i] = s[i];
		(*k)++;
	}
}

char* au_moins_une(char** l, int n){
	assert(n > 0);
	int lenght = 0;
	for (int i = 0; i < n; i++){
		lenght += strlen(l[i]);
	}	
	char* result = malloc(sizeof(char) * (lenght + 3*n));
	result[0] = '(';
	int k = 1;
	write_f(result, l[0], &k);
	for (int i = 1; i < n; i++){
		result[k] = ' ';
		result[k+1] = '|';
		result[k+2] = ' ';
		k += 3;
		write_f(result, l[i], &k);
	}
	result[k++] = ')';
	result[k] = '\0';
	return result;
}


char* au_plus_une(char** l, int n){
	assert(n > 0);
	if (n == 1) {
		return strdup("T");
	}
	int lenght = 0;
	for (int i = 0; i < n; i++){
		lenght += strlen(l[i]);
	}
	char* result = malloc(sizeof(char) * (5 * n * (n-1) + (n-1)*lenght));
	result[0] = '(';
	int k = 1;
	for (int i = 0; i < n - 2; i++){
		for (int j = i+1; j < n; j++){
			result[k++] = '(';
			result[k++] = '~';
			write_f(result, l[i], &k);
			result[k++] = ' ';	
			result[k++] = '|';	
			result[k++] = ' ';	
			result[k++] = '~';
			write_f(result, l[j], &k);
			result[k++] = ')';
			result[k++] = ' ';
			result[k++] = '&';
			result[k++] = ' ';
		}
	}
	result[k++] = '(';
	result[k++] = '~';
	write_f(result, l[n-2], &k);
	result[k++] = ' ';	
	result[k++] = '|';	
	result[k++] = ' ';	
	result[k++] = '~';
	write_f(result, l[n-1], &k);
	result[k++] = ')';
	result[k++] = ')';
	result[k] = '\0';
	return result;
}

int min(int a, int b){
	if (a < b){
		return a;
	} else {
		return b;
	}
}

// int main () {
// 	char* forms[4] = {"(x & ~y)", "y", "z", "(x | y & ~z)"};
// 	// char* phi = au_moins_une(forms, 3);
// 	char* psi = au_plus_une(forms, 4);
// 	printf("%s\n", psi);
// 	free(psi);
// 	return 0;
// }