struct LangPack {
    enum {
	INTRO = 0
    } index;
    char **langpack;
    int size;
    int capacity;
};

int load_langpack(const char *path, struct LangPack *langpack);
void deinit_langpack(struct LangPack *langpack);

