// These are needed to make newlib happy enough to compile. If you want printf
// and similar to go to a UART then you'd have to change these. Right now, I
// don't need that so they are just cute little stubs.

int _read(int file, char *ptr, int len) { return -1; }
int _write(int file, char *ptr, int len) { return -1; }