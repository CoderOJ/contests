(define (put s . arg)
  (when (not (null? arg))
    (display (+ s (car arg))) (display " ")
    (apply put (cons s (cdr arg)))))

(define nn (read))
(if (= nn 3) (put 0 2 5 63)
  (let loop ((s 0) (n nn))
    (cond 
      ((= n 0))
      ((= n 1) (put s 6))
      ((= n 2) (put s 2 4))
      ((= n 3) (put s 2 4 6))
      ((= n 4) (put s 2 3 4 9))
      ((= n 5) (put s 2 3 4 6 9))
      ((= n 6) (put s 2 3 4 8 9 10))
      ((= n 7) (put s 2 3 4 6 8 9 10))
      (#t (put s 2 3 4 6 8 9 10 12) (loop (+ s 12) (- n 8))))))

