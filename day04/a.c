#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <stdbool.h>

// For MD5
#include <windows.h>
#include <wincrypt.h>
#define MD5LEN 16
#define MD5_HEX_LENGTH (MD5LEN * 2)
static HCRYPTPROV hProv = 0;
static DWORD cbHash = MD5LEN;
static BYTE rgbHash[MD5LEN];
static CHAR rgbDigits[] = "0123456789abcdef";

static void get_md5(const char *in, char *out) {
	// https://learn.microsoft.com/en-us/windows/win32/seccrypto/example-c-program--creating-an-md-5-hash-from-file-content
	HCRYPTHASH hHash = 0;
	CryptCreateHash(hProv, CALG_MD5, 0, 0, &hHash);
	CryptHashData(hHash, in, strlen(in), 0);
	CryptGetHashParam(hHash, HP_HASHVAL, rgbHash, &cbHash, 0);
	size_t bytes_left = MD5_HEX_LENGTH;
	for (DWORD i = 0; i < cbHash; i++)
    {
		int bytes_written = snprintf(out, bytes_left, "%c%c", rgbDigits[rgbHash[i] >> 4], rgbDigits[rgbHash[i] & 0xf]);
		out += bytes_written;
		bytes_left -= bytes_written;
    }
	CryptDestroyHash(hHash);
}

static int int_to_string(int n, char *out) {
	int index = 10;
	do {
		int r = n % 10;
		n /= 10;
		*(out + index--) = r + '0';
	} while (n != 0);
	return index + 1;
}

void a() {
	char code[16] = "yzbqklnj";
	char buffer[12] = {0};
	char md5[MD5_HEX_LENGTH] = {0};
	int insert_index = strlen(code);

	CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT);

	for (int i = 0; ; i++) {
		int written = int_to_string(i, buffer);
		char* val = buffer + written;
		strncpy(code+insert_index, val, strlen(val));
		get_md5(code, md5);
		bool found = true;		
		for (int j = 0; j < 5; j++) {
			if (md5[j] != '0') {
				found = false;
				break;
			}
		}
		if (found) {
			printf("%d: %s\n", i, md5);
			break;
		}
	}
	
    CryptReleaseContext(hProv, 0);
}
