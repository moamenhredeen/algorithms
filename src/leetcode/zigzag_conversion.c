#include "leetcode.h"

char* zigzag_convert(char* s, int numRows) {
	char *res = malloc(strlen(s));
	for (int i = 0; s[i] != '\0'; ++i)
	{
		for (int j = 0; j < numRows; ++j)
		{
			res[i] = s[i];
		}
	}
	return res;
}
