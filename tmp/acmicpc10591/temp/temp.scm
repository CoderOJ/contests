(define (read-line)
  (let ([c (read-char)])
    (cond
      [(eqv? c #\newline) '()]
      [(eqv? c #!eof) '()]
      [else (cons c (read-line))])))

(define-syntax let-bind
  (syntax-rules ()
    ((_ () s ...) 
     (begin s ...))
    ((_ ([() v] d ...) s ...)
     (let-bind (d ...) s ...))
    ((_ ([(a . b) v] d ...) s ...)
     (let* ([_v v] [a (car _v)])
       (let-bind ([b (cdr _v)] d ...) s ...)))
    ((_ ([a v] d ...) s ...)
     (let ([a v])
       (let-bind (d ...) s ...)))))

(define (list-split ls v)
  (cond
    [(null? ls) '(())]
    [(eqv? v (car ls)) 
     (cons '() (list-split (cdr ls) v))]
    [else 
      (let-bind 
        ([(a . b) (list-split (cdr ls) v)])
        (cons (cons (car ls) a) b))]))

(define (filter f ls)
  (cond
    [(null? ls) '()]
    [(f (car ls)) 
     (cons (car ls) (filter f (cdr ls)))]
    [else 
      (filter f (cdr ls))]))

(define box list)
(define unbox car)
(define set-box! set-car!)

(define (parse ls)

  (define (read-pred ls pred)
    (cond
      [(null? ls) 
       (values '() '())]
      [(pred (car ls))
       (let-values 
         ([(t rs) (read-pred (cdr ls) pred)])
         (values (cons (car ls) t) rs))]
      [else 
        (values '() ls)]))

  (define (read-identifier ls)
    (cond
      [(char-numeric? (car ls))
       (let-values 
         ([(t rs) (read-pred ls char-numeric?)])
         (values 
           (string->number (list->string t)) 
           rs))]
      [(char-alphabetic? (car ls))
       (let-values 
         ([(t rs) (read-pred ls char-alphabetic?)])
         (values 
           (string->symbol (list->string t)) 
           rs))]))

  (define (read-statement ls)
    (let-values 
      ([(t rs) (read-identifier ls)])
      (cond
        [(number? t) (values t rs)]
        [(symbol? t)
         (if (and 
               (not (null? rs))
               (eqv? #\( (car rs)))
           (let-values 
             ([(tp rrs) (read-statements (cdr rs))])
             (values (cons t tp) rrs))
           (values t rs))])))

  (define (read-statements ls)
    (cond
      [(eqv? #\) (car ls)) 
       (values '() (cdr ls))]
      [(eqv? #\, (car ls)) 
       (let-values 
         ([(t rs) (read-statements (cdr ls))])
         (values t rs))]
      [else
        (let-values 
          ([(t rs) (read-statement ls)])
          (let-values 
            ([(rt rrs) (read-statements rs)])
            (values (cons t rt) rrs)))]))

  (let-values 
    ([(t rs) (read-statement ls)]) 
    t))

(define edge cons)
(define graph list)

; (define (dump-graph g)
;   (let-bind 
;     ([(n s t e) g])
;     (printf "n = ~a\n" n) 
;     (printf "s = ~a, t = ~a\n" s t) 
;     (let loop ([ls e])
;       (when (not (null? ls))
;         (printf "~a ~a\n" (caar ls) (cdar ls))
;         (loop (cdr ls))))))

(define (eval-cactus l)

  (define cactus-c 
    (graph 2 0 1 '((0 . 1))))

  (define (map-edges f e)
    (map 
      (lambda (x) 
        (cons 
          (f (car x)) 
          (f (cdr x)))) 
      e))

  (define (list-length< a b)
    (cond
      [(null? b) #f]
      [(null? a) #t]
      [else 
        (list-length< 
          (cdr a) 
          (cdr b))]))

  (define (list-concat a b)
    (cond
      [(null? a) b]
      [else 
        (cons 
          (car a) 
          (list-concat (cdr a) b))]))

  (define (func-c ls)
    (cond
      [(null? (cdr ls)) 
       (car ls)]
      [else
       (let-bind 
         ([(an as at ae) (car ls)]
          [(bn bs bt be) (func-c (cdr ls))])
         (if 
           (list-length< ae be)
           (let
             ([f (lambda (x) 
                   (cond 
                     [(= x at) bs]
                     [(+ x bn (if (> x at) -1 0))]))])
             (graph 
               (+ an bn -1) (f as) bt
               (list-concat (map-edges f ae) be)))
           (let
             ([f (lambda (x) 
                   (cond 
                     [(= x bs) at]
                     [(+ x an (if (> x bs) -1 0))]))])
             (graph 
               (+ an bn -1) as (f bt)
               (list-concat (map-edges f be) ae)))))]))

  (define (func-t ls)
    (cond
      [(null? (cdr ls)) 
       (car ls)]
      [else
       (let-bind 
         ([(an as at ae) (car ls)]
          [(bn bs bt be) (func-t (cdr ls))])
         (if 
           (list-length< ae be)
           (let
             ([f (lambda (x) 
                   (cond 
                     [(= x as) bs]
                     [else (+ x bn (if (> x as) -1 0))]))])
             (graph 
               (+ an bn -1) (f as) (f at)
               (list-concat (map-edges f ae) be)))
           (let
             ([f (lambda (x) 
                   (cond 
                     [(= x bs) as]
                     [else (+ an x (if (> x bs) -1 0))]))])
             (graph 
               (+ an bn -1) as at
               (list-concat (map-edges f be) ae)))))]))

  (define (func-loop ls)
    (cond
      [(null? (cdr ls)) 
       (car ls)]
      [else
       (let-bind 
         ([(an as at ae) (car ls)]
          [(bn bs bt be) (func-c (cdr ls))])
         (if (list-length< ae be)
           (let
             ([f (lambda (x) 
                   (cond 
                     [(= x as) bt]
                     [(= x at) bs]
                     [else 
                       (+ x bn 
                          (if (> x as) -1 0) 
                          (if (> x at) -1 0))]))])
             (graph 
               (+ an bn -2) (f as) (f at)
               (list-concat (map-edges f ae) be)))
           (let
             ([f (lambda (x) 
                   (cond 
                     [(= x bs) at]
                     [(= x bt) as]
                     [else 
                       (+ x an 
                          (if (> x bs) -1 0) 
                          (if (> x bt) -1 0))]))])
             (graph 
               (+ an bn -2) as at
               (list-concat (map-edges f be) ae)))))]))

  (define (range s t)
    (cond
      [(> s t) (range t s)]
      [(= s t) (list s)]
      [(< s t) (cons s (range (+ s 1) t))]))

  (define (my-eval c env)
    (define fs 
      `([c . ,func-c]
        [t . ,func-t]
        [loop . ,func-loop]))
    (cond
      [(number? c) c]
      [(symbol? c) 
       (cdr (assv c env))]
      [else 
        ((cdr (assv (car c) fs)) 
         (my-eval-range (cdr c) env))]))

  (define (my-eval-range c env)
    (cond
      [(and 
         (atom? (car c))
         (not (eqv? (car c) 'c)))
       (my-eval-range 
         `((range $ 1 ,(my-eval (car c) env)) . ,(cdr c))
         env)]
      [(and 
         (list? (car c))
         (eqv? 'range (caar c)))
       (let-bind 
         ([(_ v s t) (car c)])
         (map 
           (if (null? (cdr c)) 
             (lambda (x) 
               cactus-c)
             (lambda (x) 
               (my-eval 
                 (cadr c) 
                 (cons (cons v x) env))))
           (range (my-eval s env) (my-eval t env))))]
      [else 
        (map 
          (lambda (c) (my-eval c env)) 
          c)]))

  (let-bind 
    ([(n s t e) (my-eval l `((c . ,cactus-c)))])
    (graph 
      n 0 (- n 1)
      (map-edges 
        (lambda (x) 
          (cond 
            [(= s x) 0]
            [(= t x) (- n 1)]
            [else 
              (+ x 
                 (if (< x s) 1 0) 
                 (if (> x t) -1 0))]))
        e))))

(define (euler-path n es)

  (define (add-edge e u v)
    (let ([b (box #t)])
      (vector-set! e u (cons (cons v b) (vector-ref e u)))
      (vector-set! e v (cons (cons u b) (vector-ref e v)))))

  (define e
    (let ([r (make-vector (+ 1 n) '())])
      (let loop ([es es])
        (if 
          (null? es)
          r
          (begin
            (add-edge r (caar es) (cdar es))
            (loop (cdr es)))))))

  (define (dfs u ls)
    (let ([eu (vector-ref e u)])
      (if (null? eu) ls
        (let 
          ([v (caar eu)]
           [vb (cdar eu)])
          (vector-set! e u (cdr eu))
          (if (unbox vb)
            (begin
              (set-box! vb #f)
              (let 
                ([rs (cons v (dfs v ls))])
                (dfs u rs)))
            (dfs u ls))))))

  (define s
    (let loop ([s '()] [u 0])
      (if (= u n)
        (if (null? s) '(0) s)
        (loop 
          (if 
            (= 1 (modulo (length (vector-ref e u)) 2))
            (cons u s)
            s)
          (+ u 1)))))

  (for-each 
    (lambda (x) (add-edge e x n)) 
    s)

  (filter 
    (lambda (x) 
      (> (length x) 1))
    (list-split 
      (dfs n '()) 
      n)))

(let-bind 
  ([g (eval-cactus (parse (read-line)))]
   [(gn gs gt ge) g]
   [ans (euler-path gn ge)])

  (print gn " " (length ans))
  (for-each
    (lambda (p)
      (display (length p))
      (for-each 
        (lambda (u) 
          (display " ") 
          (display (+ u 1))) 
        p)
      (display "\n"))
    ans))

(exit)
