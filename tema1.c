// ALEXE Adelina Maria - 312CC
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// am definit un vagon, care este de tipul struct node
typedef struct node {
  char symbol;
  struct node *prev, *next;
} node;

// am definit trenul, care este de tipul struct Train
typedef struct Train {
  struct node *head;
  struct node *mechanic;
} Train;

// functia init, pe care am folosit-o pentru initializarea
// trenului, adica a listei dublu inlantuite cu santinela (head)
void init(struct Train **train) {
  (*train) = malloc(sizeof(struct Train));

  // am verificat dupa fiecare alocare de memorie daca
  // aceasta este alocata corect
  if (*train == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  (*train)->head = malloc(sizeof(struct node));

  if ((*train)->head == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  (*train)->head->symbol = '\0';

  struct node *q = malloc(sizeof(struct node));

  if (q == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  q->symbol = '#';
  q->next = (*train)->head;
  q->prev = (*train)->head;
  (*train)->head->next = q;
  (*train)->head->prev = q;

  (*train)->mechanic = q;
}

// functie pentru adaugarea unui nou vagon
void add(struct Train *train, char s) {
  struct node *q;

  q = malloc(sizeof(struct node));

  if (q == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  q->symbol = s;
  q->next = train->head;
  q->prev = train->head->prev;
  train->head->prev->next = q;
  train->head->prev = q;
}

// functie pentru inserarea unui vagon nou in stanga vagonului mecanicului
// doar in cazul in care acesta nu se afla in primul vagon
void insert_left(struct Train *train, char s, FILE *f) {
  if (train->mechanic->prev->symbol == '\0')
    fprintf(f, "ERROR\n");

  else {
    struct node *q;
    q = malloc(sizeof(struct node));

    if (q == NULL) {
      printf("Memory allocation failed\n");
      exit(1);
    }

    q->symbol = s;
    q->next = train->mechanic;
    q->prev = train->mechanic->prev;
    train->mechanic->prev->next = q;
    train->mechanic->prev = q;
    train->mechanic = q;
  }
}

// functie pentru inserarea unui nou vagon
// si mutarea mecanicului in cazul in care acesta e in ultimul vagon
void insert_right(struct Train *train, char s) {
  struct node *q;
  q = malloc(sizeof(struct node));

  if (q == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  q->symbol = s;
  q->prev = train->mechanic;
  q->next = train->mechanic->next;
  train->mechanic->next->prev = q;
  train->mechanic->next = q;
  train->mechanic = q;
}

// functie pentru mutarea mecanicului in alt vagon
void move_mechanic(struct Train *train, struct node *q) 
    { train->mechanic = q; }

// functie care schimba notatia unui vagon
void write_cell(struct Train *train, char s) 
    { train->mechanic->symbol = s; }

// functie pentru eliminarea unui vagon
void clear_cell(struct Train *train) {
  struct node *q = train->mechanic;

  if (q->prev->symbol == '\0' && q->next->symbol != '\0') {
    move_mechanic(train, train->head->prev);
    train->head->next = q->next;
    q->next->prev = train->head;
    free(q);
  }

  else if (q->next->symbol == '\0' && q->prev->symbol == '\0') {
    move_mechanic(train, q);
  }

  else {
    move_mechanic(train, q->prev);
    train->mechanic->next = q->next;
    q->next->prev = train->mechanic;
    free(q);
  }
}

void free_train(struct Train **train);

// functie care elimina toate vagoanele
// si aduce trenul in starea initiala
void clear_all(struct Train **train) {
  free_train(train);
  init(train);
}

// functie care afiseaza un vagon
void show_current(struct Train *train, FILE *f) {
  fprintf(f, "%c\n", train->mechanic->symbol);
}

// functie care afiseaza tot trenul
void show(struct Train *train, FILE *f) {
  struct node *q;
  q = train->head->next;

  while (q->symbol != '\0') {
    if (q == train->mechanic)
      fprintf(f, "|%c|", q->symbol);

    else
      fprintf(f, "%c", q->symbol);
    q = q->next;
  }

  fprintf(f, "\n");
}

// functie care cauta un sir prin alipirea caracterelor de pe vagoane
void search(struct Train *train, char *string, FILE *f) {
  struct node *q = train->mechanic, *t = NULL;
  int n = strlen(string), i = 0, ok = 0;

  do {
    if (q->symbol != '\0') {
      if (q->symbol == string[i]) {
        if (ok == 0) {
          t = q;
          ok = 1;
        }
        q = q->next;
        i++;

      }

      else {
        i = 0;
        ok = 0;

        if (q->symbol != string[i]) q = q->next;
      }

      if (i == n) break;
    } else
      q = q->next;

  } while (q != train->mechanic && i < n);

  if (i == n)
    move_mechanic(train, t);

  else
    fprintf(f, "ERROR\n");
}

// functie care cauta un sir doar in dreapta mecanicului
void search_right(struct Train *train, char *string, FILE *f) {
  struct node *q = train->mechanic, *t = NULL;
  int n = strlen(string), i = 0;

  do {
    if (q->symbol == string[i]) {
      t = q;
      i++;
    }

    else
      i = 0;

    q = q->next;

  } while (q != train->head && i < n);

  if (i == n)
    move_mechanic(train, t);

  else
    fprintf(f, "ERROR\n");
}

// functie care cauta un sir in stanga mecanicului
void search_left(struct Train *train, char *string, FILE *f) {
  struct node *q = train->mechanic, *t = NULL;
  int n = strlen(string), i = 0;

  do {
    if (q->symbol == string[i]) {
      t = q;
      i++;
    }

    else
      i = 0;

    q = q->prev;

  } while (q != train->head && i < n);

  if (i == n)
    move_mechanic(train, t);

  else
    fprintf(f, "ERROR\n");
}

// functie pentru eliberarea memoriei alocate pentru tren
void free_train(struct Train **train) {
  struct node *q;
  q = (*train)->head->next;

  while (q->symbol != '\0') {
    struct node *t = q;
    q = q->next;
    free(t);
  }

  free((*train)->head);
  free(*train);
}

// definirea unui nod din coada
typedef struct queue {
  char *command;
  int index;
  struct queue *next, *prev;
} queue;

// definirea unei cozi
typedef struct TQueue {
  struct queue *head;
  struct queue *tail;
} TQueue;

// functie pentru initializarea cozii
void initQ(struct TQueue **q) {
  *q = malloc(sizeof(struct TQueue));
  if (*q == NULL) {
    printf("Memory allocation failed for queue\n");
    exit(1);
  }
  (*q)->head = NULL;
}

// functie care verifica daca o coada e plina sau nu
int isEmptyQ(struct TQueue *q) {
  if (q == NULL)
    return 1;

  else
    return 0;
}

// functie care adauga un nod la o coada
void addQ(struct TQueue **q, char *command) {
  struct queue *t = malloc(sizeof(struct queue));
  if (t == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  t->command = malloc(100 * sizeof(char));
  if (t->command == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  strcpy(t->command, command);
  t->next = NULL;

  if ((*q)->head == NULL) {
    t->index = 1;
    (*q)->head = t;
    (*q)->tail = t;
    (*q)->head->prev = NULL;
    (*q)->tail->prev = NULL;
  }

  else {
    t->index = (*q)->tail->index + 1;
    (*q)->tail->next = t;
    t->prev = (*q)->tail;
    (*q)->tail = t;
  }
}

// functie care sterge un nod de la inceputul cozii
void delQ(struct TQueue **q, char *command) {
  if ((*q)->head == NULL) {
    exit(1);
  }
  struct queue *t = (*q)->head;
  strcpy(command, t->command);

  if ((*q)->head->next != NULL) {
    (*q)->head = (*q)->head->next;
    free(t->command);
    free(t);
    (*q)->head->prev = NULL;
  } else {
    free((*q)->head->command);
    free((*q)->head);
    (*q)->head = NULL;
  }
}

// functie care inverseaza elementele din nodurile cozii
void switchQ(struct TQueue **q) {
  struct queue *first, *last;
  int i, j;
  char *aux = malloc(105 * sizeof(char));
  if (aux == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  first = (*q)->head;
  last = (*q)->tail;

  i = first->index;
  j = last->index;

  while (i <= j) {
    int n = strlen(first->command);

    for (int k = 0; k < n; k++) {
      aux[k] = first->command[k];
    }
    aux[n] = '\0';
    first->command[0] = '\0';

    int m = strlen(last->command);

    for (int k = 0; k < m; k++) {
      first->command[k] = last->command[k];
    }
    first->command[m] = '\0';
    last->command[0] = '\0';

    for (int k = 0; k < n; k++) {
      last->command[k] = aux[k];
    }
    last->command[n] = '\0';
    aux[0] = '\0';

    i++;
    j--;
    first = first->next;
    last = last->prev;
  }

  free(aux);
}

// functie care afiseaza o coada
void printQ(struct TQueue *q, FILE *f) {
  struct queue *t = q->head;

  while (t != NULL) {
    fprintf(f, "%s\n", t->command);
    t = t->next;
  }
}

// functie care elibereaza o coada
void freeQ(struct TQueue **q) {
  while (isEmptyQ(*q)) {
    struct queue *t = (*q)->head;
    (*q)->head = (*q)->head->next;
    (*q)->head->prev = NULL;

    free(t->command);
    free(t);
  }

  free(*q);
  *q = NULL;
}

int main() {
  // deschiderea fisierelor de intrare si iesire
  FILE *f = fopen("tema1.in", "r");
  FILE *g = fopen("tema1.out", "w");

  if (f == NULL || g == NULL) {
    printf("Files couldn't be open\n");
    return 1;
  }

  // alocarea memoriei pentru comenzile care vor fi citite
  int n, i;
  char *command = malloc(105 * sizeof(char));
  if (command == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  char *extract = malloc(105 * sizeof(char));
  if (extract == NULL) {
    printf("Memory allocation failed\n");
    exit(1);
  }

  // declararea si initializarea trenului si a cozii
  struct Train *train;
  init(&train);

  struct TQueue *q;
  initQ(&q);

  fscanf(f, "%d", &n);
  fgetc(f);

  // citirea comenzilor
  for (i = 0; i < n; i++) {
    fgets(command, 105, f);
    command[strlen(command) - 1] = '\0';

    // apelarea functiilor corespunzatoare comenzilor
    // care vor fi executate pe loc
    if (strcmp(command, "SHOW_CURRENT") == 0) {
      show_current(train, g);
    }

    else if (strcmp(command, "SHOW") == 0) {
      show(train, g);
    }

    else if (strcmp(command, "SWITCH") == 0) {
      if (q != NULL)
        switchQ(&q);

      else
        fprintf(g, "ERROR-THE QUEUE IS EMPTY\n");
    }

    // executarea comenzii curente din coada
    else if (strcmp(command, "EXECUTE") == 0) {
      delQ(&q, extract);

      if (strcmp(extract, "MOVE_LEFT") == 0) {
        if (train->mechanic->prev == train->head)
          move_mechanic(train, train->head->prev);

        else
          move_mechanic(train, train->mechanic->prev);
      }

      else if (strcmp(extract, "MOVE_RIGHT") == 0) {
        if (train->mechanic->next == train->head) {
          add(train, '#');
          move_mechanic(train, train->head->prev);
        }

        else
          move_mechanic(train, train->mechanic->next);
      }

      else if (extract[0] == 'W') {
        write_cell(train, extract[6]);
      }

      else if (strcmp(extract, "CLEAR_ALL") == 0) {
        clear_all(&train);
      }

      else if (strcmp(extract, "CLEAR_CELL") == 0) {
        clear_cell(train);
      }

      else if (extract[0] == 'I' && extract[7] == 'L') {
        insert_left(train, extract[strlen(extract) - 1], g);
      }

      else if (extract[0] == 'I' && extract[7] == 'R') {
        insert_right(train, extract[strlen(extract) - 1]);
      }

      else if (extract[0] == 'S' && extract[6] == ' ') {
        search(train, extract + 7, g);
      }

      else if (extract[0] == 'S' && extract[6] == '_' && extract[7] == 'L') {
        search_left(train, extract + 12, g);
      }

      else if (extract[0] == 'S' && extract[6] == '_' && extract[7] == 'R') {
        search_right(train, extract + 13, g);
      }
    }

    // adaugarea in coada a comenzilor pentru a fi executate ulterior
    else if (strcmp(command, "MOVE_LEFT") == 0) {
      addQ(&q, command);
    }

    else if (strcmp(command, "MOVE_RIGHT") == 0) {
      addQ(&q, command);
    }

    else if (command[0] == 'W') {
      addQ(&q, command);
    }

    else if (strcmp(command, "CLEAR_ALL") == 0) {
      addQ(&q, command);
    }

    else if (strcmp(command, "CLEAR_CELL") == 0) {
      addQ(&q, command);
    }

    else if (command[0] == 'I' && command[7] == 'L') {
      addQ(&q, command);
    }

    else if (command[0] == 'I' && command[7] == 'R') {
      addQ(&q, command);
    }

    else if (command[0] == 'S' && command[6] == ' ') {
      addQ(&q, command);
    }

    else if (command[0] == 'S' && command[6] == '_' && command[7] == 'L') {
      addQ(&q, command);
    }

    else if (command[0] == 'S' && command[6] == '_' && command[7] == 'R') {
      addQ(&q, command);
    }
  }

  // eliberarea memoriei pentru comenzi, coada si tren
  free(extract);
  free(command);
  freeQ(&q);
  free_train(&train);

  // inchiderea fisierelor de intrare si iesire
  fclose(f);
  fclose(g);

  return 0;
}
