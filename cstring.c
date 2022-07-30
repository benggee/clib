#include <string.h>
#include <stdlib.h>

// Split string by spit
char  **str_split(char *str, const char spit, const int size, const int len) 
{
	char **strs = (char **)malloc(sizeof(char *) * len * size);

	int slen = (int)strlen(str);
	int idx = 0;
	int readidx = 0;

	for (int i = 0; i < slen; i++) {
		char readbuf[1024];		
		if (str[i] == spit) {
			if (idx >= size) {
				break;
			}
		
			readbuf[++readidx] = '\0';
			strs[idx] = malloc(sizeof(char) * 1024);
			strcpy(strs[idx], readbuf);
			memset(readbuf, 0, sizeof(readbuf));
			idx++;
			readidx = 0;

			continue;
		} 
		if (str[i] == '\0') {
			break;
		}

		if (readidx > 1024) {
			for (int j = 0; j < idx; j++) {
				free(strs[j]);
			}

			free(strs);
			return NULL;
		}
		
		readbuf[readidx] = str[i];
		readidx++;
	}
	
	if (idx != size) {
		return NULL;
	}

	return strs;
}
