#!/usr/bin/env python3

from dataclasses import dataclass
import math


@dataclass
class Point:
    x: int
    y: int


def euclidian_dist(a: Point, b: Point):
    x = b.x - a.x
    y = b.y - a.y
    return math.sqrt(x*x + y*y)


# City Block
def manhatan_dist(a: Point, b: Point):
    x = abs(b.x - a.x)
    y = abs(b.y - a.y)
    return x + y


# Chessboard
def chebyshev_dist(a: Point, b: Point):
    x = abs(b.x - a.x)
    y = abs(b.y - a.y)
    return max(x, y)


def run():
    ax, ay, bx, by = int(input()), int(input()), int(input()), int(input())

    a = Point(ax, ay)
    b = Point(bx, by)

    print(f"{euclidian_dist(a, b):.2f}")
    print(f"{manhatan_dist(a, b):.2f}")
    print(f"{chebyshev_dist(a, b):.2f}")


if __name__ == "__main__":
    run()
