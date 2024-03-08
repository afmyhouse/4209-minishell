#!/bin/bash
set -x
echo test1 > ls >> ls >> ls | echo test2 >> ls | cat ls
#ps -ef | grep  dbus | grep -v grep | awk '{print $2 $3}' | column -t | wc -l