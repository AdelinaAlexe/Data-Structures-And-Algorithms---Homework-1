Tema1

In rezolvarea acestei teme am folosit urmatoarele functii si structuri:

Am definit structurile pentru implementarea unui tren astfel:

"struct node" - un vagon din tren, ce contine simbolul (caracterul) vagonului,
dar si pointerii catre vagonul urmator si cel precedent

"struct Train" - trenul, ce contine 2 noduri cu ajutorul carora se poate
realiza deplasarea printre vagoane: head (santinela) si mechanic (mecanicul)

Functia init: functie care initializeaza trenul, mai exact aloca memorie
pentru structura tren, pentru santinela (head), atribuie simbolul '#' pentru
primul vagon si creeaza legaturile cu vagoanele din stanga si dreapta (trenul
fiind construit sub forma unei liste circulare dublu inlantuite), dar si 
seteaza pointerul catre vagonul in care se afla mecanicul. Alocarea corecta
a memoriei se verifica sub forma unor "if-uri", folosind coduri de eroare si
mesaje sugestive afisate pe ecran.

Functia add: functie pentru adaugarea unui nou vagon, in dreapta, si crearea
legaturilor cu vagoanele din stanga si dreapta.

Functia insert-left: functie care adauga un nou vagon in stanga vagonului
in care se afla mecanicul, doar in cazul in care acesta nu se afla in primul 
vagon, si afisarea mesajului "ERROR", in caz contrar.

Functia insert-right: functie care adauga un nou vagon in dreapta vagonului
in care se afla mecanicul si resetarea pointerului catre mecanic (mutarea
mecanicului in vagonul nou inserat).

Functia move-mechanic: functie care muta mecanicul in alt vagon, primit ca
parametru la functie.

Functia write-cell: functie care schimba simbolul unui vagon.

Functia clear-cell: functie care elimina un vagon si muta mecanicul in 
functie de pozitia in tren la care se afla.

Functia clear-all: functie care elimina toate vagoanele trenului, dar
il aduce la forma sa initiala (un singur vagon inscriptionat cu '#').

Functia show-current: functie care afiseaza simbolul vagonului la 
care se afla mecanicul.

Functia show: functie care afiseaza tot trenul.

Functia search: functie care cauta, caracter cu caracter, un sir primit ca
parametru la functie, printre toate vagoanele alaturate ale trenului, inclusiv
cu suprapuneri, pana se ajunge din nou la pozitia mecanicului.

Functia search-right: functie care cauta in partea din dreapta a trenului,
pana la ultimul vagon.

Functia search-left: functie care cauta in partea din stanga a trenului, in 
sens invers, pana la primul vagon.

Functia free-train: functie care elibereaza memoria pentru intreg trenul.

Am definit structurile pentru coada in care se retin comenzile astfel:

"struct queue" - un nod din coada, care contine numele comenzii, indexul,
dar si pointerii catre comanda precedenta si cea urmatoare.

"struct TQueue" - intreaga coada, care contine pointerii catre primul element
din coada (head), dar si ultimul (tail).

Functia initQ: functie care intializeaza coada si aloca memorie pentru intraga
coada.

Functia isEmptyQ: functie care verifica daca o coada este goala sau nu.

Functia addQ: functie care adauga un nou nod la finalul cozii, aloca memorie
si adauga noua comanda la campul aferent, in functie de pozitia curenta in 
coada.

Functia delQ: functie care elibereaza memoria pentru comanda extrasa de la
inceputul cozii, schimba pointerul "head" si retine comanda in pointerul
primit ca parametru la functie.

Functia switchQ: functie care interchimba continutul nodurilor din coada,
interschimband caracter cu caracter numele comenzilor.

Functia printQ: functie care afizeaza comenzile dintr-o coada.

Functia freeQ: functie care elibereaza memoria pentru intreaga coada.


In programul principal (functia main):

Am deschis fisierele de intrare si iesire si am verificat deschiderea lor
corecta.

Am declarat si alocat dinamic sirurile de caractere cu ajutorul carora voi
citi comenzile.

Am initializat trenul si coada in care retin comenzile.

Am parcurs si citit comenzile si am efectuat operatii in functie de tipul
comenzii:

In cazul comenzilor show-current, show, switch si execute, am efectuat
operatiile corespunzatoare la momentul citirii.

In cazul celorlalte comenzi, le-am adaugat in coada, iar la momentul 
citirii unei comenzi de tip execute, am apelat functiile corespunzatoare.

In final, am eliberat memoria pentru sirurile in care citesc comenzile, dar
si pentru intreaga coada si tren (lista circulara dublu-inlantuita), apeland
functiile specifice, iar mai apoi am inchis fisierele de intrare si iesire.
