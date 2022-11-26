(ns sudoku-solver.adjacency-test
  (:require [clojure.test :refer :all]
            [sudoku-solver.core :refer :all]))

(deftest adjacency-subgrid
  (testing
   (is (= (which-subgrid 1)
          {:x 0 :y 0}))
    (is  (= (which-subgrid 4)
            {:x 1 :y 0}))
    (is  (= (which-subgrid 80)
            {:x 2 :y 2}))
    (is  (= (which-subgrid 35)
            {:x 2 :y 1}))
    (is  (= (which-subgrid 31)
            {:x 1 :y 1}))
    (is (same-subgrid 0 1))
    (is (same-subgrid 0 9))
    (is (same-subgrid 0 10))
    (is (same-subgrid 0 20))
    (is (same-subgrid 30 31))
    (is (same-subgrid 30 40))
    (is (same-subgrid 30 50))))

(deftest adjacency-line
  (testing
   (is (same-line 0 1))
    (is (same-line 1 0))
    (is (same-line 75 74))
    (is (same-line 34 35))))

(deftest adjacency-coll
  (testing
      (is (same-coll 0 9))
    (is (same-coll 9 0))
    (is (same-coll 35 44))
    (is (same-coll 77 68))))
