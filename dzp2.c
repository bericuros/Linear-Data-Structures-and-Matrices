#define _CRT_SECURE_NO_WARNINGS
#include<stdio.h>

typedef struct Node {
	int info;
	struct Node *next;
};
struct Node *top;

void ocistiEkran() {
	system("cls");
}

int isEmpty() {
	return top == NULL;
}

int pop() {

	struct Node *temp;
	
	if (isEmpty(top)) return '#';  /// stack underflow
	
	char value = top->info;   /// uzima vrednost elementa na vrhu steka
	
	temp = top;    /// uzima privremenu promenljivu da bude kopija trenutnog vrha
	
	top = top->next;          /// premesta pokazivac prvog clana steka na novi clan steka
	
	temp->next = NULL;    /// ne postoji vise temp->next jer se temp brise

	free(temp);           /// oslobadja memoriju
	return value;

}

void push(int data) {

	struct Node *temp;
	temp = (struct Node *)malloc(sizeof(struct Node));

	if (temp == NULL) {
		printf("Ne postoji dovoljno memorije za novi element u steku!\n");  /// stack overflow
		return;
	}

	temp->info = data;   /// daje informaciju

	temp->next = top;   /// veze novi clan za prethodni

	top = temp;   /// novi clan na vrhu
}

void postaviNizNaVrednost(int *niz[], int duzina, int vrednost) {

	for (int i = 0;i < duzina;i++) niz[i] = vrednost;

}

void ispisUnesiAritmetickiIzraz() {
	printf("Unesite aritmeticki izraz u postfiksnom obliku.\n"
		"Za simbole promenljivih koristite velika slova engleske abecede [A-Z].\n"
		"Dozvoljene operacije su {+, -, *, /}.\n"
		"Preporucuje se duzina ne veca od 1000 karaktera.\n");
	printf("Vas izraz glasi: ");
}

void losiSimboli(int *ponovi) {
	ocistiEkran();
	printf("Nazalost, uneli ste izraz koji sadrzi neodgovarajuce simbole.\nPokusajte ponovo.\n\n");
	*ponovi = 1;
}

void nemogucSlucaj(int *ponovi) {
	ocistiEkran();
	printf("Uneti aritmeticki izraz nije validno smislen.\n"
		"Obratite paznju na poredak i broj operanada i operatora.\nPokusajte ponovo.\n\n");
	*ponovi = 1;
}

int glavniMeni() {

	int stavka;

	while (1) {
		printf("\nOdaberite jednu od ponudjenih stavki:\n");
		printf("1. Unesite aritmeticki izraz u postfiksnom obliku.\n");
		printf("2. Promenite vrednost jednog od parametara.\n");
		printf("3. Izracunavanje unetog aritmetickog izraza.\n");
		printf("4. Izlaz iz programa.\n");
		printf("\nStavka: ");

		scanf("%d", &stavka);
		if (stavka < 1 || stavka > 4) {
			ocistiEkran();
			printf("Uneli ste neodgovarajucu opciju. Pokusajte ponovo.\n");
		}
		else return stavka;
	}
}

void unesiPromenljive(char izraz[], int *poseceni[]) {
	
	int vrednost, i = 0;
	while (izraz[i] != '\0') {
		if (izraz[i] >= 65 && izraz[i] <= 90 && poseceni[izraz[i] - 65] == -1000000000) {
			printf("%c: ", izraz[i]);
			scanf("%d", &vrednost);
			poseceni[izraz[i] - 65] = vrednost;
		}
		i++;
	}

}

int ispravnostSimbola(char izraz[]) {
	int i = 0, ponovi = 0;
	while (izraz[i] != '\0') {        /// provera ispravnosti unetih simbola
		if (izraz[i] != '+' && izraz[i] != '-' && izraz[i] != '*' && izraz[i] != '/' && (izraz[i] < 65 || izraz[i] > 90)) {
			losiSimboli(&ponovi);
			break;
		}
		i++;
	}
	return ponovi;
}

int proveraSmisla(char izraz[]) {
	int znaci = 0, ponovi = 0, i = 0;                      /// provera smisla aritmetickog izraza
	while (izraz[i] != '\0') {
		if (izraz[i] < 65 || izraz[i] > 90) znaci++;

		if (2 * znaci >= i + 1) {   /// jednak ili veci broj operatora od operanada => nemoguc slucaj
			nemogucSlucaj(&ponovi);
			break;
		}
		i++;
	}

	if (2 * znaci + 1 != i) nemogucSlucaj(&ponovi);    /// broj operanada treba da bude veci za jedan od broja operatora jer su u pitanju binarne operacije

	return ponovi;
}

void unesiAritmetickiIzraz(int *poseceni[], char *pokazivacAritmetickiIzraz, int *duzina, int *isNotValid) {

	char izraz[1005];

	postaviNizNaVrednost(poseceni, 26, -1e9);

	while (1) {
		ispisUnesiAritmetickiIzraz();

		scanf("%s", &izraz);

		if (ispravnostSimbola(izraz)) continue;       /// nije ispravan unos

		if (proveraSmisla(izraz)) continue;           /// provera smisla aritmetickog izraza
		
	    break;
	}

	printf("\nVas aritmeticki izraz je uspesno zapamcen. Sada treba da unesete celobrojnu vrednost za svaku promenljivu:\n");
	unesiPromenljive(izraz, poseceni);

	int i = 0;                           /// kopiranje izraza
	while (izraz[i] != '\0') {
		*pokazivacAritmetickiIzraz = izraz[i];
		pokazivacAritmetickiIzraz++;
		i++;
	}
	*pokazivacAritmetickiIzraz = izraz[i];  /// terminator 0
	*duzina = i;    /// bez '\0'
	*isNotValid = 0;   /// sada se mogu izvrsiti stavke 2 i 3

}

void promeniVrednostElementa(int *poseceni[], int *isNotValid) {

	if (*isNotValid) {
		printf("Trenutno nepostoji zapamcen aritmeticki izraz, treba prvo da ga unesete odabirom stavke '1'.\n");
		return;
	}

	char promenljiva, svePromenljive[26];
	int vrednost, brojPromenljivih = 0;
	
	for (int i = 0;i < 26;i++) {           /// izdvajanje postojecih promenljivih
		if (poseceni[i] != -1000000000) {
			svePromenljive[brojPromenljivih] = i + 65;
			brojPromenljivih++;
		}
	}

	while (1) {
		printf("Promenljive upotrebljene u izrazu su:\n");
		for (int i = 0;i < brojPromenljivih;i++) printf("%c = %d\n", svePromenljive[i], poseceni[svePromenljive[i] - 65]);
		printf("\nUnesite naziv promenljive (elementa) ciju vrednost zelite da promenite: ");
		scanf(" %c", &promenljiva);

		if (promenljiva < 65 || promenljiva > 90) {
			ocistiEkran();
			printf("Uneli ste neodgovarajuci simbol. Pokusajte ponovo.\n\n");
		}
		else if (poseceni[promenljiva - 65] == -1000000000) {
			ocistiEkran();
			printf("Uneli ste nepostojucu promenljivu. Pokusajte ponovo.\n\n");
		}
		else {
			printf("Unesite novu zeljenu celobrojnu vrednost za datu promenljivu: ");
			scanf("%d", &vrednost);
			poseceni[promenljiva - 65] = vrednost;
			ocistiEkran();
			printf("Vrednost navedene promenljive je uspesno promenjena.\n");
			break;
		}

	}

}

void izracunajVrednostIzraza(char *pokazivac, int duzina, int poseceni[], int *isNotValid) {

	if (*isNotValid) {
		printf("Trenutno nepostoji zapamcen aritmeticki izraz, treba prvo da ga unesete odabirom stavke '1'.\n");
		return;
	}

	int operand1, operand2, isGood = 1;

	for (int i = 0;i < duzina;i++) {
		if (*(pokazivac + i) == '+' || *(pokazivac + i) == '-' || *(pokazivac + i) == '*' || *(pokazivac + i) == '/') {
			operand2 = pop();
			operand1 = pop();
			switch (*(pokazivac + i)) {
			case '+':
				push(operand1 + operand2);
				break;
			case '-':
				push(operand1 - operand2);
				break;
			case '*':
				push(operand1 * operand2);
				break;
			case '/':
				if (operand2 == 0) {
					system("cls");
					printf("U unetom aritmetickom izrazu postoji deljenje sa nulom. Unesite novi izraz sa odgovarajucim vrednostima elemenata.\n");
					isGood = 0;
					break;
				}
				push(operand1 / operand2);
				break;
			}
			if (!isGood) break;
		}
		else push(poseceni[*(pokazivac + i) - 65]);
	}

	if (isGood) printf("Rezultat unetog aritmetickog izraza je: %d\n", pop());

	*isNotValid = 1;   /// nema vise aritmetickog izraza, onesposobljavaju se stavke 2 i 3

}

void main() {

	int poseceni[26];   /// niz u kojem se pamte vrednosti promenljivih
	char aritmetickiIzraz[1005];
	int duzina = 0, isNotValid = 1;

	printf("Dobrodosli!\n");

	while (1) {

		int naredba = glavniMeni();

		ocistiEkran();

		if (naredba == 1) unesiAritmetickiIzraz(&poseceni, &aritmetickiIzraz, &duzina, &isNotValid);
		else if (naredba == 2) promeniVrednostElementa(&poseceni, &isNotValid);
		else if (naredba == 3) izracunajVrednostIzraza(&aritmetickiIzraz, duzina, poseceni, &isNotValid);
		else {
			printf("Dovidjenja!\n");
			break;
		}

	}

}