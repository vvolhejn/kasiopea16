(ns c2.core
  (:gen-class))

(defn read-numbers []
    (map read-string
        (clojure.string/split (read-line) #"\s+")))

(defn solve [[h & hs] [k & ks] res]
    (if (not h) res
        (if (not k) -1 (recur
            (if (<= h k)
                hs
                (conj hs h))
            ks
            (+ res (if (<= h k) k 0))))))

(defn test-case []
    (let [[n m] (read-numbers)
          heads (read-numbers)
          knights (read-numbers)]
          (let [res (solve heads knights 0)]
            (println res))))

(defn -main
  [& args]
  (let [tn (first (read-numbers))]
    (dotimes [i tn] (test-case))))
