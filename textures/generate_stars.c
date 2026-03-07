#include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define WIDTH 4000
#define HEIGHT 2000
#define STARS 15000

int main(void) {
    srand(time(NULL));
    FILE *f = fopen("textures/skybox.xpm", "w");
    if (!f) return 1;

    fprintf(f, "/* XPM */\n");
    fprintf(f, "static char *skybox_xpm[] = {\n");
    fprintf(f, "\"%d %d 5 1\",\n", WIDTH, HEIGHT);
    fprintf(f, "\"  c #000000\",\n");
    fprintf(f, "\". c #FFFFFF\",\n");
    fprintf(f, "\"+ c #FFFACD\",\n");
    fprintf(f, "\"x c #ADD8E6\",\n");
    fprintf(f, "\"o c #1A1B26\",\n");

    char *row = malloc(WIDTH + 1);
    for (int y = 0; y < HEIGHT; y++) {
        for (int x = 0; x < WIDTH; x++) {
            if ((rand() % 3000) == 0) row[x] = 'o';
            else row[x] = ' ';
        }
        // Inject some stars
        for (int i = 0; i < (STARS / HEIGHT); i++) {
            int x = rand() % WIDTH;
            int type = rand() % 10;
            if (type < 7) row[x] = '.';
            else if (type < 9) row[x] = '+';
            else row[x] = 'x';
        }
        fprintf(f, "\"%.*s\"%s\n", WIDTH, row, (y == HEIGHT - 1) ? "" : ",");
    }
    free(row);

    fprintf(f, "};\n");
    fclose(f);
    return 0;
}
