#!/bin/bash

sudo -s <<EOF
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy0/scaling_governor
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy1/scaling_governor
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy2/scaling_governor
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy3/scaling_governor
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy4/scaling_governor
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy5/scaling_governor
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy6/scaling_governor
echo "powersave" > /sys/devices/system/cpu/cpufreq/policy7/scaling_governor
EOF
