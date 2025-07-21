package main

import (
	"flag"
	"log"
	"os"
	"testing"
)

type Solver interface {
	Part1(input string) (any, error)
	Part2(input string) (any, error)
}

type solverFn func(input string) (any, error)

var solvers = map[uint]Solver{
	1: &Day01{},
	2: &Day02{},
}

var day *uint
var file *string

func init() {
	day = flag.Uint("day", 0, "Day to solve")
	file = flag.String("file", "", "Path to inputDay01 file")
}

func main() {
	flag.Parse()
	if *day == 0 {
		log.Fatal("No day specified")
	}
	if *file == "" {
		log.Fatal("No file specified")
	}

	solver, exists := solvers[*day]
	if !exists {
		log.Fatalf("No solver for day %d", *day)
	}

	input, err := os.ReadFile(*file)
	if err != nil {
		log.Fatal(err)
	}

	result1, err := solver.Part1(string(input))
	if err != nil {
		log.Fatal(err)
	}
	log.Printf("Part 1: %d\n", result1)

	result2, err := solver.Part2(string(input))
	if err != nil {
		log.Fatal(err)
	}
	log.Printf("Part 2: %d\n", result2)
}

type tests struct {
	input  string
	result any
}

func runTest(t *testing.T, tests []tests, solver solverFn) {
	for _, test := range tests {
		result, err := solver(test.input)
		if err != nil {
			t.Fatal(err)
		}
		if result != test.result {
			t.Errorf("Expected %v, got %v", test.result, result)
		}
	}
}
