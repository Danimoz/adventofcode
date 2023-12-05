import { promises as fs } from 'fs';

const file_path = '/home/daniel/Documents/repos/adventofcode/2023/inputs/day4.txt';

async function solution(filePath: string) {
  try {
    const data: string = await fs.readFile(filePath, 'utf-8');
    const lines: string[] = data.trim().split("\n");

    const n: number = lines.length;
    const copies: number[][] = Array.from({ length: n }, () => []);

    for (let i = 0; i < n; i++) {
      const line: string = lines[i];
      const parts: string[] = line.split(/\s+/);
      const idx: number = parts.indexOf("|");

      const winning: number[] = parts.slice(2, idx).map(Number);
      const ours: number[] = parts.slice(idx + 1).map(Number);

      let score: number = 0;
      for (const num of ours) {
        if (winning.includes(num)) {
          score += 1;
        }
      }

      for (let j = i + 1; j <= i + score; j++) {
        copies[i].push(j);
      }
    }

    const score: number[] = Array.from({ length: n }, () => 1);

    for (let i = n - 1; i >= 0; i--) {
      for (const j of copies[i]) {
        score[i] += score[j];
      }
    }

    const totalScore: number = score.reduce((acc, curr) => acc + curr, 0);
    console.log(copies);
  } catch (error) {
    console.error(error);
  }
}

solution(file_path);
