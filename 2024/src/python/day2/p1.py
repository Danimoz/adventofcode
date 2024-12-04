from ..utils.readInputs import parse_input

filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day2.txt'

file = parse_input(filePath)
data = [list(map(int, line.split())) for line in file]
result = 0

def all_ascending(arr: list[int]):
  asc = True
  for i in range(len(arr) - 1):
    if arr[i+1] > arr[i]:
      continue
    else:
      asc = False
      break
  
  return asc

def all_descending(arr: list[int]):
  desc = True
  for i in range(len(arr) - 1):
    if arr[i] > arr[i+1]:
      continue
    else:
      desc = False
      break
  return desc

for i in range(len(data)):
  check = True
  asc = all_ascending(data[i])
  desc = all_descending(data[i])

  if (asc or desc):
    for j in range(len(data[i]) - 1):
      val = abs(data[i][j] - data[i][j+1])
      if (val > 3 or val == 0):
        check = False
        break
  
    if check == True:
      result += 1

print(result)

# Optimized Version
result = 0
def is_valid_sequence(arr: list[int]) -> bool:
  """Check if sequence is ascending, descending, and has valid differences."""
  if len(arr) <= 1:
    return False
  
  return all(arr[i] <= arr[i + 1] for i in range(len(arr) - 1)) or all(arr[i] >= arr[i + 1] for i in range(len(arr) - 1))


for row in data:
  if is_valid_sequence(row):
    # Ensure differences between adjacent values are <= 3 and > 0
    if all(0 < abs(row[i] - row[i + 1]) <= 3 for i in range(len(row) - 1)):
      result += 1

  

