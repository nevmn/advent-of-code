package main

import (
	"fmt"
	"log"
)

type Day03 struct{}

func isGoodTriangle(a, b, c int) bool {
	return a+b > c && a+c > b && b+c > a
}

func (d *Day03) Part1(input string) (any, error) {
	result := 0
	err := RunOnLines(input, func(line string) error {
		var a, b, c int
		n, err := fmt.Sscanf(line, " %4d %4d %4d", &a, &b, &c)
		if err != nil || n != 3 {
			return err
		}

		if isGoodTriangle(a, b, c) {
			result++
		}

		return nil
	})
	if err != nil {
		return nil, err
	}

	return result, nil
}

func (d *Day03) Part2(input string) (any, error) {
	result := 0
	i := 0
	threeTriangles := [3][3]int{}
	err := RunOnLines(input, func(line string) error {
		var a, b, c int
		n, err := fmt.Sscanf(line, " %4d %4d %4d", &a, &b, &c)
		if err != nil || n != 3 {
			log.Fatal(err)
		}
		threeTriangles[0][i] = a
		threeTriangles[1][i] = b
		threeTriangles[2][i] = c
		i++
		if i == 3 {
			for i := 0; i < 3; i++ {
				if isGoodTriangle(threeTriangles[i][0], threeTriangles[i][1], threeTriangles[i][2]) {
					result++
				}
			}
			i = 0
			threeTriangles = [3][3]int{}
		}

		return nil
	})
	if err != nil {
		return nil, err
	}

	return result, nil
}
