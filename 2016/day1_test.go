package main

import (
	_ "embed"
	"testing"
)

//go:embed input/day01.txt
var input string

func TestDay01_Part1(t *testing.T) {
	result, _ := Day01{}.Part1(input)
	if result != 0 {
		t.Errorf("Expected 0, got %d", result)
	}
}

func TestDay01_Part2(t *testing.T) {
}
