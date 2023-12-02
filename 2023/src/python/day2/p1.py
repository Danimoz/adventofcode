output = 0
file = '/home/daniel/Documents/repos/adventofcode/2023/inputs/day2.txt'
limits = { 'red': 12, 'green': 13, 'blue': 14 }

with open(file, 'r') as f:
  for line in f:
    valid_game = True
    game_id = int(line.split(':')[0].split(' ')[1])
    sets = line.split(':')[1]

    for game_set in sets.split(';'):
      for cubes in game_set.strip().split(', '):
        cube_count, color = cubes.split(' ')
        if int(cube_count) > limits[color]:
          valid_game = False
          break  # No need to continue checking for this game if it's already invalid
      if not valid_game:
        break  # No need to check further sets if one set makes the game invalid

    if valid_game:
      output += game_id

print(output)