;;; Guile script for testing out matrix operations
;;; Disclaimer : I'm not a very good scheme programmer

;;; Create a zero matrix

(define (zero M)
  (define (zero_loop M i j)
    (if (< i 4)
      (if (< j 4) (begin
		    (set_m M i j 0.0)
		    (zero_loop M i (+ j 1))
		    )
		    (zero_loop M (+ i 1) 0)
	  )
      )
   )
  (zero_loop M 0 0)
)

;;; Create an identity matrix

(define (identity M)
  (define (iloop M i)
    (if (< i 4) (begin
		  (set_m M i i 1.0)
		  (iloop M (+ i 1))))
  )
  (begin
    (zero M)
    (iloop M 0))
)

;;; Rotate around x axis

(define (rotx M r) 
  (define temp (new_matrix))
  (define rd (/ (* r 3.14159) 180.0))
  (begin 
    (zero temp)
    (set_m temp 0 0 1.0)
    (set_m temp 1 1 (cos rd))
    (set_m temp 1 2 (- 0 (sin rd)))
    (set_m temp 2 1 (sin rd))
    (set_m temp 2 2 (cos rd))
    (set_m temp 3 3 1.0)
    (mat_mult M temp M)
    (destroy_matrix temp)
    )
)

;;; Rotate around y axis

(define (roty M r)
  (define temp (new_matrix))
  (define rd (/ (* r 3.14159) 180.0))
  (begin 
    (zero temp)
    (set_m temp 1 1 1.0)
    (set_m temp 0 0 (cos rd))
    (set_m temp 0 2 (sin rd))
    (set_m temp 2 0 (- 0 (sin rd)))
    (set_m temp 2 2 (cos rd))
    (set_m temp 3 3 1.0)
    (mat_mult M temp M)
    (destroy_matrix temp)
    )
)

;;; Rotate around z axis

(define (rotz M r)
  (define temp (new_matrix))
  (define rd (/ (* r 3.14159) 180.0))
  (begin 
    (zero temp)
    (set_m temp 0 0 (cos rd))
    (set_m temp 0 1 (- 0 (sin rd)))
    (set_m temp 1 0 (sin rd))
    (set_m temp 1 1 (cos rd))
    (set_m temp 2 2 1.0)
    (set_m temp 3 3 1.0)
    (mat_mult M temp M)
    (destroy_matrix temp)
    )
)

;;; Scale a matrix

(define (scale M s)
  (define temp (new_matrix))
  (define (sloop m i s) 
    (if (< i 4) (begin
		  (set_m m i i s)
		  (sloop m (+ i 1) s)))
    )
    (begin
      (zero temp)
      (sloop temp 0 s)
      (mat_mult M temp M)
      (destroy_matrix temp)
      )
)

;;; Make a matrix with random elements

(define (randmat M) 
  (define (rand_loop M i j)
    (if (< i 4)
      (if (< j 4) (begin
		    (set_m M i j (drand48))
		    (rand_loop M i (+ j 1))
		    )
		    (rand_loop M (+ i 1) 0)
	  )
      )
   )
  (rand_loop M 0 0)
)


;;; Now we'll hammer on things a little bit just to make
;;; sure everything works.

(display "Testing matrix program...\n")

(define M1 (new_matrix))
(identity M1)
(print_matrix M1)
(display "Rotate-x 45 degrees\n")
(rotx M1 45)
(print_matrix M1)
(display "Rotate y 30 degrees\n")
(roty M1 30)
(print_matrix M1)
(display "Rotate z 15 degrees\n")
(rotz M1 15)
(print_matrix M1)
(display "Scale 0.5\n")
(scale M1 0.5)
(print_matrix M1)

;;; Create a vector

(define v (createv 1 2 3 4))
(display "Created vector (1 2 3 4)\n")
(define t (createv 0 0 0 0))

;;; Rotating ...
(display "Rotating...\n")
(define (rot_test M v t i) 
  (if (< i 360) (begin
		  (rotx M 1)
		  (rotz M -0.5)
		  (transform M v t)
		  (rot_test M v t (+ i 1)))))
(rot_test M1 v t 0)
(printv t)

;;; Create some matrices

(display "\nCreating 2000 matrices\n")

(define (create_matrix i)
  (if (< i 2000) (cons (new_matrix) (create_matrix (+ i 1)))
      (list)
)
)

(define M_list (create_matrix 0))

;;; Put random values in them

(define (make_random ML)
  (if (null? ML) () (begin
		      (randmat (car ML))
		      (make_random (cdr ML)))
)
)

(make_random M_list)

(zero M1)
(display "Adding them together (in Guile)\n")

(define (add_mat M ML)
  (define (add_two m1 m2 i j)
    (if (< i 4)
      (if (< j 4) (begin
		    (set_m m1 i j (+ (get_m m1 i j) (get_m m2 i j)))
		    (add_two m1 m2 i (+ j 1)))
	  (add_two m1 m2 (+ i 1) 0)
	  )
      )
    )
  (if (null? ML) () (begin 
		      (add_two M (car ML) 0 0)
		      (add_mat M (cdr ML))
		      )
      )
  )

(add_mat M1 M_list)
(print_matrix M1)

(display "Doing 2000 multiplications (mostly in C)\n")
(define M (new_matrix))
(randmat M)

(define (mul_mat m ML) 
  (if (null? ML) () (begin
		      (mat_mult m (car ML) m)
		      (mul_mat m (cdr ML))
		      )
      )
  )

(mul_mat M M_list)		     

(display "Cleaning up\n")

(define (cleanup ML) 
  (if (null? ML) () (begin
		      (destroy_matrix (car ML))
		      (cleanup (cdr ML))
		      )
      )
  )


