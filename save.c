#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "save.h"

int change_save_content_size(struct Save *save) {
    save->capacity *= 2;
    char **temp = (char **)realloc(save->save, save->capacity * sizeof(char *));
    if (temp == NULL) {
        puts("Failed to reallocate memory for the save!");
        return 1;
    }
    save->save = temp;
    return 0;
}

int load_save(const char *path, struct Save *save) {
    save->size = 0;
    save->capacity = 8;
    save->save = (char **)malloc(save->capacity * sizeof(char *));
    if (save->save == NULL) {
        puts("Failed to allocate memory for the save!");
        return 1;
    }

    char *line = NULL;
    size_t len = 0;
    FILE *fptr = fopen(path, "r");
    if (fptr == NULL) {
        puts("Failed to load the save!");
        free(save->save);
        return 1;
    }

    while (getline(&line, &len, fptr) != -1) {
        if (save->size >= save->capacity) {
            if (change_save_content_size(save)) {
                free(line);
                fclose(fptr);
                return 1;
            }
        }
        save->save[save->size] = strdup(line);
        save->size++;
    }

    free(line);
    fclose(fptr);
    return 0;
}

int save_save(const char *path, struct Save *save) {
    FILE *fptr = fopen(path, "w");
    if (fptr == NULL) {
	return 1;
    }

    for (int i = 0; i < save->size; i++) {
	fputs(save->save[i], fptr);
    }
    fclose(fptr);
    return 0;
}

void deinit_save(struct Save *save) {
    for (int i = 0; i < save->size; i++) {
        free(save->save[i]);
    }
    free(save->save);
}

