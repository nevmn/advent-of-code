package main

import (
	_ "embed"
	"testing"
)

//go:embed input/day01.txt
var inputDay01 string

func TestDay01_Part1(t *testing.T) {
	tests := []tests{
		{"R2, L3", 5},
		{"R2, R2, R2", 2},
		{"R5, L5, R5, R3", 12},
		{inputDay01, 307},
	}
	runTest(t, tests, solvers[1].Part1)
}

func TestDay01_Part2(t *testing.T) {
	tests := []tests{
		{"R8, R4, R4, R8", 4},
		{inputDay01, 165},
	}
	runTest(t, tests, solvers[1].Part2)
}
