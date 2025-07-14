# Conway's Game of Life – C Implementation (MIT 6.087 Lab)

This is a C implementation of **Conway's Game of Life**, developed as part of [MIT's 6.087 Practical Programming in C](https://ocw.mit.edu/courses/electrical-engineering-and-computer-science/6-087-practical-programming-in-c-january-iap-2010/). It simulates cellular automaton behavior over a fixed-size 2D grid.

---

## 🔬 Overview

The Game of Life is a zero-player game where cells evolve according to a simple set of rules based on their neighbors:

1. A live cell with fewer than 2 live neighbors dies (underpopulation).
2. A live cell with more than 3 live neighbors dies (overpopulation).
3. A live cell with 2 or 3 neighbors lives on.
4. A dead cell with exactly 3 live neighbors becomes alive (reproduction).

This implementation supports:
- Hardcoded initialization (default glider)
- File-based input/output (`*.txt` pattern files)
- 50 generations of evolution

---

## 🗂️ Files

| File            | Description                                |
|-----------------|--------------------------------------------|
| `lab1a.c`       | Part A: core logic and hardcoded evolution |
| `lab1b.c`       | Part B: file-based world input/output      |
| `lifegame.c`    | Grid management and helper functions       |
| `lifegame.h`    | Function declarations and constants        |
| `sship.txt`     | Sample initial configuration               |
| `sshipout.txt`  | Expected final output after 50 generations |
| `world.txt`     | Output from latest simulation              |

---

## 🛠️ Build Instructions

```bash
gcc -g -O0 -Wall lab1b.c lifegame.c -o lab1b
