#include <cstdio>
#include <cstdlib>
#include <cstring>
#include "sha256.h"
#include "aes.h"

int main(int argc, char *argv[]) {
	if (argc != 4) {
		printf ("Usage: %s [encrypt|decrypt] filename password\n", argv[0]);
		return 1;
	}
	int i, ch;
	int encrypt=0, decrypt=0;
	char *filename = NULL, *password = NULL;
	uint8_t buf[1024], out[1024] = {0};
	char outname[256];
	uint8_t hash[32];
	sha256_context ctx;
	FILE *fin, *fout;
	int in_count, out_count, real_out;
	if (!strcmp(argv[1], "encrypt"))
		encrypt = 1;
	if (!strcmp(argv[1], "decrypt"))
		decrypt = 1;
	filename = argv[2];
	password = argv[3];
	if (!encrypt ^ decrypt) {
		printf("%s: Must specify one of encrypt/decrypt\n", argv[0]);
		return 1;
	}
	strcpy(outname, filename);
	strcat(outname, ".ans");
	sha256_init(&ctx);
	sha256_hash(&ctx, (uint8_t *)password, (uint32_t)strlen(password));
	sha256_done(&ctx, hash);
	fin = fopen(filename, "rb");
	fout = fopen(outname, "wb+");
	if (!fin || !fout) {
		printf("File read error!");
		return 1;
	}
	if (encrypt) {
		while (in_count = fread(buf, 1, 512, fin)) {
			fwrite(&in_count, sizeof(int), 1, fout);
			if (AESEncrypt(buf, out, in_count, &out_count, hash, 32)) {
				printf("encrypt error!\n");
				return 1;
			}
			real_out = fwrite(out, 1, out_count, fout);
			if (real_out != out_count) {
				printf("file output error!\n");
				return 1;
			}
		}
	}
	else {
		while (fread(&out_count, sizeof(int), 1, fin)) {
			in_count = fread(buf, 1, 512, fin);
			if (AESDecrypt(buf, out, in_count, &out_count, hash, 32)) {
				printf("decrypt error!\n");
				return 1;
			}
			real_out = fwrite(out, 1, out_count, fout);
			if (real_out != out_count) {
				printf("file output error!\n");
				return 1;
			}
		}
	}
	fclose(fin);
	fclose(fout);
    return 0;
}