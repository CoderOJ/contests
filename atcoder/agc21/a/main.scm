(define n (read))
(define (count x)
  (let loop ((ans 0) (cur x))
    (if (= cur 0) ans
      (loop (+ ans (modulo cur 10)) (quotient cur 10)))))
(let loop ((ans (count n)) (cur 10))
  (if (> cur n) (write ans)
    (loop (max ans (count (- (* (quotient n cur) cur) 1))) (* cur 10))))
