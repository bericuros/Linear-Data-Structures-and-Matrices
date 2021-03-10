#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

int glavniMeni() {

	char stavka;

	while (1) {
	    printf("\nIzaberite neku od ponudjenih stavki unosom njenog rednog broja:\n");
	    printf("1. Napravite matricu.\n");
	    printf("2. Postavite podrazumevanu vrednost.\n");
	    printf("3. Izaberite element matrice.\n");
	    printf("4. Dodelite vrednost elementu.\n");
	    printf("5. Broj nepodrazumevanih elemenata.\n");
	    printf("6. Ispis matrice.\n");
	    printf("7. Racunanje ostvarene ustede prostora.\n");
	    printf("8. Brisanje matrice.\n");
	    printf("9. Izlaz.\n");
		printf("\nStavka: ");
	
	    scanf(" %c", &stavka);
		if (stavka < 49 || stavka > 57) {
			system("cls");
			printf("Uneli ste neponudjenu opciju. Pokusajte opet.\n");
		}
	    else break;
	}

	return stavka-48;

}

int proveriPostojanjeMatrice(int *tip) {

	if (*tip == -1) {
		printf("Matrica nije napravljena. Napravite matricu kako biste mogli koristiti ovu funkciju.\n");
		return 0;
	}
	return 1;

}

int adresnaFunkcija(int i, int j) {
	return j * (j - 1) / 2 + i;
}

void napraviMatricu(int *mat[], int *tip) {

	int vr;

	while (1) {
		printf("Unesite tip (dimenziju) matrice (pozeljne vrednosti su u opsegu od 1 do 100): ");
		scanf("%d", &vr);

		if (vr <= 0) {
			system("cls");
			printf("Uneli ste nemoguc tip matrice. Pokusajte opet.\n");
		}
		else if (vr > 100) {
			system("cls");
			printf("Tip matrie je previse velik. Pokusajte sa manjom vrednoscu.\n");
		}
		else break;
	}

	*tip = vr;

	for (int j = 1;j < (*tip);j++) {
		for (int i = 0;i < j;i++) {
			printf("Unesite vrednost elementa na koordinati (%d, %d) u matrici: ", i, j);
			scanf("%d", &vr);
			mat[adresnaFunkcija(i, j)] = vr;
		}
	}
	
}

void izaberiElement(int *mat[], int *tip, int *podrazumevanaVrednost) {

	if (!proveriPostojanjeMatrice(tip)) return;

	int i, j, vr;
	while (1) {
		printf("Unesite koordinate trazenog elementa: ");
		scanf("%d %d", &i, &j);
		if (i < 0 || i >= *tip || j < 0 || j >= *tip) printf("Uneli ste neodgovarajuce koordinate.\n"
			"Koordinate moraju biti u opsegu [0, %d).\n"
			"Pokusajte ponovo.\n", *tip);
		else {
			if (i >= j) vr = *podrazumevanaVrednost;
			else vr = mat[adresnaFunkcija(i, j)];

			printf("\nTrazeni element ima vrednost: %d\n", vr);
			break;
		}
	}
	

}

void dodeliVrednost(int *mat[], int *tip) {

	if (!proveriPostojanjeMatrice(tip)) return;

	int i, j, vr;
	while (1) {
		printf("Unesite koordinate elementa ciju vrednost zelite da promenite: ");
		scanf("%d %d", &i, &j);
		if (i < 0 || i >= *tip || j < 0 || j >= *tip || i >= j) printf("Uneli ste neodgovarajuce koordinate.\n"
			"Koordinate moraju biti u opsegu [0, %d) i takodje mora da vazi nejednakost i < j,\n"
			"pri cemu je 'i' redni broj reda, a 'j' redni broj kolone.\n"
			"Pokusajte ponovo.\n", *tip);
		else {
			printf("Unesite zeljenu vrednost: ");
			scanf("%d", &vr);
			mat[adresnaFunkcija(i, j)] = vr;
			break;
		}
	}

}

void brojNepodrazumevanih(int *mat[], int *tip, int *podrazumevanaVrednost) {

	if (!proveriPostojanjeMatrice(tip)) return;

	int brojac = *tip * (*tip - 1) / 2;

	//int limit = adresnaFunkcija(0, *tip), brojac = 0;

	//for (int i = 0;i < limit;i++) if (mat[i] != *podrazumevanaVrednost) brojac++;

	printf("Broj nepodrazumevanih elemanata je: %d\n", brojac);

}

void ispisMatrice(int *mat[], int *tip, int *podrazumevanaVrednost) {

	if (!proveriPostojanjeMatrice(tip)) return;

	printf("Sadrzaj matrice je sledeci:\n\n");
	for (int i = 0;i < *tip;i++) {
		for (int j = 0;j < *tip;j++) {
			if (i >= j) printf("%5d ", *podrazumevanaVrednost);
			else printf("%5d ", mat[adresnaFunkcija(i, j)]);
		}
		printf("\n");
	}

}

void ustedaProstora(int *tip) {

	if (!proveriPostojanjeMatrice(tip)) return;

	double usteda;

	usteda = (double)(*tip*(*tip+1) / 2)/(*tip**tip)*100;
	printf("Usteda prostora je %.2lf posto.\n", usteda);

}

void brisanjeMatrice(int *mat[], int *tip, int tekst) {
	
	if (!proveriPostojanjeMatrice(tip)) return;

	int limit = adresnaFunkcija(0, *tip);

	for (int i = 0;i < limit;i++) mat[i] = 0;
	*tip = -1;

	if (tekst) printf("Matrica je uspesno obrisana.\n");

}

void postaviPodrazumevanuVrednost(int *podrazumevanaVrednost) {

	printf("Unesite novu podrazumevanu vrednost: ");
	int novaVrednost;
	scanf("%d", &novaVrednost);
	*podrazumevanaVrednost = novaVrednost;

}

void main() {

	int podrazumevanaVrednost = 0, tip = 100;
	int mat[5000];

	brisanjeMatrice(&mat, &tip, 0);
	tip = -1;

	printf("Dobrodosli!\n");

	while (1) {
		
		int naredba = glavniMeni();

		system("cls");

		if (naredba == 1) napraviMatricu(&mat, &tip);
		else if (naredba == 2) postaviPodrazumevanuVrednost(&podrazumevanaVrednost);
		else if (naredba == 3) izaberiElement(&mat, &tip, &podrazumevanaVrednost);
		else if (naredba == 4) dodeliVrednost(&mat, &tip);
		else if (naredba == 5) brojNepodrazumevanih(&mat, &tip, &podrazumevanaVrednost);
		else if (naredba == 6) ispisMatrice(&mat, &tip, &podrazumevanaVrednost);
		else if (naredba == 7) ustedaProstora(&tip);
		else if (naredba == 8) brisanjeMatrice(&mat, &tip, 1);
		else {
			printf("Dovidjenja!\n");
			break;
		}

	}

}