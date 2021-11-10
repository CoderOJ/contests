(define n (read))
(define cost-right (read))
(define cost-left (read))

(define a (make-vector (+ n 1)))
(let loop ((i 1))
  (when (<= i n)
    (vector-set! a i (read))
    (loop (+ i 1))))

(define cost (make-vector (+ n 1)))
(let loop-i ((i 1))
  (when (<= i n)
    (vector-set! cost i 
      (let loop-j ((j (- i 1)) (cur-cost 0) (min-cost (expt 10 30)))
        (if (= j 0) (min cur-cost min-cost)
          (if (< (vector-ref a j) (vector-ref a i))
            (loop-j (- j 1) (+ cur-cost cost-left) 
                    (min min-cost (+ cur-cost (vector-ref cost j))))
            (loop-j (- j 1) (+ cur-cost cost-right) min-cost)))))
    (loop-i (+ i 1))))

(display
  (let loop ((i n) (extra-cost 0))
    (if (= i 0) extra-cost
      (min (+ (vector-ref cost i) extra-cost)
           (loop (- i 1) (+ extra-cost cost-left))))))
