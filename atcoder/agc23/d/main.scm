(define (put . arg)
  (when (not (null? arg))
    (display (car arg)) (display " ")
    (apply put (cdr arg))))

(define n (read))
(define s (read))

(define p 
  (let loop ((p '()) (i 0))
    (if (= i n) 
      (sort (list->vector p) (lambda (a b) (< (car a) (car b))))
      (loop (cons (cons (read) (read)) p) (+ i 1)))))

(define (pos index) (car (vector-ref p index)))
(define (pop index) (cdr (vector-ref p index)))
(define (set-pop index value) (set-cdr! (vector-ref p index) value))

(write 
  (let solve ((ans 0) (l 0) (r (- n 1)) 
              (goal (if (< (pop 0) (pop (- n 1))) 0 (- n 1))))
    ; (put 'ans ans 'l l 'r r 'goal goal) (newline)
    (cond 
      ((< s (pos l)) (+ ans (- (pos r) s)))
      ((< (pos r) s) (+ ans (- s (pos l))))
      ((>= (pop l) (pop r)) 
        (set-pop l (+ (pop l) (pop r))) 
        (solve (+ ans (if (= goal r) (- (pos r) (pos l)) 0)) l (- r 1) l))
      (#t
        (set-pop r (+ (pop l) (pop r)))
        (solve (+ ans (if (= goal l) (- (pos r) (pos l)) 0)) (+ l 1) r r)))))
