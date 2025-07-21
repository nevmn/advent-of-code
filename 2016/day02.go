package main

import (
	"bufio"
	"strconv"
	"strings"
)

type MoveDirection rune

const (
	up    MoveDirection = 'U'
	right               = 'R'
	down                = 'D'
	left                = 'L'
)

type Day02 struct {
	position int
	stops    stops
}

type stops struct {
	top    []any
	right  []any
	bottom []any
	left   []any
}

func (d *Day02) changePositionP1(direction MoveDirection) {
	switch direction {
	case up:
		d.position -= 3
	case left:
		d.position -= 1
	case down:
		d.position += 3
	case right:
		d.position += 1
	}
}

func (d *Day02) changePositionP2(direction MoveDirection) {
	switch direction {
	case left:
		d.position -= 1
	case right:
		d.position += 1
	case up:
		if toChar(d.position) == "D" || d.position == 3 {
			d.position -= 2
		} else {
			d.position -= 4
		}
	case down:
		if d.position == 1 || toChar(d.position) == "B" {
			d.position += 2
		} else {
			d.position += 4
		}
	}
}

func (d *Day02) move(direction MoveDirection) bool {
	var row []any
	switch direction {
	case up:
		row = d.stops.top
	case right:
		row = d.stops.right
	case down:
		row = d.stops.bottom
	case left:
		row = d.stops.left
	}

	for _, pos := range row {
		if d.position == pos {
			return false
		}
	}

	return true

}

func toChar(pos int) string {
	if pos <= 9 {
		return strconv.Itoa(pos)
	}
	return string(rune('A' + pos - 10))
}

func (d *Day02) Part1(input string) (any, error) {
	var result string
	d.position = 5
	d.stops.top = []any{1, 2, 3}
	d.stops.right = []any{3, 6, 9}
	d.stops.bottom = []any{7, 8, 9}
	d.stops.left = []any{1, 4, 7}

	reader := strings.NewReader(input)
	scanner := bufio.NewScanner(reader)

	for scanner.Scan() {
		line := scanner.Text()
		for _, char := range line {
			direction := MoveDirection(char)
			if d.move(direction) {
				d.changePositionP1(direction)
			}
		}
		result += toChar(d.position)
	}

	return result, nil
}

func (d *Day02) Part2(input string) (any, error) {
	var result string
	d.position = 5
	d.stops.top = []any{5, 2, 1, 4, 9}
	d.stops.right = []any{1, 4, 9, 12, 13}
	d.stops.bottom = []any{5, 10, 13, 12, 9}
	d.stops.left = []any{1, 2, 5, 10, 13}

	reader := strings.NewReader(input)
	scanner := bufio.NewScanner(reader)

	for scanner.Scan() {
		line := scanner.Text()
		for _, char := range line {
			direction := MoveDirection(char)
			if d.move(direction) {
				d.changePositionP2(direction)
			}
		}
		result += toChar(d.position)
	}

	return result, nil
}
