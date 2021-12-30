(define n (read))

(define a (make-vector n))
(let loop ((i 0))
  (when (< i n)
    (vector-set! a i (read))
    (loop (+ i 1))))

(define (solve l r fl fr)
  (if (<= (- r l) 1) 0
    (let loop ((s (+ l 1)) (ans (expt 10 18)))
      (if (= s r) ans
        (loop (+ s 1)
              (min ans (+ (solve l s fl (+ fl fr)) 
                          (solve s r (+ fl fr) fr) 
                          (* (vector-ref a s) (+ fl fr)))))))))

(display (+ (vector-ref a 0)
            (vector-ref a (- n 1))
            (solve 0 (- n 1) 1 1)))
(newline)
