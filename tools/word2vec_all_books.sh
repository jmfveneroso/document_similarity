#!/bin/bash

for f in books_stemmed/*
do
  filename=$(basename "$f")
  filename="${filename%.*}.bin"
  echo "Processing $f file..."
  ./tools/word2vec -train $f -output "book_vectors_2/$filename" -cbow 0 -binary 1 -read-vocab "vocab_1000.txt" -size 200
done
