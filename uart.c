#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    struct termios oldtio, newtio;
    int fd;
    char c;

    // Open the serial device
    fd = open("/dev/ttyS0", O_RDWR | O_NOCTTY);
    if (fd < 0) {
        perror("open");
        exit(1);
    }

    // Save current serial port settings
    tcgetattr(fd, &oldtio);

    // Set new serial port settings
    newtio.c_cflag = B9600 | CS8 | CLOCAL | CREAD;
    newtio.c_iflag = IGNPAR;
    newtio.c_oflag = 0;
    newtio.c_lflag = 0;
    newtio.c_cc[VMIN] = 1;
    newtio.c_cc[VTIME] = 0;
    tcflush(fd, TCIFLUSH);
    tcsetattr(fd, TCSANOW, &newtio);

    // Read characters from the serial device
    while (1) {
        if (read(fd, &c, 1) == '[') {
                    read(fd, &c, 1);
                    if (c == 'A') {
                        printf("Up arrow key pressed\n");
                    } else if (c == 'B') {
                        printf("Down arrow key pressed\n");
                    }
            }
        }
    

    // Restore original serial port settings and close the serial device
    tcsetattr(fd, TCSANOW, &oldtio);
    close(fd);

    return 0;
}

