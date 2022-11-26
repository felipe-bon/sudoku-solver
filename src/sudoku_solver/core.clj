(ns sudoku-solver.core
  (:gen-class)
  (:require [sudoku-io]))

(def SUDOKU-SIZE 9)
(def SUDOKU-GRID 3)

(defn line [v]
  (let [first-pos-line (* SUDOKU-SIZE
                          (quot v SUDOKU-SIZE))]
    (remove #(= % v)
            (range first-pos-line
                   (+ SUDOKU-SIZE
                      first-pos-line)))))

(defn column [v]
  (let [first-column (quot v SUDOKU-SIZE)]
    (remove #(= % v)
            (map #(+ % (mod v SUDOKU-SIZE))
                 (range 0
                        (* SUDOKU-SIZE SUDOKU-SIZE)
                        SUDOKU-SIZE)))))
; 12 13 14
; 21 22 23
; 30 31 32
(defn subgrid [v]
  (let [first-element-of-grid-line
        (* (quot v (* SUDOKU-GRID
                      SUDOKU-SIZE))
           (* SUDOKU-SIZE SUDOKU-GRID))
        mod-size-min-threshold (* (quot (mod v SUDOKU-SIZE)
                                        SUDOKU-GRID)
                                  SUDOKU-GRID)]
    (filter #(and (not= % v)
                  (<= mod-size-min-threshold
                      (mod % SUDOKU-SIZE)
                      (dec (+ mod-size-min-threshold SUDOKU-GRID))))
            (range first-element-of-grid-line
                   (+ first-element-of-grid-line
                      (* SUDOKU-GRID
                         SUDOKU-SIZE))))))

(defn line [v]
  (let [first-pos-line (- v
                          (mod v SUDOKU-SIZE))]
    (range first-pos-line
           (+ SUDOKU-SIZE
              first-pos-line))))

(defn sudoku-chuveirinho []
  (map #(into (sorted-set-by <) (conj (concat (subgrid %)
                                             (column %)
                                             (line %))
                                     %))
       (range 0
              (* SUDOKU-SIZE SUDOKU-SIZE))))

(defn foo
  "I don't do a whole lot."
  [x]
  (println x "Hello, World!"))
