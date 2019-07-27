#!/bin/bash

# Start
sudo ifconfig wlan1 192.168.4.1

sudo service dnsmasq restart

sudo sysctl net.ipv4.ip_forward=1

sudo hostapd -B /etc/hostapd/hostapd_1.conf
