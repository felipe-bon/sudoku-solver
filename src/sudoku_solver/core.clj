(ns sudoku-solver.core
  (:gen-class))

(def SUDOKU-LINE-SIZE 9)
(def SUDOKU-GRID 3)
(def SUDOKU-SIZE (* SUDOKU-LINE-SIZE SUDOKU-LINE-SIZE))

(defn same-line [v w] (= (quot v SUDOKU-LINE-SIZE)
                         (quot w SUDOKU-LINE-SIZE)))

(defn same-coll [v w] (= (mod v SUDOKU-LINE-SIZE)
                         (mod w SUDOKU-LINE-SIZE)))

(defn which-subgrid [v] {:x (quot (mod v SUDOKU-LINE-SIZE)
                                   SUDOKU-GRID)
                         :y (quot v (* SUDOKU-GRID SUDOKU-LINE-SIZE))})

(defn same-subgrid [v w] (= (which-subgrid v)
                            (which-subgrid w)))

(defn is-adj
  [v w] (or (same-line v w)
            (same-coll v w)
            (same-subgrid v w)))

(defn sudoku-chuveirinho
  ([] (sudoku-chuveirinho 0))
  ([v] (if (< v SUDOKU-SIZE) (concat (list (remove #(not (is-adj v %))
                                                   (range 0 SUDOKU-SIZE)))
                                     (sudoku-chuveirinho (inc v))))))

