#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

//FUNÇÃO QUE QUE PEGA O PATH PARA SER USADO EM FOPEN//
char* pathreader(FILE *f, char *path)
{
  char vector_path[2000];
  fscanf (f, " %s", vector_path);//vetor armazena o path;
  path = (char*) malloc (2000 * sizeof(char));
  strcpy(path, vector_path); //coloca o valor do vector_path no path;
  return path;
}

//CALCULA A DISTANCIA EUCLIDIANA//
float euclidiana (float *test, float *treino, int columns)//aplicação da fórmula;
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

//CALCULA A DISTANCIA DE MAINKOWSKI//
float mainkowski (float *test, float *treino, int columns, float r)//aplicação da fórmula;
  {
    int k = 0;
    float distance=0, sum = 0;

    for (k = 0; k < columns - 1; k++)
        {
          sum += pow((test[k] - treino[k]), r);
        }
    return pow(sum, 1.0/r);
  }

//CALCULA A DISTANCIA DE CHEBYSHEV//
float chebyshev (float *test, float *treino, int columns)//aplicação da fórmula;
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

//FUNÇÃO DE ORGANIZAÇÃO VETORIAL//
void BubbleSort (float *v, int n)
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

//ACHA A AMOSTRA DE UM RÓTULA//
float find_label(int lines_trainning, float labels[lines_trainning], int columns, int k, float **data_traine)
{
  int w, i, j;
  float vetor_N_organizado[lines_trainning], close_labels[k], test_label;
  for(w = 0; w < lines_trainning; w++)
    {
      vetor_N_organizado[w] = labels[w]; //coloca o vetor com as distancias desorganizadas em outro vetor;
    }
  BubbleSort(labels, lines_trainning); //organiza as distancias em ordem crescente;
    for(i = 1; i < k+1; i++)
      {
        for(j = 0; j < lines_trainning; j++)
          {
            if(labels[i] == vetor_N_organizado[j]) //compara os vetores para achar a posição da distância, obtendo assim seu rótulo;
              {
                close_labels[i] = data_traine[j][columns-1];//armazena as K distancias mais proximas em outro vetor;
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
        if (close_labels[m] == close_labels[l])//compara o vetor com ele mesmo para achar elemntos iguais;
          {
            repeat++; //se certo rótulo se repetir, soma um;
          }
      }
    if (repeat > aux) //o rotulo que tiver um maior repeat;
        {
          aux = repeat; //atualiza o valor do auxiliar;
          test_label = close_labels[m]; //o que tiver a maior repetição ficará armazenada;
        }
  }
return test_label;//retorna o rótulo com base nas distâncias;
}

//CALCULA QUANTOS ROTULOS EXISTEM//
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
return k;//quantidade de rotulos;
}

//RETORNA UMA MATRIZ COM TODOS OS ROTULOS DIFERENTES//
void diff_labels(float **test, int n_labels, int columns, int lines_test, float *rot)
{
  int i = 0;
  float x = 1.0;

for(i = 0; i< n_labels; i++)
    {
      rot[i] = x++;
    }
}

//RETORNA QUAIS ERAM OS ROTULOS DAS AMOSTRAS NA BASE TESTE//
void test_labels(float **test, float *old, int lines_test, int columns)
  {
    int i = 0;
      for(i = 0; i < lines_test; i++)
        {
          old[i] = test[i][columns - 1]; //pega as ultimas colunas da matriz teste e armazena num vetor;
        }
  }

//MATRIZ DE CONFUSAO//
void matriz_confusao(int **matriz_confusa, float *new, float *old, float *label, int lines_test, int n_rotulos)

    {
    int i, j, line, column;
      for(i = 0; i < lines_test; i++)
        {
          for(j = 0; j < n_rotulos; j++)
            {
              if(new[i] == label[j])
                  {
                    line = (int)(new[i] - 1);
                    column = (int) (label[j]-1);
                    matriz_confusa[line][column]++;
                  }
            }
          }
  }


//RETORNA A ACURÁCIA//
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

      return acuracia*100;
    }
}
}

void main()
{
  FILE *fr;
  char info[] = "config.txt";//chama o config
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

  traine_path = pathreader(fr, path);//guarda um caminho do treino;

  test_path = pathreader(fr, path);//guarda um caminho do treino;

  prediction_path = pathreader(fr, path);//guarda o caminho do path;

  fclose(fr);

  FILE *fp;
  FILE *fp_test;
  int lines = 0, columns = 1; //as colunas iniciam como 1 para contabilizar a última coluna que não termina com vírgula;
  char c, d;

  //abre o arquivo de teste//
  fp_test = fopen(test_path, "r");
  if (fp_test == NULL)
  {
    printf("ERRO!\n");
    exit(1);
  }

  //abre o arquivo de treino//
  fp = fopen(traine_path, "r");
    if (fp == NULL)
      {
        printf("ERRO!");
      }

  //calculando o numero de linhas do treino//
  do
    {
      if (c == '\n')
        {
          lines++;
        }
    }
  while(fread(&c, sizeof(char),1, fp));//lê o arquivo e soma 1 a cada '\n' encontrado;
  rewind(fp);

//calculando o numero de linha de ambos os arquivos(que são iguais)//
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
    }while(fread(&d, sizeof(char),1,fp));//lê o arquivo somando um para cada vírugula, parando o programa ao encontrar um '\n'
  rewind(fp);

  int i, j=0;
  float **data;//cria a matriz armazenará a matriz treino;
  data = (float**) malloc (lines * sizeof(float *));
  for (i = 0; i < lines; i++)
    {
      data[i] = (float*) malloc (columns * sizeof(float*)); //aloca a matriz;
    }

for (i=0; i < lines; i++)
{
  for (j=0; j< columns;j++)
    {
      fscanf(fp, "%f%*c", &data[i][j]);// preenche a matriz com as informações do arquivo .csv
    }
}


float **data_test; //declaração da matriz que terá a matriz test
char e;
int lines_test = 0;

//calculando as linhas da matriz teste//
do
  {
    if (e == '\n')
      {
        lines_test++;
      }
  }
while(fread(&e, sizeof(char),1, fp_test));//contabiliza 1 a cada '\n'
rewind(fp_test);

data_test = (float **) malloc (lines * sizeof(float *));
for (i = 0; i < lines; i++)
  {
    data_test[i] = (float*) malloc (columns * sizeof(float*)); // aloca matriz do arquivo teste;
  }

int y, z;
for (z=0; z < lines; z++)
{
for (y=0; y < columns; y++)
  {
    fscanf(fp_test, "%f%*c", &data_test[z][y]);//scanea os valores do arquivos o colocando na matriz;
  }
}
fclose(fp_test);
fclose(fp);//fecha ambos arquivos

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

//calculando quantas linhas tem o arquivo config//
do
  {
    if (o == '\n')
      {
        lines_file++;
      }
  }while(fread(&o, sizeof(char),1, fr));//mesma lógica, contabilizando a cada \n
  rewind(fr);

int n_labels;
n_labels = n_rotulos(data_test, lines_test, columns); //chama a função e calcula o numero de rotulos;
float *diff_rot;

diff_rot = (float *) malloc (n_labels * sizeof(float *));//aloca vetor;
diff_labels(data_test, n_labels, columns, lines_test, diff_rot); //chama a função para retornar um vetor com vetores distintos;

float dist[lines], label, all_labels[lines_test];
int contador;
int **confusa; //matriz confusao
confusa = (int**) malloc (n_labels * sizeof(int*));
for(i = 0; i < n_labels; i++)
  {
    confusa[i] = (int*) malloc (n_labels * sizeof(int*)); //aloca a matriz
  }


float old[lines], acc;
FILE *out;
char *out_path;
int counter;

//PULA AS TRES PRIMEIRAS LINHAS, QUE SAO PATHS//
fgets(junk, sizeof(junk), fr);
fgets(junk, sizeof(junk), fr);
fgets(junk, sizeof(junk), fr);


for(counter = 1; counter < lines_file - 2; counter++)//EXECUTA TENDO COMO BASE O NUMERO DE LINHAS
{
  out_path = (char *) malloc (200 * sizeof(char)); //aloca o nome da saida
  sprintf (out_path, "%spredicao_%i.txt", prediction_path, counter); //imprime os nomes, com paths e numero;
  fscanf (fr, " %i%*c%*c %c", &k, &type);//escanea o tipo
  if (type == 'M')
    {
      fscanf(fr, ", %f", &r);// caso necessário escanea o r;
    }
  else
    {
      fgetc(fr);
    }

 switch(type) //calcula dependendo do tipo de distancia;
      {
        case 'E':
        for(i = 0; i < lines_test; i++)
          {
            for(j=0; j < lines; j++)
              {
                dist[j] = euclidiana(data_test[i], data[j],columns-1);
              }
                label = find_label(lines, dist, columns, k, data);
                all_labels[i] = label; //vetor com todos os labels achados com aquela distancia
              }

          test_labels(data_test, old, lines_test, columns);//
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
              all_labels[i] = label;//vetor com todos os labels achados com aquela distancia
            }
            test_labels(data_test, old, lines_test, columns);//rotulos das amostras teste;
            matriz_confusao(confusa, all_labels, old, diff_rot, lines_test, n_labels); //faz a matriz de confusao;
            acc = acuracia(confusa, lines_test, n_labels);//calcula a acuracia


            //PRINTA AS INFORMÇÕES CALCULADAS NOS ARQUIVOS DE SAIDA PREDICAOX//
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
              all_labels[i] = label;//vetor com todos os labels achados com aquela distancia
            }
            test_labels(data_test, old, lines_test, columns);
            matriz_confusao(confusa, all_labels, old, diff_rot, lines_test, n_labels);
            acc = acuracia(confusa, lines_test, n_labels);

            //PRINTA AS INFORMÇÕES CALCULADAS NOS ARQUIVOS DE SAIDA PREDICAOX//
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
