(define (1- x) (- x 1))

(define (read-list n)
  (cond
    [(zero? n) '()]
    [else (let ([a (read)]
                [d (read-list (1- n))])
            (cons a d))]))

(define (reduce-gcd a)
  (let ([g (apply gcd a)])
    (map (lambda (x) (quotient x g)) a)))

(define n (read))
(define a (read-list n))

(define (win? a)
  ; (print a)
  (let ([a-odd (filter odd? a)]
        [a-even (filter even? a)])
    (cond
      [(odd? (length a-even)) #t]
      [(> (length a-odd) 2) #f]
      [(= 1 (car a-odd)) #f]
      [else 
        (not (win? 
               (reduce-gcd
                 (map 
                   (lambda (x) (if (odd? x) (1- x) x))
                   a))))])))

(print (if (win? a) "First" "Second"))
