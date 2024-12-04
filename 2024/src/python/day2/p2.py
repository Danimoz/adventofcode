from ..utils.readInputs import parse_input

filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day2.txt'

file = parse_input(filePath)
data = [list(map(int, line.split())) for line in file]

result = 0
def is_safe(sequence):
  # Check if the sequence is strictly increasing
  is_increasing = all(sequence[i] < sequence[i + 1] for i in range(len(sequence) - 1))
  # Check if the sequence is strictly decreasing
  is_decreasing = all(sequence[i] > sequence[i + 1] for i in range(len(sequence) - 1))

  if not (is_increasing or is_decreasing):
    return False

  # Check if all adjacent differences are between 1 and 3 inclusive
  for i in range(len(sequence) - 1):
    diff = abs(sequence[i + 1] - sequence[i])
    if not (1 <= diff <= 3):
      return False

  return True


def is_safe_with_one_removal(sequence):
  """
  Determines if a sequence can be made safe by removing exactly one level.
  """
  for i in range(len(sequence)):
    # Create a new sequence with one level removed
    new_sequence = sequence[:i] + sequence[i + 1:]
    if is_safe(new_sequence):
      return True
    
  return False


for row in data:
  if is_safe(row):
    result += 1
  elif is_safe_with_one_removal(row):
    result += 1

print(result)
