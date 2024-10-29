#include "langpack.h"
#include "save.h"
#include <stdio.h>

int main(void) {
    struct LangPack langpack;
    if (load_langpack("langpack", &langpack)) {
	return 1;
    }

    for (int i = 0; i < langpack.size; i++) {
	printf("%s", langpack.langpack[i]);
    }

    struct Save save;
    if (load_save("save", &save)) {
	return 1;
    }

    for (int i = 0; i < save.size; i++) {
	printf("%s", save.save[i]);
    }

    deinit_save(&save);
    deinit_langpack(&langpack);
    return 0;
}

