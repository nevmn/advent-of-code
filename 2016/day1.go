package main

import (
	"strconv"
	"strings"
)

type faceDirection int

const (
	north faceDirection = iota
	east
	south
	west
)

type position struct {
	x int
	y int
}

type Day01 struct {
	faceDirection      faceDirection
	position           position
	history            map[position]bool
	firstDoubleVisited *position
}

func (d *Day01) step(num int) {
	for i := 0; i < num; i++ {
		switch d.faceDirection {
		case north:
			d.position.y += 1
			break
		case east:
			d.position.x += 1
			break
		case south:
			d.position.y -= 1
		case west:
			d.position.x -= 1
		}

		if d.firstDoubleVisited != nil {
			continue
		}

		pos := position{d.position.x, d.position.y}

		_, exists := d.history[pos]
		if exists {
			d.history[pos] = true
			d.firstDoubleVisited = &pos
		} else {
			d.history[pos] = false
		}
	}
}

func (d *Day01) Part1(input string) (int, error) {
	d.faceDirection = north
	d.position = position{0, 0}
	d.history = make(map[position]bool)
	d.firstDoubleVisited = nil

	for _, cmd := range strings.Split(input, ", ") {
		switch cmd[0] {
		case 'R':
			d.faceDirection = (d.faceDirection + 1) % 4
			break
		case 'L':
			d.faceDirection = (d.faceDirection - 1 + 4) % 4
			break
		}
		num, err := strconv.Atoi(strings.TrimRight(cmd[1:], "\r\n"))
		if err != nil {
			return 0, err
		}
		d.step(num)
	}

	return Abs(d.position.x) + Abs(d.position.y), nil
}

func (d *Day01) Part2(input string) (int, error) {
	if _, err := d.Part1(input); err != nil {
		return 0, err
	}

	if d.firstDoubleVisited != nil {
		return Abs(d.firstDoubleVisited.x) + Abs(d.firstDoubleVisited.y), nil
	}

	return 0, nil
}
