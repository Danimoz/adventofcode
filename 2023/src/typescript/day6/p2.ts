import { promises as fs } from 'fs';

async function solution(filePath: string){
  const file = await fs.readFile(filePath, 'utf-8');
  const [times, distances] = file.split("\n");
  let time = '';
  let distance = '';
  times.split(": ")[1].split(" ").filter(x => x !== "").forEach(x => time += x);
  distances.split(": ")[1].split(" ").filter(x => x !== "").forEach(x => distance += x);

  const actualTime = Number(time);
  const actualDistance = Number(distance);

  const limit = Math.floor(actualTime / 2);
  let possibleHighscores = 0;

  for (let i = 1; i <= limit; i++){
    const currentDistance = i * (actualTime - i);
    if (currentDistance > actualDistance){
      possibleHighscores += (actualTime - 2 * i + 1);
      break
    } 
  }

  console.log(possibleHighscores);
}


const filePath = '/home/daniel/Documents/repos/adventofcode/2023/inputs/day6.txt';
solution(filePath);