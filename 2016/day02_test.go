package main

import (
	_ "embed"
	"testing"
)

//go:embed input/day02.txt
var inputDay02 string

func TestDay02_Part1(t *testing.T) {
	tests := []tests{
		{`ULL
RRDDD
LURDL
UUUUD`, "1985"},
		{inputDay02, "44558"},
	}
	runTest(t, tests, solvers[2].Part1)
}

func TestDay02_Part2(t *testing.T) {
	tests := []tests{
		{`ULL
RRDDD
LURDL
UUUUD`, "5DB3"},
		{inputDay02, "6BBAD"},
	}
	runTest(t, tests, solvers[2].Part2)
}
