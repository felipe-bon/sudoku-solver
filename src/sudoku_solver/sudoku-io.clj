(ns sudoku-io
    (:gen-class))

(defn print-sudoku
  ([sudoku-adjacency-list] (print-sudoku sudoku-adjacency-list 0))
  ([sudoku-adjacency-list acc]
   (if (and (mod acc 9) (not= acc 0))
       (print "\n"))
   (if (= 0 (mod acc 3)) (print "|"))
   (print (first (first sudoku-adjacency-list)))
   (print-sudoku (rest sudoku-adjacency-list)
                 (inc acc))))
