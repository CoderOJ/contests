(define n (* 2 (read)))
(define m (read))
(define a (make-vector n))

(let loop ((i 0))
  (when (< i n)
    (vector-set! a i (read))
    (loop (+ i 1))))
(vector-sort! < a)

(define (calc-ans lb rb)
  (let loop ((l lb) (r rb) (ans 0))
    (if (> l r) ans
      (loop (+ l 1) (- r 1) 
            (max ans (modulo (+ (vector-ref a l) (vector-ref a r)) m))))))

(define gm-bound
  (let loop ((l 0) (r (- n 1)) (c n))
    (if (>= l r) c
      (if (< (+ (vector-ref a l) (vector-ref a r)) m)
        (loop (+ l 1) r c)
        (loop (+ l 1) (- r 1) r)))))

(define sp-id (- n (* 2 (- n gm-bound))))
(display (max (calc-ans 0 (- sp-id 1)) (calc-ans sp-id (- n 1))))
(newline)
