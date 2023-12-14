import math

with open("/home/daniel/Documents/repos/adventofcode/2023/inputs/day8.txt", "r") as file:
  lines = file.read().split("\n")

steps = lines[0]

dict = {}

for item in lines[2:]:
  key, value = item.split('= ')
  left, right = value.strip('()').split(', ')
  dict[key.strip()] = (left, right)

def n_steps(curr):
  count = 0
  while curr[2] != 'Z':
    step = steps[count % len(steps)]
    if step == 'L':
      curr = dict[curr][0]
    else:
      curr = dict[curr][1]
    
    count += 1
  
  return count

curr = [n for n in dict if n[2] == 'A']
lens = [n_steps(node) for node in curr]

ans = math.lcm(*lens)

print(ans)
    
