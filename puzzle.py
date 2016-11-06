#!/usr/bin/env python
# -*- coding: utf-8 -*-

import random
import sys

# puzzle de 3x3
# puzzle resolt    puzzle desordenat
# +---+            +---+
# |123|            | 38|
# |456|            |245|
# |78 |            |761|
# +---+            +---+
# Ordena el puzzle movent els números.
# Indica quin número vols moure a l'espai en blanc adjacent
# El programa ha de
# 1. generar un puzzle desordenat
# 2. mostrar el puzzle
# 3. demanar quin número es vol moure
# 4. veure si es pot moure 
# 5.  si no es pot moure, dir-ho i tornar al punt 2
# 6.  si es pot moure, fer el moviment.
# 7.    comprovar si ha guanyat
# 8.      si ha guanyat acabar eljoc
# 9.      si no ha guanyat, tornar al punt 2.

def genera_puzzle(puzzle):
  for i in range(0,9):
    repeat = True
    while repeat:
      j = random.randint(0,8)
      if puzzle[j] == 10:
        puzzle[j] = i
        repeat = False
  
  return puzzle

def mostra_puzzle(puzzle):
  print "+---+"
  print "|%d%d%d|" % (puzzle[0], puzzle[1], puzzle[2])
  print "|%d%d%d|" % (puzzle[3], puzzle[4], puzzle[5])
  print "|%d%d%d|" % (puzzle[6], puzzle[7], puzzle[8])  
  print "+---+"
  print "\n"

def demanar_numero():
  valid = False
  while not valid:
    in_value = raw_input("(1-9) or q? ")
    if len(in_value) == 1:
      if in_value in "12345678qQ":
        valid = True

  if in_value == 'q' or in_value == 'Q':
    print "\nGame interrupted\n"
    sys.exit(0)

  return int(in_value)


def obtenir_posicio(num, puzzle):
  pos = []

  for row in range(0, 3):
    for column in range(0, 3):
      if num == puzzle[row * 3 + column]:
        pos = [row, column]
        break

  return pos     


def verifica_numero(num, puzzle):
  valid = False
  pos = []
  
  pos = obtenir_posicio(num, puzzle)
  valid = verifica_posicio(pos, puzzle)

  return valid

def verifica_posicio(pos, puzzle):
  valid = False
  row = pos[0]
  column = pos[1]
  
  if (row - 1) >= 0:
    if puzzle[(row - 1) * 3 + column] == 0:
      valid = True

  if (row + 1) <= 2:
    if puzzle[(row + 1) * 3 + column] == 0:
      valid = True

  if (column - 1) >= 0:
    if puzzle[(row * 3) + (column - 1)] == 0:
      valid = True

  if (column + 1) <= 2:
    if puzzle[(row * 3) + (column + 1)] == 0:
      valid = True

  return valid

def moviment(num, puzzle):
  pos = []
  pos = obtenir_posicio(num, puzzle)
  
  row = pos[0]
  column = pos[1]
  
  if (row - 1) >= 0:
    if puzzle[(row - 1) * 3 + column] == 0:
      puzzle[(row - 1) * 3 + column] = num
      puzzle[(row * 3) + column] = 0

  if (row + 1) <= 2:
    if puzzle[(row + 1) * 3 + column] == 0:
      puzzle[(row + 1) * 3 + column] = num
      puzzle[(row * 3) + column] = 0

  if (column - 1) >= 0:
    if puzzle[(row * 3) + (column - 1)] == 0:
      puzzle[(row * 3) + (column - 1)] = num
      puzzle[(row * 3) + column] = 0

  if (column + 1) <= 2:
    if puzzle[(row * 3) + (column + 1)] == 0:
      puzzle[(row * 3) + (column + 1)] = num
      puzzle[(row * 3) + column] = 0    
  
  return puzzle

def es_puzzle_completat(puzzle):
  s = ''.join(map(lambda (x): str(x), puzzle))
  if s == '123456780':
    return True
  else:
    return False


if __name__ == "__main__":
  puzzle = [10 for x in range(0, 9)]
  final = False
  puzzle = genera_puzzle(puzzle)
  while not final:
    final = False
    mostra_puzzle(puzzle)
    num = demanar_numero()
    if verifica_numero(num, puzzle):
      puzzle = moviment(num, puzzle)
      if es_puzzle_completat(puzzle):
        print "\nWell done!!\n"
        mostra_puzzle(puzzle)
        final = True
