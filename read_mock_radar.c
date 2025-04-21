#include <stdio.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    char buffer[128];
    int fd = open("/dev/mock_radar", O_RDONLY);
    if (fd < 0) {
        perror("Failed to open /dev/mock_radar");
        return 1;
    }

    int bytes = read(fd, buffer, sizeof(buffer) - 1);
    if (bytes < 0) {
        perror("Read error");
        return 1;
    }

    buffer[bytes] = '\0';
    printf("Radar Data: %s", buffer);
    close(fd);
    return 0;
}