#!/bin/bash

## Set basic variables:

# Interface mode.
interface=$1

# Net description.
mode=$2

# Channel
channel=$3

hostapd_1='/etc/hostapd/hostapd_1.conf'
hostapd_2='/etc/hostapd/hostapd_2.conf'

# Execute commands:
if [ "$interface" == "wlan1" ]; then

    hw_mode_str='s/hw_mode=.*/hw_mode='$mode'/g'
    sed -i -- $hw_mode_str $hostapd_1 

    channel_str='s/channel=.*/channel='$channel'/g'
    sed -i -- $channel_str $hostapd_1

elif [ "$interface" == "wlan2" ]; then  
 
    hw_mode_str='s/hw_mode=.*/hw_mode='$mode'/g'
    sed -i -- $hw_mode_str $hostapd_2 

    channel_str='s/channel=.*/channel='$channel'/g'
    sed -i -- $channel_str $hostapd_2 

else
    echo "Wrong parameters."
fi
