(define n (read))
(define a (let loop ((i 0) (a '()))
            (if (= i n) (list->vector a)
              (loop (+ i 1) (cons (read) a)))))

(define (calc-sum index step)
  (let loop ((i index) (sum 0))
    (if (>= i n) sum
      (loop (+ i step) (+ sum (vector-ref a i))))))

(define (solve-even)
  (max (calc-sum 1 2) (calc-sum 0 2)))

(define (check thr)
  (let loop ((i 1) (sum (vector-ref a 0)))
    (if (= i n) 
      (>= sum thr)
      (if (< sum thr) 
        (loop (+ i 2) (+ sum (- 0 (vector-ref a i)) (vector-ref a (+ i 1))))
        (loop (+ i 2) (+ (max 0 (- sum (vector-ref a i))) (vector-ref a (+ i 1))))))))

(define (solve-odd)
  (+ (calc-sum 1 2)
     (let binary-search ((l 0) (r 1000000000))
       ; (display (list 'l l 'r r)) (newline)
       (if (= l r) l
         (let ((mid (quotient (+ l r 1) 2)))
           (if (check mid) (binary-search mid r) (binary-search l (- mid 1))))))))

(define first-ans (if (= (modulo n 2) 0) (solve-even) (solve-odd)))
(define second-ans (- (calc-sum 0 1) first-ans))
(display first-ans) (display #\ ) (display second-ans) (newline)
