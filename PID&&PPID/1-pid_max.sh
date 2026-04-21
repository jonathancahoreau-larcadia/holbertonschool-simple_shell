#!/bin/sh
pid_wrap=$(cat /proc/sys/kernel/pid_max)
pid_max=$((pid_wrap - 1))
echo "$pid_max"