(define (see . param) (display param) (newline))

(define mod 998244353)
(define max-n 500005)
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

(define n (read))
(define k (read))

(define (solve r b)
  (cond
    ((< r b) 0)
    ((< r n) 0)
    ((>= (- r b) n) (ncr k r))
    (#t 
      (when (= r b) (set! b (- b 1)))
      (- (ncr (+ r b) r) (ncr (+ r b) (+ r r (- n) 1))))))

(let loop ((ans 0) (i 0))
  (see ans i)
  (cond
    ((> i k) (write (modulo ans mod)) (newline))
    (#t (loop (+ ans (solve i (- k i))) (+ i 1)))))
