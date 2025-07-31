package main

import (
	"bufio"
	"strings"
)

func Abs[T ~int](x T) T {
	if x < 0 {
		return -x
	}
	return x
}

func RunOnLines(input string, fn func(string) error) error {
	reader := strings.NewReader(input)
	scanner := bufio.NewScanner(reader)

	for scanner.Scan() {
		line := scanner.Text()
		if err := fn(line); err != nil {
			return err
		}
	}

	return nil
}
