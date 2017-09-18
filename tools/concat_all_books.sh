#!/bin/bash

for f in books_stemmed/*
do
  echo "Processing $f file..."
  cat $f >> all_books.txt
done
