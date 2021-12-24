(define n (read))
(define e (make-vector n (list)))

(let loop ((i 1))
  (when (< i n)
    (let ((u (- (read) 1))
          (v (- (read) 1)))
      (vector-set! e u (cons v (vector-ref e u)))
      (vector-set! e v (cons u (vector-ref e v))))
    (loop (+ i 1))))

(define len 0)
(define (dfs u f)
  (let loop ((el (vector-ref e u)) (pmax 0))
    (if (null? el) pmax
      (if (= (car el) f) (loop (cdr el) pmax)
        (let ((vmax (+ (dfs (car el) u) 1)))
          (set! len (max len (+ pmax vmax)))
          (loop (cdr el) (max pmax vmax)))))))

(dfs 0 0)
(display
  (if (= (modulo len 3) 1) "Second" "First"))
(newline)
