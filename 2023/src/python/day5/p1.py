file_path = '/home/daniel/Documents/repos/adventofcode/2023/inputs/day5.txt'

with open(file_path, 'r') as file:
  lines = file.read().strip().split("\n")

seeds = list(map(int, lines[0].split(" ")[1:]))

maps = []

i = 2
while i < len(lines):
  catA, _, catB = lines[i].split(" ")[0].split("-")
  maps.append([])

  i += 1
  while i < len(lines) and not lines[i] == "":
    dstStart, srcStart, rangeLen = map(int, lines[i].split())
    maps[-1].append((dstStart, srcStart, rangeLen))
    i += 1
  
  i += 1

def findLoc(seed):
  cur_num = seed

  for m in maps:
    for dstStart, srcStart, rangeLen in m:
      if srcStart <= cur_num < srcStart + rangeLen:
        cur_num = dstStart + (cur_num - srcStart)
        break

  return cur_num

locs = []
for seed in seeds:
  loc = findLoc(seed)
  locs.append(loc)

print(min(locs))