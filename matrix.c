/*==========================================
  A matrix will be a 4xN array of doubles
  Each column will represent an [x, y, z, 1] point.
  For multiplication purposes, consider the rows like so:
  x0  x1      xn
  y0  y1      yn
  z0  z1  ... zn
  1  1        1
  ==========================================*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "matrix.h"

/*-------------- void print_matrix() --------------
Inputs:  struct matrix *m

print the matrix such that it looks like
the template in the top comment
*/
void print_matrix(struct matrix *m) {
  int r = m->rows;
  int lC = m->lastcol;
  // matrix entry
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < lC; j++) {
      printf("%.2f ", m->m[i][j]);
    }
    printf("\n");
  }
}

/*-------------- void ident() --------------
Inputs:  struct matrix *m <-- assumes m is a square matrix

turns m in to an identity matrix
*/
void ident(struct matrix *m) {
  int r = m->rows;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < r; j++) {
      m->m[i][j] = 0;
      if (i == j) m->m[i][j] = 1;
    }
  }
  m->lastcol = r;
}

/*-------------- void matrix_mult() --------------
Inputs:  struct matrix *a
         struct matrix *b

multiply a by b, modifying b to be the product
a*b -> b
*/
void matrix_mult(struct matrix *a, struct matrix *b) {
  int rA = a->rows;
  int rcAB = a->cols;
  int cB = b->cols;

  struct matrix *temp; 
  temp = new_matrix(rA, cB);
  temp->lastcol = b->lastcol;

  double sum = 0;
  for (int i = 0; i < rA; i++) {
    for (int j = 0; j < cB; j++) {
      for (int k = 0; k < rcAB; k++) {
        sum += (a->m[i][k] * b->m[k][j]);
      }
      temp->m[i][j] = sum;
      sum = 0;    
    }
  }

  copy_matrix(temp, b);
  free_matrix(temp);
}

/*-------------- void clear_matrix() --------------
Inputs:  struct matrix *a

clears entry in a, a becomes a null matrix
*/
void clear_matrix(struct matrix *a) {
  int r = a->rows;
  int c = a->cols;
  for (int i = 0; i < r; i++) {
    for (int j = 0; j < c; j++) {
      a->m[i][j] = 0;
    }
  }
  a->lastcol = 0;
}

/*===============================================
  These Functions do not need to be modified
  ===============================================*/

/*-------------- struct matrix *new_matrix() --------------
Inputs:  int rows
         int cols

Once allocated, access the matrix as follows:
m->m[r][c]=something;
if (m->lastcol)...
*/
struct matrix *new_matrix(int rows, int cols) {
  double **tmp;
  int i;
  struct matrix *m;

  tmp = (double **)malloc(rows * sizeof(double *));
  for (i=0;i<rows;i++) {
      tmp[i]=(double *)malloc(cols * sizeof(double));
    }

  m=(struct matrix *)malloc(sizeof(struct matrix));
  m->m=tmp;
  m->rows = rows;
  m->cols = cols;
  m->lastcol = 0;

  return m;
}



/*-------------- void free_matrix() --------------
Inputs:  struct matrix *m
Returns:

1. free individual rows
2. free array holding row pointers
3. free actual matrix
*/
void free_matrix(struct matrix *m) {

  int i;
  for (i=0;i<m->rows;i++) {
      free(m->m[i]);
    }
  free(m->m);
  free(m);
}


/*======== void grow_matrix() ==========
Inputs:  struct matrix *m
         int newcols 
Returns: 

Reallocates the memory for m->m such that it now has
newcols number of collumns
====================*/
void grow_matrix(struct matrix *m, int newcols) {
  int i;
  for (i=0;i<m->rows;i++) {
      m->m[i] = realloc(m->m[i],newcols*sizeof(double));
  }
  m->cols = newcols;
}


/*-------------- void copy_matrix() --------------
Inputs:  struct matrix *a
         struct matrix *b 
Returns: 

copy matrix a to matrix b
*/
void copy_matrix(struct matrix *a, struct matrix *b) {

  int r, c;

  for (r=0; r < a->rows; r++) 
    for (c=0; c < a->cols; c++)  
      b->m[r][c] = a->m[r][c];  
  
  b->lastcol = a->lastcol;
}
