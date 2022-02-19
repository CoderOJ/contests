(define answers 
  '(AKIHABARA
    AKIHABAR 
    AKIHABRA 
    AKIHABR
    AKIHBARA
    AKIHBAR
    AKIHBRA
    AKIHBR
    KIHABARA
    KIHABAR
    KIHABRA
    KIHABR
    KIHBARA
    KIHBAR
    KIHBRA
    KIHBR))

(display (if (memv (read) answers) "YES" "NO"))
