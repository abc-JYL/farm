struct Save {
    enum {
	Name = 0
    } index;
    char **save;
    int size;
    int capacity;
};

int load_save(const char *path, struct Save *save);
int save_save(const char *path, struct Save *save);
void deinit_save(struct Save *save);

