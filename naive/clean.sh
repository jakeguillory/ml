#!/bin/bash
set -e  # stop on errors

tail -n +2 emails.csv \
| awk 'BEGIN {
    RS="\"[[:space:]]*,[[:space:]]*"
    ORS=","
}
NR % 2 {
    gsub(/\n/, " ")
    gsub(/""/, "\"")
    print $0
    next
}
{ print $0 }' \
| sed 's/^"//; s/",$//' \
| tr '[:upper:]' '[:lower:]' \
| sed 's/[^a-z0-9 ,]/ /g' \
| tr -s ' ' \
| sed -E 's/, *([01]) *$/,\1/' \
| sed 's/^ *//; s/ *$//' \
> emails_clean.csv

echo "✅ Cleaned file saved as emails_clean.csv"

