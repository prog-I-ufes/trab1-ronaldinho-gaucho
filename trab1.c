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
  //printf(" %s", path);
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
    for(i = 0; i < k+1; i++)
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
            //printf(" %f\n",close_labels);
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
  //printf("%i \n ",lines);
  //printf("%i \n ",columns);
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
      //printf("%f ", data[i][j]);
    }
//  printf("\n");
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
    //printf("%f ", data_test[i][j]);
  }
//printf("\n");
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

fgets(junk, sizeof(junk), fr);
fgets(junk, sizeof(junk), fr);
fgets(junk, sizeof(junk), fr);
fscanf (fr, " %i%*c%*c %c", &k, &type);

  if (type == 'M')
    {
      fscanf(fr, ", %f", &r);

    }
  else
    {
      fgetc(fr);
    }


float dist[lines], label, all_labels[lines_test];
int contador;

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
          printf("deu certo");
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
          break;

          default:
          printf("Valor inválido!\n");
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
}
