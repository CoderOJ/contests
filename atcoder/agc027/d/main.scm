(define (lazy-cdr ls)
  (force (cdr ls)))

(define (head n ls)
  (if (= n 0) '()
     (cons (lazy-car ls) (head (- n 1) (lazy-cdr ls)))))

(define (lazy-ncdr n ls)
  (if (= n 0) ls (lazy-ncdr (- n 1) (lazy-cdr ls))))



(define (is-prime x)
  (let loop ((i 2))
    (if (> (* i i) x) #t
      (if (= (modulo x i) 0) #f
        (loop (+ i 1))))))

(define primes
  (let loop ((i 2))
    (if (is-prime i) 
      (lazy-cons i (loop (+ i 1))) 
      (loop (+ i 1)))))

(define (gcd n m)
  (if (= 0 m) n (gcd m (modulo n m))))
(define (lcm n m) (quotient (* n m) (gcd n m)))

(define (println fac ls)
  (if (null? ls) (newline)
    (let () (display (* fac (car ls))) (display #\ ) (println fac (cdr ls)))))

(define n (read))
(define pa (list->vector (head n primes)))
(define pb (list->vector (head n (lazy-ncdr n primes))))

(define (get x y)
  (if (or (< x 0) (< y 0)) 1
    (if (= 0 (modulo (+ x y) 2)) 
      (* (vector-ref pa (quotient (+ x y) 2))
         (vector-ref pb (quotient (+ (- n x 1) y) 2)))
      (+ 1
        (lcm (lcm (get (- x 1) y) (get (+ x 1) y))
             (lcm (get x (- y 1)) (get x (+ y 1))))))))

(let loop ((i 0))
  (if (< i n)
    (let ()
      (let loop ((j 0))
        (if (= j n) (newline)
          (let () (display (get i j)) (display #\ ) (loop (+ j 1)))))
      (loop (+ i 1)))))
