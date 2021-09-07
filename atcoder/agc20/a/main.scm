(read)
(display (if (= (modulo (abs (- (read) (read))) 2) 1) "Borys" "Alice"))
