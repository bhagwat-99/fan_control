#include <errno.h>
#include <fcntl.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>


// check if file already exist to avoid gpio export error
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
        char * filename = "/sys/class/gpio/gpio412";
       
        if(checkIfFileExists(filename))
        {
                // Export the desired pin by writing to /sys/class/gpio/export
                int fd = open("/sys/class/gpio/export", O_WRONLY);
                if (fd == -1) {
                        perror("Unable to open /sys/class/gpio/export");
                        return -1;
                }

                if (write(fd, "412", 3) != 3) {
                        perror("Error writing to /sys/class/gpio/export");
                        close(fd);
                        return -1;
                }

                close(fd);

        }
        return 0;
}

int unexport_gpio()
{
        char * filename = "/sys/class/gpio/gpio412";
       
       //if file exist unexport int
        if(checkIfFileExists(filename) == 0)
        {
                 // Unexport the pin by writing to /sys/class/gpio/unexport

                int fd = open("/sys/class/gpio/unexport", O_WRONLY);
                if (fd == -1) {
                        perror("Unable to open /sys/class/gpio/unexport");
                        return -1;
                }

                if (write(fd, "412", 3) != 3) {
                        perror("Error writing to /sys/class/gpio/unexport");
                        return -1;
                }

                close(fd);
                return 0;

        }
        return 0;
}


// set the direction of gpio 412
int set_gpio_direction()
{
    // Set the pin to be an output by writing "out" to /sys/class/gpio/gpio24/direction
    int fd = open("/sys/class/gpio/gpio412/direction", O_WRONLY);
    if (fd == -1) {
        perror("Unable to open /sys/class/gpio/gpio412/direction");
        return -1;
    }

    if (write(fd, "out", 3) != 3) {
        perror("Error writing to /sys/class/gpio/gpio412/direction");
        return -1;
    }

    close(fd);
    return 0;
}

int read_temp()
{
    char buf[20];
    int core_temp = 0;

    // read temperature of thermal zone 0
    char * filepath = "/sys/devices/virtual/thermal/thermal_zone0/temp";
    char * MODE = "r";
    FILE* fd = fopen(filepath, MODE);
    if(fd == NULL) {
        printf("Unable to open %s",filepath);
        return -1;
    }
    fgets(buf,10,fd);
    int temp = atoi(buf);
    if(core_temp < temp)
    {
            core_temp = temp;
    }
    fclose(fd);

    // read temperature of thermal zone 1
    filepath = "/sys/devices/virtual/thermal/thermal_zone1/temp";
    MODE = "r";
    fd = fopen(filepath, MODE);
    if(fd == NULL) {
        printf("Unable to open %s",filepath);
        return -1;
    }
    fgets(buf,10,fd);
    temp = atoi(buf);
    if(core_temp < temp)
    {
            core_temp = temp;
    }
    fclose(fd);



    // read temperature of thermal zone 2
    filepath = "/sys/devices/virtual/thermal/thermal_zone2/temp";
    MODE = "r";
    fd = fopen(filepath, MODE);
    if(fd == NULL) {
        printf("Unable to open %s",filepath);
        return -1;
    }
    fgets(buf,10,fd);
    temp = atoi(buf);
    if(core_temp < temp)
    {
            core_temp = temp;
    }
    fclose(fd);


    // read temperature of thermal zone 3
    filepath = "/sys/devices/virtual/thermal/thermal_zone3/temp";
    MODE = "r";
    fd = fopen(filepath, MODE);
    if(fd == NULL) {
        printf("Unable to open %s",filepath);
        return -1;
    }
    fgets(buf,10,fd);
    temp = atoi(buf);
    if(core_temp < temp)
    {
            core_temp = temp;
    }
    fclose(fd);


    // read temperature of thermal zone 4
    filepath = "/sys/devices/virtual/thermal/thermal_zone4/temp";
    MODE = "r";
    fd = fopen(filepath, MODE);
    if(fd == NULL) {
        printf("Unable to open %s",filepath);
        return -1;
    }
    fgets(buf,10,fd);
    temp = atoi(buf);
    if(core_temp < temp)
    {
            core_temp = temp;
    }
    fclose(fd);



    // read temperature of thermal zone 5
    filepath = "/sys/devices/virtual/thermal/thermal_zone5/temp";
    MODE = "r";
    fd = fopen(filepath, MODE);
    if(fd == NULL) {
        printf("Unable to open %s",filepath);
        return -1;
    }
    fgets(buf,10,fd);
    temp = atoi(buf);
    if(core_temp < temp)
    {
            core_temp = temp;
    }
    fclose(fd);


    return core_temp;
}

int fan_on()
{
        // turn fan off
        int fd = open("/sys/class/gpio/gpio412/value", O_WRONLY);
        if (fd == -1)
        {
                perror("Unable to open /sys/class/gpio/gpio412/value");
                return -1;
        }
        if (write(fd, "1", 1) != 1) {
            perror("Error : turning on fan");
            close(fd);
            return -1;
        }

        return 0;
}

int fan_off()
{
        // turn fan off
        int fd = open("/sys/class/gpio/gpio412/value", O_WRONLY);
        if (fd == -1)
        {
                perror("Unable to open /sys/class/gpio/gpio412/value");
                return -1;
        }
        if (write(fd, "0", 1) != 1) {
            perror("Error : turning off fan");
            close(fd);
            return -1;
        }

        return 0;
}

int control_fan()
{
        int core_temp;
        if(core_temp = read_temp() == -1)
        {
                return -1;
        }

        if(core_temp < 70000)
        {
                // turn fan off
                fan_on();
        }
        else if(core_temp > 75000)
        {
                //turn on fan
                fan_off();
        }
}

int main()
{
        if(export_gpio() == -1)
        {
                return -1;
        }

        if(set_gpio_direction() == -1)
        {
                if(unexport_gpio() == -1)
                {
                        return -1;
                }

                return -1;
        }

        //turn off fan
        fan_off();

        if(control_fan() == -1)
        {
                return -1;
        }

        if(unexport_gpio() == -1)
        {
                return -1;
        }
        return 0;
}