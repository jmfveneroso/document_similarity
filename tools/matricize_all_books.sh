#!/bin/bash

for f in book_vectors_2/*
do
  filename=$(basename "$f")
  filename="${filename%.*}_mat.txt"
  echo "Processing $f file..."
  ./tools/matrix_calculator $f "vocab_only_words.txt" > "book_matrices_2/$filename"
done
