from ..utils.readInputs import parse_input

filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day4.txt'
file = parse_input(filePath)

rows = len(file)
cols = len(file[0])

def check_sequence(seq: str):
  if seq == 'XMAS' or seq == 'SAMX':
    return True
  return False

sum = 0

for  i in range(rows):
  for j in range(cols):
    # check horizontally (right)
    if j <= cols - 4 and (file[i][j] == 'X' or file[i][j] == 'S'):
      if check_sequence(file[i][j:j+4]):
        sum += 1

    # check vertically (down)
    if  i <= rows - 4 and (file[i][j] == 'X' or file[i][j] == 'S'):
      vert = ''.join(file[i+k][j] for k in range(4))
      if check_sequence(vert):
        sum += 1

    # check diagonal (left-to-right)
    if i <= rows - 4 and j <= cols - 4 and (file[i][j] == 'X' or file[i][j] == 'S'):
      ltr_diag = ''.join(file[i+k][j+k] for k in range(4))
      if check_sequence(ltr_diag):
        sum += 1

    # check diagonal (right-to-left)
    if i <= rows - 4 and j >= 4 - 1 and (file[i][j] == 'X' or file[i][j] == 'S'):
      rtl_diag = ''.join(file[i+k][j-k] for k in range(4))
      if check_sequence(rtl_diag):
        sum += 1

print(sum)
    



