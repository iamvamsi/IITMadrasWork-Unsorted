(defun even (x) ( if   x ( if (= (mod (car x) 2) 0) ( cons (car x) ( even (cdr x) ) ) (even (cdr x)) ) x ) )



(defun red_1 (x) (	if x  (if (= (car x) 0 ) (cons 9 (red_1 ( cdr x ) ) ) ( cons (- (car x) 1) (cdr x)  ) ) x ) )

(defun div (x y) (- (/ (car x) (car y) ) (/ (mod (car x) (car y) ) (car y) )) )



(defun add_I (x y z) (if y 
						
							
							(if x		

								(cons (mod (+ (car x) (car y) (car z) ) 10) 
									 (add_I 
											(cdr x) 
											(cdr y) 
											(list (
													div 
														 (list (+ (car x) (car y) (car z) ) )
														 '(10) 
														
												  )
											)
								 	)
								)
								(
									cons 
									 (mod (+  (car y) (car z) ) 10) 
									 (add_I 
											 x
											(cdr y) 
											(list (
													div 
														 (list (+ (car y) (car z) ) )
														 '(10) 
														
												  )
											)
								 	)
								)
							
							)	
						
							

							 y 
					  )
)


(defun sing_mult (x y z) 
						(if y 
							(cons 
								(  mod ( + (* (car y) x ) (car z) )  10  )  
								(
									sing_mult  
												x 
												(cdr y) 
												(list  (
															div 
																	(list ( + (* (car y) x ) (car z) ) )
																	'(10)
														)
												)
								)
							) 
							y 
						)
)  
(defun add_zero (x)
					(if
					x
					(reverse (cons 0 (reverse x)))
					x
					)
)
(defun mult (x y) ( if (cdr x) 
						( add_I 
									(sing_mult (car x) (add_zero y) '(0)) 
									(add_zero (cons 0 (mult (cdr x)  y ) ) )
									'(0) 
						) 
						(
									sing_mult (car x) (add_zero y) '(0) 	
						)
				  ) 
)

(defun zero (x) 
				(if x
					(if (zero (cdr x))
							(if (= (car x) 0) '(1) ()  )	
							()
					)
					'(1)
				)
)
	

(defun one (x) 
				( if (= (car x) 1)
					(zero (cdr x) )
					()
				)
)
(defun factorial (x) ( 
						
						if(one x )
						'(1)
						(mult x (factorial (red_1  x ) ) ) 
						
						
					 )
 )
(defun Remove_zero (x)
				(if
					(= (car x) 0)
					(Remove_zero (cdr x) )
					x
				)
)
(defun Fact (x)
			(Remove_zero (reverse (factorial (reverse x)))))

BST ------------------------------------------------------------------

(defun make_leaf (x)
					(list x)
)



(defun make_node (x y z)
				(list x y z)
)


(defun make_empty_BST
	nil
)
(defun Getnode_element (x)
				(first x)
)
(defun Getnode_left (x)
				(second x)
)



(defun Getnode_right (x)
				(third x)
)




(defun Getleaf_element (x)
	(first x)		

)



(defun Is_leaf (x)
				(and (listp x) (= (list-length x) 1))
)	



	
(defun Is_node (x)
				(and (listp	x)	(=	(list-length	x)	3))
)




(defun BSTleaf_delete (x y)
			(if (= y (Getleaf_element	x))
				(make_empty_BST )
				x
			)
)
(defun Is_empty (x)
		(null x)
)


(defun BSTnode_Delete (B x) 
	(let
      ((elmt  (Getnode_element B))
       (left  (Getnode_left    B))
       (right (Getnode_right   B)))
    (if (<= x elmt)



	(if (Is_leaf left)
	    (if (= x (Getleaf_element left))
		right
	      B)
	  (make_node elmt (BSTnode_delete left x) right))




      (if (Is_leaf right)
	  (if (= x (Getleaf_element right))
	      left
	      B)
	(make_node elmt left (BSTnode_delete right x))))))








(defun BST_remove (x y)
		(if (Is_empty x)
			x
			(if (Is_leaf x)
				(BSTleaf_delete	x y)
				(BSTnode_delete	x y)
			)
		)
)



(defun BST_insert (B x)
  "Insert x into BST B."
  (if (Is_empty B)
      (make_leaf x)
    (BST_nonempty_insert B x)))

(defun BST_nonempty_insert (B x)
  "Insert x into nonempty BST B."
  (if (Is_leaf B)
      (BST_leaf_insert B x)
    (let ((elmt  (Getnode_element B))
	  (left  (Getnode_left    B))
	  (right (Getnode_right   B)))
      (if (<= x (Getnode_element B))
	  (make_node elmt
			      (BST_nonempty_insert (Getnode_left B) x)
			      right)
	(make_node elmt
			    left
			    (BST_nonempty_insert (Getnode_right B) x))))))

(defun BST_leaf_insert (L x)
  "Insert element x to a BST with only one leaf."
  (let ((elmt (Getleaf_element L)))
    (if (= x elmt)
	L
      (if (< x elmt)
	  (make_node x
			      (make_leaf x)
			      (make_leaf elmt))
	(make_node elmt
			    (make_leaf elmt)
			    (make_leaf x))))))











