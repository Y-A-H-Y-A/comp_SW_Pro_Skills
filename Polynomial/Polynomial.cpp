#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <assert.h>
using namespace std;

// Creating a structure for the polynomial
typedef struct polynomialstruct {
	int coef;
	int expo;
	struct polynomialstruct* next;
} polynomial_type;

// create a single list with the size of (size)
polynomial_type* creatlist(int size) {
	// creat the headr
	polynomial_type* headr = (polynomial_type*)(malloc(sizeof polynomial_type));
	headr->next = NULL;
	// creat a list in the size of (size)
	for (int i = 0; i < size; i++) {
		polynomial_type* p = (polynomial_type*)malloc(sizeof(polynomial_type));
		p->next = headr->next;
		headr->next = p;
	}
	return headr;
}

//print a term (a sign and a variabl with its expo and coef)
void printTerm(char sign, polynomial_type* term)// this Function will take the sign of the term and the term itself

{
	cout << sign;
	if (term->expo == 0)     //if the expo is 0 then print only the absolute value of the term's coef 
	{
		cout << " " << abs(term->coef);
	}
	else
	{
		//cout << " " << abs(term->coef) << "X" << "<" << term->expo << "> "; ((((((  1st way to print the term ))))))
		cout << " " << abs(term->coef) << "X" << "^" << term->expo << " ";      //print the the absolute value of the term's coef and its expo ((((((  2nd way to print the term ))))))
	}

}

//this functioin will print a whole polynomial with its terms and its each expo and coef
void printpoly(polynomial_type* poly)

{
	int first = 1;
	cout << "(  ";
	for (polynomial_type* p = poly->next; p != NULL; p = p->next) //p will be treated as a term an will be inserted in the printTerm() 
	{
		if (first)
		{
			char sign = (p->coef >= 0) ? ' ' : '-';
			printTerm(sign, p);
			first = 0;
		}
		else
		{
			char sign = (p->coef >= 0) ? '+' : '-';
			printTerm(sign, p);
		}
	}
	cout << "  )";
	cout << endl;
};

// insert a term into a polynomial poly
void insertTerm(polynomial_type* poly, polynomial_type* term) 

{
	polynomial_type* p = poly;  //the pointer p now is the polynomial poly
	/*while the poly isn't empty and the  first term's expo in the poly is already higher than 
	the inserted term's expo then just move the p to its next */
	while (p->next != NULL && p->next->expo > term->expo) 
	{
		p = p->next;
	}
	/*if the poly is empty or the first terms's expo is lower than the inserted term's expo then 
	the term will be place befor the term that has lower expo 
	(NOTE:there is a video in my phone that explain everything )*/
	if (p->next == NULL || p->next->expo < term->expo ) 
	{
		term->next = p->next;
		p->next = term;
	}
	else 
	{
		assert(p->next->expo==term->expo); //(this will merg the coef of the term that's already in the poly and the inserted term)
		p->next->coef += term->coef;
		free(term);
		if (p->next->coef == 0) 
		{
			polynomial_type* q = p->next;
			p->next = p->next->next;
			free(q);
		}
	}
}

//input a polynomial form terminal
polynomial_type* ReadPoly()
{
	int co = 0, ex = 0;
	//create an empty list
	polynomial_type* poly = creatlist(0);

	do 
	{
		cout << "input a coefficient and an exponent: ";
		cin >> co >> ex;
		if (co != 0)
		{
			polynomial_type* term = (polynomial_type*)malloc(sizeof(polynomial_type));
			term->coef = co;
			term->expo = ex;
			term->next = NULL;
			insertTerm(poly, term);
		}
	}
	while (ex != 0);
	return poly;
}
polynomial_type* mergePoly(polynomial_type* poly1, polynomial_type* poly2) 
{
	polynomial_type* poly3 = creatlist(0);

	for (polynomial_type* p = poly1->next; p != NULL; p = p->next) 
	{
		polynomial_type* new_item = (polynomial_type*)malloc(sizeof(polynomial_type));
		*new_item = *p;
		insertTerm(poly3, new_item);
	}

	for (polynomial_type* p = poly2->next; p != NULL; p = p->next) 
	{
		polynomial_type* new_item = (polynomial_type*)malloc(sizeof(polynomial_type));
		*new_item = *p;
		insertTerm(poly3, new_item);
	}

	return poly3;
}




int main()
{
	cout << "Yahya Isaac_(LuoKe)_20193290616" << endl;
	polynomial_type* poly1 = ReadPoly(); //Getting the first polynomial from the user
	cout << "This is the first Polynomial (P1): ";
	printpoly(poly1); //showing the first entered polynomial

	polynomial_type* poly2 = ReadPoly(); //Getting the second one form the user as well
	cout << "This is the second Polynomial (P2): ";
	printpoly(poly2); //showing the second one

	//mergeing p1 with p2 and show the sum in a third polynomial p3
	polynomial_type* poly3 = mergePoly(poly1, poly2);
	cout << "P1 + P2 = ";
	printpoly(poly3);

	return 1;
}