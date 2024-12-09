from ..utils.readInputs import parse_input

filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day6.txt'
file = parse_input(filePath)

rows = len(file)
cols = len(file[0])

direction_map = {
  'up': 'right',
  'right': 'down',
  'down': 'left',
  'left': 'up'
}

def get_start_point():
  # Find start point with direction
  start_markers = {'^': 'up', '>': 'right', 'v': 'down', '<': 'left'}
  for i in range(rows):
    for j in range(cols):
      if file[i][j] in start_markers:
        return (i, j, start_markers[file[i][j]])
  return None

# Initialize
start = get_start_point()
if start is None:
    raise ValueError("No starting point found")

spt_row, spt_col, direction = start
positions = set()
positions.add((spt_row, spt_col))

while True:
  # Calculate next position based on direction
  if direction == 'up':
    next_row, next_col = spt_row - 1, spt_col
  elif direction == 'right':
    next_row, next_col = spt_row, spt_col + 1
  elif direction == 'down':
    next_row, next_col = spt_row + 1, spt_col
  else:  # left
    next_row, next_col = spt_row, spt_col - 1

  # Check if next position is valid
  if 0 <= next_row < rows and 0 <= next_col < cols:
    if file[next_row][next_col] == '#':
      # Obstacle: Change direction
      direction = direction_map[direction]
    else:
      # Move to next position
      spt_row, spt_col = next_row, next_col
      positions.add((spt_row, spt_col))
  else:
    # Out of bounds: stop simulation
    break

print(len(positions))

