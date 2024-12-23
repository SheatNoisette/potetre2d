#!/bin/sh

# This script is used to generate the license file for the project.
# The license file is generated by concatenating the license files of all
# dependencies of the project.

find . -type f \( -iname "license" -o -iname "unlicense" -o -iname "copying" \) | while read -r file; do

    echo "------------------------------------------------------------------------"
    if [ "$file" = "./LICENSE" ]; then
        echo "Potetre2D LICENSE"
    else
        echo "$file" | sed -e "s/^\.\///g" | sed -e "s/libs\///g" | sed -e "s/\// /g" | sed -e "s/\b\(.\)/\u\1/g"
    fi
    echo "------------------------------------------------------------------------"
    echo
    cat "$file"
    echo
done