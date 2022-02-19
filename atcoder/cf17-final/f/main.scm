(define (get n m x y)
  (cond
    [(= x (- n 1)) y]
    [(= y 0) (quotient x (- m 1))]
    [else (let ([id (quotient x (- m 1))]
                [xx (modulo x (- m 1))]
                [yy (- y 1)])
            (if (= id 0)
              (+ m (* (- m 1) xx) yy)
              (+ m (* (- m 1) yy) (modulo (+ (* id yy) xx) (- m 1)))))]))

(define n 1407)
(define m 38)

(display n)
(display " ")
(display m)
(display "\n")

(let loop ([i 0])
  (when (< i n)
    (let loop ([j 0])
      (when (< j m)
        (display (+ 1 (get n m i j)))
        (display " ")
        (loop (+ j 1))))
    (display "\n")
    (loop (+ i 1))))
