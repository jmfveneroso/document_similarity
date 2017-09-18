#!/bin/bash

for f in books_clean/*
do
  echo "Processing $f file..."
  ./tools/tokenizer $f > "books_tokenized/$(basename $f)"
  ./tools/stemmer "books_tokenized/$(basename $f)" > "books_stemmed/$(basename $f)"
done
