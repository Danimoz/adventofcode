# Description: Day 1 of Advent of Code 2023

addition_array = []

with open("/home/daniel/Documents/repos/adventofcode/2023/inputs/day1.txt", "r") as file:
  for line in file:
    digits = [char for char in line if char.isdigit()] 
    addition_array.append(int(digits[0] + digits[-1]))

print(sum(addition_array))      
