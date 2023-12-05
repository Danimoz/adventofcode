file_path = '/home/daniel/Documents/repos/adventofcode/2023/inputs/day3.txt'

with open(file_path, 'r') as file:
  data = file.read()
  engine_map = data.strip().split('\n')

m = len(engine_map) # Number of rows
n = len(engine_map[0]) # Number of columns

goods = [[[] for _ in range(n)] for _ in range(m)]


def is_symbol(i, j, num):
  if not(0 <= i < m and 0 <= j < n):
    return False
  
  if engine_map[i][j] == '*':
    goods[i][j].append(num)
  return engine_map[i][j] != '.' and not engine_map[i][j].isdigit()

ans = 0

for i, line in enumerate(engine_map):
  start = 0
  j = 0
  while j < n:
    start = j
    num = ''
    while j < n and line[j].isdigit():
      num += line[j]
      j += 1

    if num == '':
      j += 1
      continue

    num = int(num)

    is_symbol(i, start - 1, num) or is_symbol(i, j, num)
      
    for k in range(start-1, j+1):
      is_symbol(i - 1, k, num) or is_symbol(i + 1, k, num)

for i in range(m):
  for j in range(n):
    nums = goods[i][j]
    if engine_map[i][j] == "*" and len(nums) == 2:
      ans += nums[0] * nums[1]
        

print(ans)

