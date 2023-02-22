#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <termios.h>
#include <fcntl.h>

int main(int argc, char *argv[]) {
    struct termios oldtio, newtio;
    int fd;
    char c[3];

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
    
	while (1) 
	{
		read(fd,c,3); 
		printf("Tecla 1: %s", c);	
		switch(c[0])
		{
			case '\e':
				printf("Tecla 2: %d %c", c[1],c[1]);	
				if(c[1] == '[')
				{
					printf("Tecla 3: %d %c", c[2],c[2]);	
					if(c[2] == 'A')
						printf("UP arrow key\n");

					if(c[2] == 'B')
						printf("DOWN arrow key\n");
				}
				break;
		}
	}

    // Restore original serial port settings and close the serial device
    tcsetattr(fd, TCSANOW, &oldtio);
    close(fd);

    return 0;
}

