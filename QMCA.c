#include <stdio.h>
#include <string.h>
#include <math.h>

#define NUM_MINTERMS 16
#define NUM_INPUTS 4
#define NUM_GROUPS 5
#define NUM_IMPLICANTS 120 //temporary, there is more than this needed actually

typedef struct Terms {
    unsigned int term;
} Term;

typedef struct Implicants{
    Term minterm;
    int is_null;
    int is_prime;
    unsigned int pass_digit;
} Implicant;

void take_terms(Term[], int *);
void check_conflict(Term[], int);
int hamming_weight(unsigned int n);
void init_turns(Implicant[]);
void calc_PIs(Implicant[], Term[], int);
int chck_available(Implicant, Implicant, unsigned int*);


int main(int argc, char const *argv[])
{
    Term minterms[NUM_MINTERMS];
    Implicant implicants[NUM_IMPLICANTS];
    int num_minterms = 0;
    int i;

    

    printf("Please insert minterms seperated by space (e.g., 3 5 7):");
    init_implicants(implicants);
    take_terms(minterms, &num_minterms);
    check_conflict(minterms, num_minterms);//checks if there is no minterm entered.

    calc_PIs(implicants, minterms, num_minterms);
    

    return 0;
}

void take_terms(Term terms[], int *num_terms){
    int term;
    char input[NUM_MINTERMS];
    fgets(input, NUM_MINTERMS, stdin);
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

void check_conflict(Term minterms[], int num_minterms){
    if(num_minterms == 0){
        printf("There must be minterms for this algorithm to work.");
        return;
    }
}

void init_turns(Implicant implicants[]){
    int i;
    for (i = 0; i < NUM_MINTERMS; i++){
        implicants[i].is_null = 1;
        implicants[i].is_prime = 0;
        implicants[i].pass_digit = 0;
    }
}

void calc_PIs(Implicant implicants[], Term minterms[], int num_minterms){
    
    int i, j, k, u, size, t, x;
    unsigned int chngd_bit = 0;
    for (i = 0; i < NUM_GROUPS; i++){
        for(j = 0; j < num_minterms; j++){
            if (hamming_weight(minterms[j].term) == i){
                implicants[i].minterm.term = minterms[j];
                implicants[i].is_null = 0;
                implicants[i].is_prime = 1;
                implicants[i].pass_digit = 0;
            }
        }
    }
    //new one uncertain num_implicants
    for(i = 0, j = 0, k = 0; i < NUM_IMPLICANTS; i++){
        
    }

    //old one deprecated because of for loop restrictions.
    // size = 0;
    // for (i = 0; i < NUM_INPUTS; i++){
    //     for (j = 0, x = 0; j < NUM_GROUPS; j++){
    //         for (k = 0; k < NUM_INPUTS; k++){
    //             chngd_bit = 0;
    //             for (t = 0; t < NUM_INPUTS; t++){
    //                 if (chck_available(turns[i].groups[j].implicants[k], turns[i].groups[j+1].implicants[t], &chngd_bit)){
    //                     turns[i].groups[j].implicants[k].is_prime = 0;
    //                     turns[i].groups[j+1].implicants[t].is_prime = 0;
    //                     size = hamming_weight(turns[i].groups[j].implicants[k].minterm.term);
    //                     turns[i+1].groups[size].implicants[x].pass_digit = chngd_bit | turns[i].groups[j].implicants[k].pass_digit;
    //                     turns[i+1].groups[size].implicants[x++].minterm.term = turns[i].groups[j].implicants[k].minterm.term | turns[i].groups[j+1].implicants[t].minterm.term;
    //                 }
    //             }
    //         }
    //     }
    // }

    for (i = 0; i < NUM_INPUTS; i++){
        for (j = 0; j < NUM_GROUPS; j++){
            for (k = 0; k < NUM_INPUTS; k++){
                if(turns[i].groups[j].implicants[k].is_null == 0 && turns[i].groups[j].implicants[k].is_prime == 1) {
                    printf("is null?: %d\n", turns[i].groups[j].implicants[k].is_null);
                    printf("turn: %d, group: %d, implicant %d, prime: %u\n", i, j, k, turns[i].groups[j].implicants[k].minterm.term);
                    };
            }
        }
    }


}

int hamming_weight(unsigned int n) {
    int r = n ? 1 : 0;
    while (n &= (n - 1)) ++ r;
    return r;
}

int chck_available(Implicant prior, Implicant next, unsigned int * chngd_bit){
    unsigned int mask = 1;
    int i, r = 0;
    const unsigned int start_weight = hamming_weight(prior.minterm.term);
    unsigned int p_term = prior.minterm.term;
    if((prior.pass_digit == next.pass_digit) && (!prior.is_null && !next.is_null)){
        for(i = 0; i < NUM_INPUTS; i++){
            if((mask & prior.pass_digit) == 1){
                mask = mask << 1;
                continue;
            }
            p_term = (p_term & mask) | (next.minterm.term & mask);
            mask = mask << 1;
        }
        if ((hamming_weight(p_term) - start_weight) == 1){
            r = 1;
            (*chngd_bit) = prior.minterm.term ^ next.minterm.term;
        };
    }
    return r;
}



