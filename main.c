#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"

int main() {
  // checking matrix manipulation 
  struct matrix *edges2;
  edges2 = new_matrix(4, 4);
  
  printf("Testing add_edge. Adding (1, 2, 3), (4, 5, 6) m2 =\n");
  add_edge(edges2, 1, 2, 3, 4, 5, 6);
  print_matrix(edges2);
  printf("\n");

  printf("Testing ident. m1 =\n");
  struct matrix *edges1; 
  edges1 = new_matrix(4,4);
  copy_matrix(edges2, edges1);
  ident(edges1);
  print_matrix(edges1);
  printf("\n");

  printf("Testing Matrix mult. m1 * m2 =\n");
  matrix_mult(edges1, edges2);
  print_matrix(edges2);
  printf("\n");

  printf("Testing Matrix mult. m1 =\n");
  clear_matrix( edges1 );
  add_edge(edges1, 1, 2, 3, 4, 5, 6);
  add_edge(edges1, 7, 8, 9, 10, 11, 12);
  print_matrix(edges1);
  printf("\n");

  printf("Testing Matrix mult. m1 * m2 =\n");
  matrix_mult(edges1, edges2);
  print_matrix(edges2);
  printf("\n");

  free_matrix( edges2 );
  free_matrix( edges1 );

  // checking matrices in images
  screen s;
  color c;
  // cyan
  c.blue = 255;
  c.green = 100;
  c.red = 100;
  struct matrix *lines;
  lines = new_matrix(4, 100);
  clear_screen(s);
  // image-generating code
  for (int i = 0; i < 15; i++) {
    double fact = pow(1.1,i);
    double dX = (fact-1)*250/fact;
    double dY = (fact-1)*187/fact;
    add_edge(lines,35.00/fact+dX,62.00/fact+dY,0,250/fact+dX,434/fact+dY,0);
    add_edge(lines,35.00/fact+dX,62.00/fact+dY,0,467/fact+dX,62/fact+dY,0);
    add_edge(lines,467.00/fact+dX,62.00/fact+dY,0,250/fact+dX,434/fact+dY,0);
    add_edge(lines,142.00/fact+dX,248.00/fact+dY,0,250/fact+dX,62/fact+dY,0);
    add_edge(lines,358.00/fact+dX,248.00/fact+dY,0,250/fact+dX,62/fact+dY,0);
    add_edge(lines,358.00/fact+dX,248.00/fact+dY,0,142/fact+dX,248/fact+dY,0);
  }
  
  draw_lines(lines, s, c);

  display(s);
  save_extension(s, "Pascalian.png");
}  
