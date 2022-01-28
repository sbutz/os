#include "matrix.h"

extern matrix *createMatrix(int x, int y)  {
    register i, j;
    matrix *newMatrix = (matrix *)malloc(sizeof(matrix));
    newMatrix->width = y, newMatrix->height = x;
    newMatrix->elements = createList();
    for (i = 0; i < x;  ++i)
        for (j = 0;  j < y;  ++j)  {
            double *value = (double *)malloc(sizeof(double));  
            *value = 0.0L;
            insertElement(newMatrix->elements, value);
        }
    return newMatrix;
}

extern void setValue(matrix *target, int x, int y, double value)  {
    double *vp = malloc(sizeof(double));
    *vp = value;
	node *position = getNode( target->elements,  
                             x * target->width + y );
	position->element = vp;
}

extern double getValue(matrix *source, int x, int y)  {
	node *position = getNode( source->elements, 
                             x * source->width + y );
	return *(double *)position->element;
}  

extern matrix *mult(matrix *m1, matrix *m2)  {
    register i, j;
	matrix *product = createMatrix(m1->height, m2->width);
	for (i = 0;  i < product->height;  ++i)       
	  for (j = 0;  j < product->width;  ++j)  {
            register k;  double sum = 0.0;
            for (k = 0; k < m1->width; ++k) { 
                sum = sum + getValue(m1, i, k) * getValue(m2, k, j);
            } 
            setValue(product, i, j, sum);
        }
	return product;
}

#include <pthread.h>

struct param_t {
  int i, j;
  matrix *m1, *m2, *product;
};

void *peermult(void *data)  {
   matrix *m1, *m2, *product;  int i, j;
   register k;  double sum = 0.0;
   m1 = ((struct param_t *)data)->m1;
   m2 = ((struct param_t *)data)->m2;
   product = ((struct param_t *)data)->product;
   i = ((struct param_t *)data)->i;
   j = ((struct param_t *)data)->j;  
   for (k = 0; k < m1->width; ++k) { 
     sum = sum + getValue(m1, i, k) * getValue(m2, k, j);
   } 
   setValue(product, i, j, sum);
}

extern matrix *parmult(matrix *m1, matrix *m2)  {
    register i, j;
    matrix *product = createMatrix(m1->height, m2->width);
    pthread_t *multipliers = (pthread_t *)
        malloc(sizeof(pthread_t) * product->width * product->height);
    for (i = 0;  i < product->height;  ++i)       
      for (j = 0;  j < product->width;  ++j)  {
        struct param_t *p = (struct param_t *)malloc(sizeof(struct param_t));
        p->i = i;  p->j = j;  p->m1 = m1;  p->m2 = m2;
        p->product = product;
        pthread_create( &multipliers[i * product->width + j], NULL,
                        peermult, p );
    }
    for (i = 0;  i < product->width * product->height;  ++i)   {
       pthread_join(multipliers[i], NULL);
    }
    return product;
}

extern matrix *forkmult(matrix *m1, matrix *m2)  {
    int i, j, k, id, size = m1->height * m2->width;
    matrix *product = createMatrix(m1->height, m2->width);
    int **pipes = (int **)malloc(sizeof(int *) * size);
    for(k = 0;  k < size;  ++k)  { 
       pipes[k] = (int *)malloc(sizeof(int) * 2);
       pipe(pipes[k]);
    }
    for (k = 0, i = 0;  i < product->height;  ++i)   
      for (j = 0;  j < product->width;  ++j)  {
      id = fork();
      if (id != 0)  {
       double value;
       close(pipes[k][1]);
       read(pipes[k++][0], &value, sizeof(double));
       setValue(product, i, j, value);
      } else  {
       int l; double sum = 0.0;
       close(pipes[k][0]);
       for (l = 0;  l < m1->width; ++l) 
         sum = sum + getValue(m1, i, l) * getValue(m2, l, j);
       write(pipes[k][1], &sum, sizeof(double));
       exit(0);
      }
    }
    return product;
}

extern void printMatrix(matrix *m)  {
    register z, s;
    for (z = 0;  z < m->height;  ++z)  {
        for (s = 0;  s < m->width;  ++s) 
            printf("%4.1f ", getValue(m, z, s));
        printf("\n");
    }
}

