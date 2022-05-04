#!/usr/bin/env python

import random

def main():
    seed = 0
    random.seed(seed)
    n = 10_000
    A = list(range(n))
    random.shuffle(A)
    with open("nums.txt", "w") as f:
        for x in A:
            f.write(f"{x}\n")

if __name__ == "__main__":
    main()