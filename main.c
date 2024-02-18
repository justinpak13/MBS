#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <locale.h>

typedef struct Loan {
	// Principal in dollars
	float principal;
	// term in months
	int term;
	// yearly interest divided by 12
	float rate;
	
	float total_interest_paid;

	int current_period;
} Loan;

Loan *create_loan(float principal, int term, float rate){
	Loan *loan = malloc(sizeof(Loan));
	loan -> principal = principal;
	loan -> term = term * 12;
	loan -> rate = rate / 12 / 100;
	loan -> total_interest_paid = 0;
	loan -> current_period = 0;
	
	return loan;

}

void print_loan(Loan *loan){
	printf("\nTotal Principal Amount: %'.2f\n", loan -> principal);
	printf("Term in Years: %d\n", loan -> term * 12);
	printf("APR: %.2f\n\n", loan -> rate * 12 * 100);
}


float *amort(Loan *loan){
	float rate = loan -> rate; 
	float principal = loan -> principal;
	float n = loan -> term;

	float *result = malloc(sizeof(float) * 3);

	result[0] = principal * (rate * pow(1 + rate, n)) / (pow(1 + rate, n) - 1);
	result[1] = principal * rate;
	result[2] = result[0] - result[1];


	return result;
}



int main(void){
	setlocale(LC_NUMERIC, "");
	Loan *loan = create_loan(240000, 15, 3.5);

	print_loan(loan);

	float *result = amort(loan);


	printf("Monthly Pmt   ");
	printf("Interest Pmt   ");
	printf("Principal Pmt     ");
	printf("Rem Balance\n");

	printf("$%'10.2f   ", (result[0]));
	printf("$%'11.2f   ", (result[1]));
	printf("$%'12.2f   ", (result[2]));
	printf("$%'12.2f\n", (loan -> principal - result[2]));
	

	free(result);
}
