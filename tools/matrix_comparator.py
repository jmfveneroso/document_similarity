import numpy as np

mats = []
for i in range(1, 71):
  tmp = []

  num = str(i) if i > 9 else "0" + str(i)
  filename = "../book_matrices/book_" + num + "_mat.txt"
  file = open(filename, "r") 
  for j in range(1000):
    line = file.readline().strip()
    arr = line.split(', ')
    if len(arr) != 1000:
      print "Error."
    tmp.append(arr)

  mats.append(np.matrix(tmp, dtype=float))

def calculate_proximity(mat1, mat2):
  return np.sqrt(np.sum(np.square(mat1 - mat2)))

result = []
for i in range(0, 70):
  arr = []
  for j in range(0, 70):
    arr.append(str(calculate_proximity(mats[i], mats[j])))
  print ", ".join(arr)
