#!/bin/bash

fan_state=OFF


# exporting gpio for fan control
export_gpio()
{
        echo 412 > /sys/class/gpio/export

        echo "out" > /sys/class/gpio/gpio412/direction
        echo 0 > /sys/class/gpio/gpio353/value
}
export_gpio

read_temp()
{
        core_temp=0

        for i in {0..5}
        do
                temp=$(cat /sys/devices/virtual/thermal/thermal_zone$i/temp)
                if [[ $core_temp -lt $temp ]]
                then
                  core_temp=$temp
                fi
        done
}

while true
do
    read_temp
    temp=$core_temp

    if [[ $temp -gt 65000 ]]
    then
        if [ $fan_state = OFF ]
        then
            fan_state=ON
            echo 1 > /sys/class/gpio/gpio412/value
            echo "fan on"
        fi
    elif [ $fan_state = ON ]
    then
        echo 0 > /sys/class/gpio/gpio412/value
        echo "fan off"
        fan_state=OFF
    fi
sleep 2
done