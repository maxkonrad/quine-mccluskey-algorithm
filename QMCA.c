#include <stdio.h>
#include <string.h>

typedef struct Terms {
    int term;
    int is_combined;
    int hamming_weight;
} Term;

typedef struct Groups{
    int weight;
    int minterms[];
    unsigned int common;
    int is_combined
} Group;

void bubble_sort(Term[], int size);
void take_terms(Term[], int *);
void check_conflict(Term[], int, Term[], int);
void calc_hamming_weight(Term[], int);


int main(int argc, char const *argv[])
{
    struct Terms minterms[256];
    int num_minterms = 0;
    struct Terms dont_cares[256];
    int num_dont_cares = 0;
    int i;
    struct Groups prime_implicants[256];
    struct Groups implicants[256];
    struct Groups essential_prime_implicants[256];

    printf("Please insert minterms seperated by space (e.g., 3 5 7):");
    take_terms(minterms, &num_minterms);
    printf("Please insert don't care conditions seperated by space (e.g., 3 5 7):");
    take_terms(dont_cares, &num_dont_cares);
    
    check_conflict(minterms, num_minterms, dont_cares, num_dont_cares);//checks if there is a conflict between don't care conditions and minterms & if there is no minterm entered.
    minterms[num_minterms];
    dont_cares[num_dont_cares];
    bubble_sort(minterms, num_minterms);
    bubble_sort(dont_cares, num_dont_cares);

    calc_hamming_weight(minterms, num_minterms);
    calc_hamming_weight(dont_cares, num_dont_cares);
    


    return 0;
}

void take_terms(Term terms[], int *num_terms){
    int term;
    char input[256];
    fgets(input, 256, stdin);
    char* token = input;
    while (sscanf(token, "%d", &term) == 1){
        terms[(*num_terms)++].term = term;

        token = strchr(token, ' ');
        if (token == NULL){
            break;
        }
        token++;
    }
}

void check_conflict(Term minterms[], int num_minterms, Term dont_cares[], int num_dont_cares){
    int i = 0, j = 0;
    if(num_minterms == 0){
        printf("There must be minterms for this algorithm to work.");
    }
    for (; i < num_minterms; i++){
        for (; j < num_dont_cares; j++){
            if (minterms[i].term == dont_cares[j].term){
                printf("There is a conflict between minterms and don't care conditions, plaese check your input.");
                return;
            }
        }
    }
}

void bubble_sort(Term arr[], int size){
	int i, j, temp;
	for(i = 0; i < size - 1; i++){
		for(j = i + 1; j < size; j++){
			if(arr[j].term < arr[i].term){
				temp = arr[i].term;
				arr[i].term = arr[j].term;
				arr[j].term = temp;
			}
		}
	}
}


void calc_hamming_weight(Term arr[], int n){
    int i = 0, j = 0;
    for (; i < n; i++){
        unsigned int num = (unsigned int) arr[i].term;
        int count = 0;
        while (num > 0){
            if (num & 1)
                count++;
            num >>= 1;
        }
        arr[i].hamming_weight = count;
    }
}