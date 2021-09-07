(define n (read))

(define a
  (let loop ((res '()) (i n))
    (if (= i 0) res
      (loop (cons (read) res) (- i 1)))))

(let loop ((op a) (l 2) (r 2))
  ; (write (list op l r)) (newline)
  (cond
    ((> l r) (write -1) (newline))
    ((null? op) (write l) (display " ") (write r) (newline))
    (#t (let* ((cur (car op)) 
               (vl (* cur (quotient (+ l cur -1) cur)))
               (vr (+ (* cur (quotient r cur)) cur -1)))
          (loop (cdr op) vl vr)))))
