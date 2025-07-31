package main

import (
	_ "embed"
	"testing"
)

//go:embed input/day03.txt
var inputDay03 string

func TestDay03_Part1(t *testing.T) {
	tests := []tests{
		{inputDay03, 983},
	}
	runTest(t, tests, solvers[3].Part1)
}

func TestDay03_Part2(t *testing.T) {
	tests := []tests{
		{inputDay03, 1836},
	}
	runTest(t, tests, solvers[3].Part2)
}
