#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

char* pathreader(FILE *f, char *path)
{
  char vector_path[2000];
  fscanf (f, " %s", vector_path);
  path = (char*) malloc (2000 * sizeof(char));
  strcpy(path, vector_path);
  return path;
}

float euclidiana (float *test, float *treino, int columns) //retorna a distancia euclidiana
  {
    int k=0;
    float distance=0, sum=0;
    for (k = 0; k < columns - 1; k++)
        {
          sum = test[k] - treino[k];
          sum = sum*sum;
          distance = distance + sum;
        }
    return sqrt(distance);
  }

float mainkowski (float *test, float *treino, int columns, float r) //retorna a distancia mainkowski
  {
    int k = 0;
    float distance=0, sum = 0;

    for (k = 0; k < columns - 1; k++)
        {
          sum += pow((test[k] - treino[k]), r);
        }
    return pow(sum, 1.0/r);
  }

float chebyshev (float *test, float *treino, int columns)//retorna a distancia chebyshev
  {
    int k = 0;
    float aux=0, aux2 = 0;

    for (k = 0; k < columns; k++)
        {
          aux = abs(test[k] - treino[k]);
                if (aux > aux2)
                  {
                    aux2 = aux;
                  }
        }
    return aux2;

  }

void BubbleSort (float *v, int n) //função de organização vetorial
{
  int i, j;
  float aux;
  for (j = n; j > 0; j--)
    {
      for (i = 0; i < j; i++)
        {
          if (v[i] > v [i + 1])
            {
              aux = v[i];
              v[i] = v[i+1];
              v[i+1] = aux;
            }
        }
    }
}

float find_label(int lines_trainning, float labels[lines_trainning], int columns, int k, float **data_traine)
{
  int w, i, j;
  float vetor_N_organizado[lines_trainning], close_labels[k], test_label;
  for(w = 0; w < lines_trainning; w++)
    {
      vetor_N_organizado[w] = labels[w];
    }
  BubbleSort(labels, lines_trainning);
    for(i = 1; i < k+1; i++) // OLHAR O I = 1
      {
        for(j = 0; j < lines_trainning; j++)
          {
            if(labels[i] == vetor_N_organizado[j])
              {
                close_labels[i] = data_traine[j][columns-1];
              }
            }
       }
int repeat = 0;
float aux = 0;
int m=0, l=0;

for(m = 0; m < k+1; m++)
  {
    for(l = 0; l < k+1; l++)
      {
        if (close_labels[m] == close_labels[l])
          {
            repeat++;
          }

      }
      if (repeat > aux)
        {
          aux = repeat;
          test_label = close_labels[m];
        }
  }
return test_label;
}

int n_rotulos (float **test, int lines_test, int columns)
{
int i = 0, j = 0, k = 0;
  for(i = 0; i < lines_test; i++)
    {
      if (test[i][columns-1] > k)
        {
          k = test[i][columns-1];
        }
    }
return k;
}


void diff_labels(float **test, int n_labels, int columns, int lines_test, float *rot)
{
  int i = 0;
  float x = 1.0;

for(i = 0; i< n_labels; i++)
    {
      rot[i] = x++;
    }
}
void test_labels(float **test, float *old, int lines_test, int columns)
  {
    int i = 0;
    for(i = 0; i < lines_test; i++)
      {
        old[i] = test[i][columns - 1];
      }
  }

void matriz_confusao(int **matriz_confusa, float *new, float *old, float *label, int lines_test, int n_rotulos)
{
int i, j, k;
for (k = 0; k < n_rotulos; k++)
  {
    for (i = 0; i < lines_test; i++)
      {
          if (new[i] == old[i])
            {
              matriz_confusa[k][k]++;
            }
          else
            {
              for(j = 0; j < n_rotulos; j++)
                {
                  if(new[i] == label[j])
                    {
                      matriz_confusa[k][j]++;
                    }
                }
            }
      }
  }
}

float acuracia (int **matriz_confusao, int lines_test, int n_labels)
  {
    int i, j;
    float sum;
    float acuracia;
for(i=0; i< n_labels; i++)
{
  for(j = 0; j< n_labels; j++)
    {
      if (i == j)
      {
        sum += matriz_confusao[i][j];
      }
      acuracia = sum/lines_test;

      return acuracia;
    }
}
}
void main()
{
  FILE *fr;
  char info[] = "config.txt";
  fr = fopen(info,"r");
    if(fr == NULL)
      {
        printf("Erro!");
        exit(1);
      }
  char *test_path;
  char *traine_path;
  char *prediction_path;
  char *path;

  traine_path = pathreader(fr, path);

  test_path = pathreader(fr, path);

  prediction_path = pathreader(fr, path);

  fclose(fr);

  FILE *fp;
  FILE *fp_test;
  int lines = 0, columns = 1; //as colunas iniciam como 1 para contabilizar a última coluna que não termina com vírgula;
  char c, d;
  fp_test = fopen(test_path, "r");
  if (fp_test == NULL)
  {
    printf("ERRO!\n");
    exit(1);
  }
  fp = fopen(traine_path, "r");
    if (fp == NULL)
      {
        printf("ERRO!");
      }
  do
    {
      if (c == '\n')
        {
          lines++;
        }
    }
  while(fread(&c, sizeof(char),1, fp));
  rewind(fp);
  do
    {
      if(d == ',')
      {
        columns++;
      }
      if(d == '\n')
        {
          break;
        }
    }while(fread(&d, sizeof(char),1,fp));
  rewind(fp);

  int i, j=0;
  float **data;
  data = (float**) malloc (lines * sizeof(float *));
  for (i = 0; i < lines; i++)
    {
      data[i] = (float*) malloc (columns * sizeof(float*));
    }

for (i=0; i < lines; i++)
{
  for (j=0; j< columns;j++)
    {
      fscanf(fp, "%f%*c", &data[i][j]);
    }
}
float **data_test;
char e;
int lines_test = 0;
do
  {
    if (e == '\n')
      {
        lines_test++;
      }
  }
while(fread(&e, sizeof(char),1, fp_test));
rewind(fp_test);
data_test = (float **) malloc (lines * sizeof(float *));

for (i = 0; i < lines; i++)
  {
    data_test[i] = (float*) malloc (columns * sizeof(float*));
  }

int y, z;
for (z=0; z < lines; z++)
{
for (y=0; y < columns; y++)
  {
    fscanf(fp_test, "%f%*c", &data_test[z][y]);
  }
}
fclose(fp_test);
fclose(fp);
char junk[1024], type;
int k=0;
float r;
fr = fopen(info,"r");
    if(fr == NULL)
      {
        printf("Erro!");
        exit(1);
      }

int lines_file = 0;
char o;
do
  {
    if (o == '\n')
      {
        lines_file++;
      }
  }while(fread(&o, sizeof(char),1, fr));
  rewind(fr);

int n_labels;
n_labels = n_rotulos(data_test, lines_test, columns);
float *diff_rot;

diff_rot = (float *) malloc (n_labels * sizeof(float *));
diff_labels(data_test, n_labels, columns, lines_test, diff_rot);

float dist[lines], label, all_labels[lines_test];
int contador;
int **confusa;
confusa = (int**) malloc (n_labels * sizeof(int*));
for(i = 0; i < n_labels; i++)
  {
    confusa[i] = (int*) malloc (n_labels * sizeof(int*));
  }

  for(j = 0; j < n_labels; j++)
    {
      for(i = 0; i < n_labels; i++)
      {
        confusa[i][j] = 0;
      }
   }

float old[lines], acc;
FILE *out;
char *out_path;

int counter;
fgets(junk, sizeof(junk), fr);
fgets(junk, sizeof(junk), fr);
fgets(junk, sizeof(junk), fr);
for(counter = 1; counter < lines_file - 2; counter++)
{
  out_path = (char *) malloc (200 * sizeof(char));
  sprintf (out_path, "%spredicao_%i.txt", prediction_path, counter);
  fscanf (fr, " %i%*c%*c %c", &k, &type);
  if (type == 'M')
    {
      fscanf(fr, ", %f", &r);

    }
  else
    {
      fgetc(fr);
    }

 switch(type)
      {
        case 'E':
        for(i = 0; i < lines_test; i++)
          {
            for(j=0; j < lines; j++)
              {
                dist[j] = euclidiana(data_test[i], data[j],columns-1);
              }
                label = find_label(lines, dist, columns, k, data);
                all_labels[i] = label;
              }

          test_labels(data_test, old, lines_test, columns);
          matriz_confusao(confusa, all_labels, old, diff_rot, lines_test, n_labels);
          acc = acuracia(confusa, lines_test, n_labels);

          out = fopen(out_path, "w");
              fprintf(out, "%.2f \n", acc);
              fprintf(out, "%c", '\n');

              for(i = 0; i < n_labels; i++)
                {
                  for(j = 0; j < n_labels; j++)
                    {
                      fprintf(out, "%i ", confusa[i][j]);
                    }
                  fprintf(out, "%c", '\n');
                }
              fprintf(out, "%c", '\n');

              for(i = 0; i < lines_test; i++)
                {
                  fprintf(out, "%i\n", (int) all_labels[i]);
                }
              fclose(out);
          break;

          case 'M':
          for(i = 0; i < lines_test; i++)
            {
              for(j=0; j < lines; j++)
                {
                  dist[j] = mainkowski(data_test[i], data[j],columns-1, r);
                }
              label = find_label(lines, dist, columns, k, data);
              all_labels[i] = label;
            }
            test_labels(data_test, old, lines_test, columns);
            matriz_confusao(confusa, all_labels, old, diff_rot, lines_test, n_labels);
            acc = acuracia(confusa, lines_test, n_labels);

            out = fopen(out_path, "w");
                fprintf(out, "%.2f \n", acc);
                fprintf(out, "%c", '\n');

                for(i = 0; i < n_labels; i++)
                  {
                    for(j = 0; j < n_labels; j++)
                      {
                        fprintf(out, "%i ", confusa[i][j]);
                      }
                    fprintf(out, "%c", '\n');
                  }
                fprintf(out, "%c", '\n');

                for(i = 0; i < lines_test; i++)
                  {
                    fprintf(out, "%i\n", (int) all_labels[i]);
                  }
              fclose(out);
          break;

          case 'C':
          for(i = 0; i < lines_test; i++)
            {
              for(j=0; j < lines; j++)
                {
                  dist[j] = chebyshev(data_test[i], data[j],columns-1);
                }
              label = find_label(lines, dist, columns, k, data);
              all_labels[i] = label;
            }
            test_labels(data_test, old, lines_test, columns);
            matriz_confusao(confusa, all_labels, old, diff_rot, lines_test, n_labels);
            acc = acuracia(confusa, lines_test, n_labels);

            out = fopen(out_path, "w");
                fprintf(out, "%.2f \n", acc);
                fprintf(out, "%c", '\n');

                for(i = 0; i < n_labels; i++)
                  {
                    for(j = 0; j < n_labels; j++)
                      {
                        fprintf(out, "%i ", confusa[i][j]);
                      }
                    fprintf(out, "%c", '\n');
                  }
                fprintf(out, "%c", '\n');

                for(i = 0; i < lines_test; i++)
                  {
                    fprintf(out, "%i\n", (int) all_labels[i]);
                  }
              fclose(out);
          break;

          default:
          printf("Valor inválido!\n");
      }
  }
}







/*
        free(test_path);
        free(traine_path);
        free(prediction_path);
        free(path);
        for (i=0; i < lines; i++);
        {
          free(data[i]);
          }
          for (i=0; i < lines_test; i++);
          {
           free(data_test[i]);
            }
          free(data);
          free(data_test);
//free(distances);
*/
