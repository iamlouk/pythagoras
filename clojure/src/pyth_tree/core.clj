(ns pyth-tree.core (:gen-class))

(import javax.swing.JFrame)
(import javax.swing.JPanel)
(import java.awt.Graphics2D)
(import java.awt.RenderingHints)

(def WIDTH  900)
(def HEIGHT 600)
(def START_WIDTH  150)
(def START_HEIGHT 150)
(def DEPTH 10)

(def it 0)
(def shift 0.0)

(defn rotate [x y alpha]
  (let [cos (Math/cos alpha) sin (Math/sin alpha)]
    { :x (- (* x cos) (* y sin))
      :y (+ (* x sin) (* y cos)) }))

(def startrect
  { :a { :x (- (/ WIDTH 2) (/ START_WIDTH 2)) :y (- HEIGHT START_HEIGHT) }
    :b { :x (+ (/ WIDTH 2) (/ START_WIDTH 2)) :y (- HEIGHT START_HEIGHT) }
    :c { :x (+ (/ WIDTH 2) (/ START_WIDTH 2)) :y HEIGHT                  }
    :d { :x (- (/ WIDTH 2) (/ START_WIDTH 2)) :y HEIGHT                  } })

(defn calc-t [rect]
  (let [rotated (rotate (/ (- ((rect :a) :x) ((rect :d) :x)) 2) (/ (- ((rect :a) :y) ((rect :d) :y)) 2) shift)] {
    :x (+ ((rect :a) :x) (/ (- ((rect :b) :x) ((rect :a) :x)) 2) (rotated :x))
    :y (+ ((rect :a) :y) (/ (- ((rect :b) :y) ((rect :a) :y)) 2) (rotated :y)) }))

(defn calc-left [rect t]
  { :a {
      :x (+ ((rect :a) :x) (- (t :x) ((rect :b) :x)))
      :y (+ ((rect :a) :y) (- (t :y) ((rect :b) :y))) }
    :b {
      :x (+ (t :x) (- (t :x) ((rect :b) :x)))
      :y (+ (t :y) (- (t :y) ((rect :b) :y))) }
    :c t
    :d (rect :a) })

(defn calc-right [rect t]
  { :a {
      :x (+ (t :x) (- (t :x) ((rect :a) :x)))
      :y (+ (t :y) (- (t :y) ((rect :a) :y))) }
    :b {
      :x (+ ((rect :b) :x) (- (t :x) ((rect :a) :x)))
      :y (+ ((rect :b) :y) (- (t :y) ((rect :a) :y))) }
    :c (rect :b)
    :d t })

(def tree [])
(defn calc-tree [rect i]
  (def tree (conj tree rect))
  (if (> i 0)
    (let [t (calc-t rect) i (dec i)]
      (calc-tree (calc-left rect t) i)
      (calc-tree (calc-right rect t) i))))

(defn draw-rect [g t rect]
  (.draw g (java.awt.geom.Line2D$Float. ((rect :a) :x) ((rect :a) :y) ((rect :b) :x) ((rect :b) :y)))
  (.draw g (java.awt.geom.Line2D$Float. ((rect :b) :x) ((rect :b) :y) ((rect :c) :x) ((rect :c) :y)))
  ; (.draw g (java.awt.geom.Line2D$Float. ((rect :c) :x) ((rect :c) :y) ((rect :d) :x) ((rect :d) :y)))
  (.draw g (java.awt.geom.Line2D$Float. ((rect :d) :x) ((rect :d) :y) ((rect :a) :x) ((rect :a) :y))))


(defn -main [& args]
  ; (defn hello [name]
  ;   (println (format "Hello, %s!" name)))
  ; (hello (nth args 0 (System/getenv "USER"))))

  (def frame (JFrame. "Pythagoras tree!"))
  (.setSize frame WIDTH HEIGHT)
  (.setDefaultCloseOperation frame JFrame/EXIT_ON_CLOSE)
  (.setVisible frame true)

  (def panel (proxy [JPanel] []
    (paint [graphics]
      (let [g (cast Graphics2D graphics) t (calc-t startrect)]
        (.setRenderingHint g RenderingHints/KEY_ANTIALIASING RenderingHints/VALUE_ANTIALIAS_ON)
        ; (print "repaint: " (time (run! (fn [rect] (draw-rect g t rect)) tree)))
        ; (java.lang.Thread/sleep (/ 1000 30))
        (def shift (* (Math/sin (* it 0.025)) 0.1))
        (def it (inc it))
        ; (println (format "Iteration: %d, Shift: %f" it shift))
        (def tree [])
        (calc-tree startrect DEPTH)
        (run! (fn [rect] (draw-rect g t rect)) tree)
        ; (print (format "calculating %d rects: %s" (int (java.lang.Math/pow 2.0 (double DEPTH))) (time (calc-tree startrect DEPTH))))
        (.repaint panel)))))

  (.setContentPane frame panel)
  (.revalidate frame))
