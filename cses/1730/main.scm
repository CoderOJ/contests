(define (main)
  (let loop ((n (read)) (xor-sum 0))
    (if (= n 0) (if (> xor-sum 0) "first" "second")
      (loop (- n 1) (logxor xor-sum (read))))))

(let loop-main ((t (read)))
  (when (> t 0)
    (display (main)) (newline)
    (loop-main (- t 1))))

(exit)
