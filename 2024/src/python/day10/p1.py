from ..utils.readInputs import parse_input
from collections import deque

filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day10.txt'
file = parse_input(filePath)


def GetElementValue(array, y, x):
  # Return -1 for out-of-bounds access; otherwise, return the cell value
  if y < 0 or x < 0 or y >= len(array) or x >= len(array[y]):
    return -1
  return array[y][x]

lines = [[int(x) for x in line] for line in file]
total = 0

# Iterate over the grid to find all trailheads (current_value 0)
for y in range(len(lines)):
  for x in range(len(lines[y])):
    if GetElementValue(lines, y, x) == 0:  # Check for trailhead
      queue = deque([[y, x, 0]])  # Initialize queue with the trailhead position
      found = set()  # To store distinct reachable 9's

      while queue:
        current_y, current_x, current_value = queue.popleft()  # Get the next cell to process

        if current_value == 9:
          # If current_value is 9, add to found set
          found.add((current_y, current_x))
        else:
          neighbors = [
                        (current_y + 1, current_x), (current_y - 1, current_x), 
                        (current_y, current_x + 1), (current_y, current_x - 1)
                      ]
          for ny, nx in neighbors:
            if GetElementValue(lines, ny, nx) == current_value + 1:
              queue.append([ny, nx, current_value + 1])

      # Add the number of reachable 9's from this trailhead to the total score
      total += len(found)

print("PART 1 SOLUTION = " + str(total))
