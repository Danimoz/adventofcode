# Answer is 53348

words = ['one', 'two', 'three', 'four', 'five', 'six', 'seven', 'eight', 'nine']

total = 0

with open("/home/daniel/Documents/repos/adventofcode/2023/inputs/day1.txt", "r") as file:
  for line in file:
    first = 0
    last = 0

    for pos in range(len(line)):
      for i, word in enumerate(words):
        i += 1  # Adjust index to start from 1
        if line[pos:pos + len(word)] == word or line[pos] == str(i):
          if first == 0:
            first = i
          last = i

    total += first * 10 + last

print(total)
