#include "leetcode.h"
#include <assert.h>
#include <string.h>



int main(void)
{
	char *res;
	
	res = zigzag_convert("PAYPALISHIRING", 3);
	assert(strcmp(res, "PAHNAPLSIIGYIR") == 0);

	res = zigzag_convert("PAYPALISHIRING", 4);
	assert(strcmp(res, "PINALSIGYAHRPI") == 0);

	return 0;
}
