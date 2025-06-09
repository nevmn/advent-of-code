package main

import (
	"flag"
	"log"
	"os"
)

type Solver interface {
	Part1(input string) (int, error)
	Part2(input string) (int, error)
}

var solvers = map[uint]Solver{
	1: &Day01{},
}

var day *uint
var file *string

func init() {
	day = flag.Uint("day", 0, "Day to solve")
	file = flag.String("file", "", "Path to input file")
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
