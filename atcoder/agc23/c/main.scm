(define mod 1000000007)
(define max-n 1000005)
(define n (- (read) 1))

(define fac
  (let loop ((result (make-vector max-n 1)) (i 1))
    (cond
      ((>= i max-n) result)
      (#t (vector-set! result i (modulo (* i (vector-ref result (- i 1))) mod)) 
          (loop result (+ i 1))))))
(define inv
  (let loop ((result (make-vector max-n 1)) (i 2))
    (cond
      ((>= i max-n) result)
      (#t (vector-set! result i (modulo (* (- mod (quotient mod i)) 
                                           (vector-ref result (modulo mod i))) mod))
          (loop result (+ i 1))))))
(define ifac
  (let loop ((result (make-vector max-n 1)) (i 1))
    (cond
      ((>= i max-n) result)
      (#t (vector-set! result i (modulo (* (vector-ref result (- i 1))
                                           (vector-ref inv i)) mod))
          (loop result (+ i 1))))))

(define (ncr n r)
  (cond 
    ((> r n) 0)
    ((< r 0) 0)
    (#t (modulo (* (vector-ref fac n) (vector-ref ifac r) (vector-ref ifac (- n r))) mod))))

(define (split-into n k)
  (ncr k (- n k)))

(define (can-cover k)
  (* (vector-ref fac k) (vector-ref fac (- n k)) (split-into (- n 1) (- k 1))))

(if (= n 1) (write 1)
  (let loop ((ans (modulo (* (+ n 1) (vector-ref fac n)) mod)) (i 2))
    (if (> i n) (write ans)
      (loop (modulo (- ans (can-cover i)) mod) (+ i 1)))))
