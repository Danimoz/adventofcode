from ..utils.readInputs import parse_input

filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day10.txt'
file = parse_input(filePath)


def GetElementValue(array, y, x):
  # Return -1 for out-of-bounds access; otherwise, return the cell value
  if y < 0 or x < 0 or y >= len(array) or x >= len(array[y]):
    return -1
  return array[y][x]

lines = [[int(x) for x in line] for line in file]
total = 0

rows = len(lines)
cols = len(lines[0])

def rating_iterative(lines, start_y, start_x):
  stack = [(start_y, start_x, 0)]
  total_paths = 0

  while stack:
    current_y, current_x, current_value = stack.pop()

    if current_value == 9:
      total_paths += 1
      continue

    else:
      neighbors = [
                    (current_y + 1, current_x), (current_y - 1, current_x), 
                    (current_y, current_x + 1), (current_y, current_x - 1)
                  ]
      path_count = 0
      for ny, nx in neighbors:
        if GetElementValue(lines, ny, nx) == current_value + 1:
          stack.append((ny, nx, current_value + 1))
          path_count += 1
      
  return total_paths

total = 0

for i in range(rows):
  for j in range(cols):
    if GetElementValue(lines, i, j) == 0:  # Check for trailhead
      # Use the iterative rating function for each trailhead
      total += rating_iterative(lines, i, j)

print(total)
          
