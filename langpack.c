#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "langpack.h"

int change_langpack_content_size(struct LangPack *langpack) {
    langpack->capacity *= 2;
    char **temp = (char **)realloc(langpack->langpack, langpack->capacity * sizeof(char *));
    if (temp == NULL) {
        puts("Failed to reallocate memory for the language pack!");
	return 1;
    }
    langpack->langpack = temp;
    return 0; 
}

int load_langpack(const char *path, struct LangPack *langpack) {
    langpack->size = 0;
    langpack->capacity = 8;
    langpack->langpack = (char **)malloc(langpack->capacity * sizeof(char *));
    if (langpack->langpack == NULL) {
        puts("Failed to allocate memory for the language pack!");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL) {
        puts("Failed to load the language pack!");
        free(langpack->langpack);
        return 1;
    }

    while (getline(&line, &len, fptr) != -1) {
        if (langpack->size >= langpack->capacity) {
	    if (change_langpack_content_size(langpack)) {
		free(line);
		fclose(fptr);
		return 1;
	    }
	}
        langpack->langpack[langpack->size] = strdup(line);
        langpack->size++;
    }

    free(line);
    fclose(fptr);
    return 0;
}

void deinit_langpack(struct LangPack *langpack) {
    for (int i = 0; i < langpack->size; i++) {
        free(langpack->langpack[i]);
    }
    free(langpack->langpack);
}

