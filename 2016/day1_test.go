package main

import (
	_ "embed"
	"testing"
)

//go:embed input/day01.txt
var input string

type tests struct {
	input  string
	result int
}

func TestDay01_Part1(t *testing.T) {
	tests := []tests{
		{"R2, L3", 5},
		{"R2, R2, R2", 2},
		{"R5, L5, R5, R3", 12},
		{input, 307},
	}
	for _, test := range tests {
		result, err := solvers[1].Part1(test.input)
		if err != nil {
			t.Fatal(err)
		}
		if result != test.result {
			t.Errorf("Expected %d, got %d", test.result, result)
		}
	}
}

func TestDay01_Part2(t *testing.T) {
	tests := []tests{
		{"R8, R4, R4, R8", 4},
		{input, 165},
	}
	for _, test := range tests {
		result, err := solvers[1].Part2(test.input)
		if err != nil {
			t.Fatal(err)
		}
		if result != test.result {
			t.Errorf("Expected %d, got %d", test.result, result)
		}
	}
}
