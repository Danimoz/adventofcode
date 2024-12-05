from ..utils.readInputs import parse_input

filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day4.txt'
file = parse_input(filePath)

rows = len(file)
cols = len(file[0])

def check_sequence(seq: str):
  return seq == 'SAM' or seq == 'MAS'


sum = 0

for  i in range(rows):
  for j in range(cols):
    if i <= rows - 3 and j <= cols - 3 and (file[i][j] == 'M' or file[i][j] == 'S') and (file[i][j+2] == 'M' or file[i][j+2] == 'S'):
      ltr_diag = ''.join(file[i+k][j+k] for k in range(3))
      rtl_diag = ''.join(file[i+k][j+2-k] for k in range(3))
      if check_sequence(ltr_diag) and check_sequence(rtl_diag):
        sum += 1

      
print(sum)