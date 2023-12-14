with open("/home/daniel/Documents/repos/adventofcode/2023/inputs/day8.txt", "r") as file:
  lines = file.read().split("\n")

steps = lines[0]
direction = lines[2:]

dict = {}

for item in direction:
  key, value = item.split('= ')
  left, right = value.strip('()').split(', ')
  dict[key.strip()] = (left, right)

curr = 'AAA'
count = 0
while curr != 'ZZZ':
  step = steps[count % len(steps)]
  if step == 'L':
    curr = dict[curr][0]
  else:
    curr = dict[curr][1]
  
  count += 1
  
print(count)
    
