#!/bin/bash

for f in book_vectors/*
do
  filename=$(basename "$f")
  filename="${filename%.*}_mat.txt"
  echo "Processing $f file..."
  ./tools/matrix_calculator $f "vocab_only_words.txt" > "book_matrices/$filename"
done
