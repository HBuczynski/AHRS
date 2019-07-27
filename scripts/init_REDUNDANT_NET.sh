#!/bin/bash

sudo ifconfig wlan2 192.168.5.1

sudo service dnsmasq restart

sudo sysctl net.ipv4.ip_forward=1

sudo hostapd -B /etc/hostapd/hostapd_2.conf

