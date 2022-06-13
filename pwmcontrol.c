#include <stdio.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


int checkIfFileExists(const char * filename)
{
    FILE *file;
    if (file = fopen(filename, "r"))
    {
        fclose(file);
        return 0;
    }

    return 1;
}

// export the gpio pin 412
int export_gpio()
{
        printf("exportting pwm\n");
        // Export the desired pin by writing to /sys/class/gpio/export
        int fd = open("/sys/class/pwm/pwmchip3/export", O_WRONLY);
        if (fd == -1) {
                perror("Unable to open /sys/class/pwm/pwmchip3/export");
                exit(1);
        }

        if (write(fd, "0", 1) != 1) {
                perror("Error writing to /sys/class/pwm/pwmchip3/export");
                close(fd);
                exit(1);
        }
        close(fd);

        // period
        fd = open("/sys/class/pwm/pwmchip3/pwm0/period", O_WRONLY);
        if (fd == -1) {
                perror("Unable to open /sys/class/pwm/pwmchip3/pwm0/period");
                exit(1);
        }

        if (write(fd, "1000000", 7) != 7) {
                perror("Error writing to /sys/class/pwm/pwmchip3/pwm0/period");
                close(fd);
                exit(1);
        }
        close(fd);

        // duty cycle
        fd = open("/sys/class/pwm/pwmchip3/pwm0/duty_cycle", O_WRONLY);
        if (fd == -1) {
                perror("Unable to open /sys/class/pwm/pwmchip3/pwm0/duty_cycle");
                exit(1);
        }

        if (write(fd, "1000000", 7) != 7) {
                perror("Error writing to /sys/class/pwm/pwmchip3/pwm0/duty_cycle");
                close(fd);
                exit(1);
        }
        close(fd);

}

int main(){
        export_gpio();
}