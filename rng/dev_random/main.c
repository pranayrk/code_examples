#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

int main() {
    int random_data_fd;
    unsigned int random_number;

    // Open /dev/urandom for reading
    random_data_fd = open("/dev/urandom", O_RDONLY);
    if (random_data_fd == -1) {
        perror("Error opening /dev/urandom");
        return 1;
    }

    // Read sizeof(unsigned int) bytes into random_number
    if (read(random_data_fd, &random_number, sizeof(random_number)) == -1) {
        perror("Error reading from /dev/urandom");
        close(random_data_fd);
        return 1;
    }

    // Close the file descriptor
    close(random_data_fd);

    printf("Random number from /dev/urandom: %u\n", random_number);

    // If you need a random number within a specific range,
    // you can use the modulo operator:
    int min_val = 1;
    int max_val = 100;
    int ranged_random_number = (random_number % (max_val - min_val + 1)) + min_val;
    printf("Random number in range [%d, %d]: %d\n", min_val, max_val, ranged_random_number);

    return 0;
}
