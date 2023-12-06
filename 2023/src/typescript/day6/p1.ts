import { promises as fs } from 'fs';
const filePath = '/home/daniel/Documents/repos/adventofcode/2023/inputs/day6.txt';


async function solution(filePath: string){
  const file = await fs.readFile(filePath, 'utf-8');
  const lines = file.split("\n");
  const times = lines[0].split(": ")[1].split(" ").filter(x => x !== "").map(Number);
  const distances = lines[1].split(": ")[1].split(" ").filter(x => x !== "").map(Number);

  let totalPossibilities = 1; 

  for (let i=0; i<times.length; i++){
    let currentTime = times[i];
    let currentHighscore = distances[i];

    let possibleHighscores = 0;
    const limit = Math.floor(currentTime / 2);

    for (let j = 1; j <= limit; j++){
      const currentDistance =  j * (currentTime - j);
      if (currentDistance > currentHighscore){
        possibleHighscores += (currentTime - 2 * j + 1);
        break
      } 
    }
    
    totalPossibilities *= possibleHighscores;
  }
  
  console.log(totalPossibilities);
}

solution(filePath);