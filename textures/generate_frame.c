#include <stdio.h>
#include <stdlib.h>

#define W 64
#define H 64

int main(void) {
    FILE *f = fopen("textures/door_frame.xpm", "w");
    if (!f) return 1;

    fputs("/* XPM */\n", f);
    fputs("static char *door_frame_xpm[] = {\n", f);
    fputs(\"64 64 4 1\",\n", f);
    fputs(\"  c #1A1B26\",\n", f);
    fputs(\". c #414868\",\n", f);
    fputs(\"+ c #00FFBB\",\n", f);
    fputs(\"x c #000000\",\n", f);

    for (int y = 0; y < H; y++) {
        fputs(\"", f);
        for (int x = 0; x < W; x++) {
            if (x < 10) fputc(' ', f);
            else if (x > 50 && x < 54 && y > 10 && y < 54) fputc('+', f);
            else if (y % 16 < 2) fputc('x', f);
            else fputc('.', f);
        }
        if (y == H - 1) fputs(\"\n", f);
        else fputs(\"\",\n", f);
    }

    fputs("};\n", f);
    fclose(f);
    return 0;
}
