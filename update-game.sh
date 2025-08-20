#!/bin/bash
# Poli skripta

echo "Navigating to git folder..."
cd Git/bikove-i-kravi || exit 1

echo "Getting new game data..."
git fetch
git pull

echo "Moving executable to root folder..."
if [ -f ./bikove-i-kravi ]; then
    mv -f ./bikove-i-kravi ../../
    echo "Executable moved to root folder."
else
    echo "Executable not found in bikove-i-kravi folder!"
fi

cd ../../ || exit 1
