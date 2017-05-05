#include <stdio.h>
#include <assert.h>
#include "memfile.h"
#include "tst_data.h"

#define LEN 561351

int main(int argc, char* argv[])
{
	FILE* f = fopen("tst_data.dat", "rb");
	if (!f) {
		printf("error: open tst_data.dat failed.\n");
	}

	MEMFILE* mf = mfopen(tst_data, GetTstDataSize());
	if (!mf) {
		printf("error: open tst_data memory array failed.\n");
	}
	
	assert(ftell(f) == mftell(mf));

	fseek(f, 0, SEEK_END);
	mfseek(mf, 0, SEEK_END);
	assert(ftell(f) == mftell(mf));


	int len = ftell(f);
	printf("file len=%d\n", len);

	// case 1
	rewind(f);
	mfrewind(mf);

	int i = 0;
	for (; i < len; i++) {
		char cf, cmf;
		int ret0 = fread(&cf, sizeof(char), 1, f);
		int ret1 = mfread(&cmf, sizeof(char), 1, mf);
		assert(ret0 == ret1);
		assert(ftell(f) == mftell(mf));
		assert(cf == cmf);
	}

	// case 2
	rewind(f);
	mfrewind(mf);

	assert(ftell(f) == mftell(mf));

	for (i = 0; i < len && i + 1 < len;) {
		short i16_f, i16_mf;
		int ret0 = fread(&i16_f, sizeof(short), 1, f);
		int ret1 = mfread(&i16_mf, sizeof(short), 1, mf);
		assert(ret0 == ret1);
		assert(i16_f == i16_mf);
		i += 2;
	}

	// case 3
#if 1
	rewind(f);
    mfrewind(mf);
	char mf2arr[LEN];
	memset(mf2arr, 0, LEN);
	MEMFILE* mf2 = mfopen(mf2arr, LEN);
	for (i = 0; i < len;) {
		char cmf;
		int ret1 = mfread(&cmf, sizeof(char), 1, mf);
		assert(ret1);
		mfwrite(&cmf, sizeof(char), 1, mf2);
		i++;
		assert(mftell(mf2) == i);
    }
	mfclose(mf2, False);
#endif


	fclose(f);
	mfclose(mf, False);

	printf("tst......OK.\n");

	return 0;
}
