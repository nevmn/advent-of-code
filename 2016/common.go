package main

func Abs[T ~int](x T) T {
	if x < 0 {
		return -x
	}
	return x
}
