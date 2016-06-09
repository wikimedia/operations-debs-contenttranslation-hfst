#!/bin/sh

awk '{ printf "%-25s%-20s%-10s%-10s%s\n",$1,$2,$3,$4,$5}' FS=\,
