import { parseInput } from "../utils/readFile";
import { MergeSort } from '../utils/mergeSort'

const filePath = '/home/daniel/Documents/repos/adventofcode/2024/inputs/day1.txt';

async function solution() {
  const file = await parseInput(filePath);
  
  // Arrange inputs
  const leftArr: number[] = []
  const rightArr: number[] = []

  // Loop through and put each item in the respective arrays
  file.forEach((item) => {
    const lr = item.split(' ')
    leftArr.push(Number(lr[0]))
    rightArr.push(Number(lr[lr.length - 1]))
  })

  const sorter = new MergeSort()
  sorter.sortInPlace(leftArr)
  sorter.sortInPlace(rightArr)

  let sum = 0
  for (let i = 0; i < leftArr.length; i++){
    sum += Math.abs(leftArr[i] - rightArr[i])
  }

  console.log(sum)
}

solution()