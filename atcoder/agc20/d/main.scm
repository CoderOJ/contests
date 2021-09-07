(define (solve a b c d)
  (define k (quotient (+ a b) (+ 1 (min a b))))
  (define (get_ab p)
    (cons
      (- a (* (quotient p (+ k 1)) k) (modulo p (+ k 1)))
      (- b (quotient p (+ k 1)))))
  (define sep 
    (let search ((l 0) (r (+ a b)))
      (if (= l r) l
        (let* ((mid (quotient (+ l r) 2))
               (g_r (get_ab mid))
               (pa (car g_r))
               (pb (cdr g_r)))
          (if (<= pb (* pa k))
            (search (+ mid 1) r)
            (search l mid))))))
  (define pos 
    (let* ((g_r (get_ab sep))
           (pa (car g_r))
           (pb (cdr g_r)))
      (+ 1 sep pb (- (* pa k)))))

  (let loop ((i c))
    (display
      (if (<= i sep)
        (if (= (modulo i (+ k 1)) 0) #\B #\A)
        (if (= (modulo (- i pos) (+ k 1)) 0) #\A #\B)))
    (when (< i d) (loop (+ i 1))))
  (newline))


(let loop ((n (read)))
  (when (> n 0)
    (let* ((a (read))
           (b (read))
           (c (read))
           (d (read)))
    (solve a b c d) (loop (- n 1)))))
