extern void greet(const char *name);

int main(int argc, char *argv[]) {
    for (int i = 1; i < argc; i++) {
    	greet(argv[i]);
    }

    return 0;
}
