#!/bin/bash

src_dir="src/"

build_dir="build/"

mkdir -p "$build_dir"

for file in "$src_dir"*
do
    name="$(basename "$file")"
    extension="${name##*.}"
    if [ "$extension" != "cpp" ] && [ "$extension" != "hpp" ]; then
        contents="$(cat "$file")"
        escaped_contents="${contents//\\/\\\\}" 
        echo -e "R\"(\n" > "$build_dir"$name
        echo -e "$escaped_contents" >> "$build_dir"$name
        echo -e "\n)\"" >> "$build_dir"$name
        echo "ファイル $file を処理済み"
    else
        cp "$file" "$build_dir"
        echo "ファイル $file をコピー"
    fi
done



g++ -std=c++23 "$build_dir"almo.cpp -o "$build_dir"almo 

if [ $? -ne 0 ]; then
    echo "ビルドに失敗しました。"
    exit 1
fi


echo "ビルドが完了しました。"
