(define (sg n k)
  ; (display (list n k)) (newline)
  (cond
    ((< n k) 0)
    ((= 0 (modulo n k)) (quotient n k))
    (#t (let* ([quo-k (quotient n k)]
               [min-n  (+ 1 (* quo-k k))]
               [det (- n min-n)]
               [sub (+ quo-k 1)]
               [sub-k (+ 1 (quotient det sub))])
          (sg (- n (* sub-k sub)) k)))))

(let loop ([i (read)] [xor-sum 0])
  (if (= i 0) (display (if (= 0 xor-sum) "Aoki\n" "Takahashi\n"))
    (loop (- i 1) (logxor xor-sum (let* ([n (read)] [k (read)]) (sg n k))))))
