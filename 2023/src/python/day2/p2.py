output = 0
file = '/home/daniel/Documents/repos/adventofcode/2023/inputs/day2.txt'

with open(file, 'r') as f:
  for line in f:
    red, green, blue = [], [], []

    sets = line.split(':')[1]

    for set in sets.split(';'):
      for cubes in set.strip().split(', '):
        if cubes.split(' ')[1] == 'red':
          red.append(int(cubes.split(' ')[0]))

        if cubes.split(' ')[1] == 'green':
          green.append(int(cubes.split(' ')[0]))

        if cubes.split(' ')[1] == 'blue':
          blue.append(int(cubes.split(' ')[0]))
  
    output += max(red) * max(green) * max(blue)

print('part 2:', output)