#!/bin/bash

echo "delete *~";
find . -name "*~" -exec rm {} \;

echo "delete *.h.gch";
find . -name "*.h.gch" -exec rm {} \;

echo "delete #*#";
find . -name "#*#" -exec rm {} \;

echo "delete *#*";
find . -name "*#*" -exec rm {} \;

echo "delete ._*";
find . -name "._*" -exec rm {} \;