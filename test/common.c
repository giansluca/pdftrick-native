#include <sys/stat.h>

void make_dir(char *path) {
    struct stat stats;

#ifdef __APPLE__
    if (stat(path, &stats) == -1) {
        mkdir(path, 0700);
    }
#elif _WIN32
    if (stat(path, &stats) == -1) {
        mkdir(path);
    }
#elif __linux__
// do linux specific stuff
#else
// error
#endif
}
