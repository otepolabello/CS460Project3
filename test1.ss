;; Project 3 Test 3
;; Function calls

(define (square b)
	(* b b)
)

(define (reciprocal value)
	(/ 1 value)
)

(define (main)
	(display (square 25)) (newline)
	(display (square -25)) (newline)
	(display (square 14.4)) (newline)
	(display (square 0)) (newline)
	(display (reciprocal 4)) (newline)
	(display (reciprocal 6.25)) (newline)
	(display (reciprocal 0)) (newline)
	(display (reciprocal "abc")) (newline)
)

(main)
