#include <stdio.h>
#include <string.h>
#include <math.h>

typedef struct Terms {
    unsigned int term;
    int hamming_weight;
    int is_used;
} Term;

typedef struct Implicants{
    Term minterm;
    int is_prime;
    unsigned int pass_digit;
} Implicant;

typedef struct Groups{
    int weight;
    int id;
    int size_id;
    int num_implicants;
    Implicant implicants[128];
} Group;

void take_terms(Term[], int *);
void check_conflict(Term[], int);
void init_groups(Group[]);
int hamming_weight(unsigned int);
void calc_PIs(Group[], Term[], int);
int calc_available(Implicant, Implicant, int*);


int main(int argc, char const *argv[])
{
    struct Terms minterms[128];
    int num_minterms = 0;
    int i;

    struct Groups groups[30];

    printf("Please insert minterms seperated by space (e.g., 3 5 7):");
    take_terms(minterms, &num_minterms);

    check_conflict(minterms, num_minterms);//checks if there is no minterm entered.
    init_groups(groups);

    calc_PIs(groups, minterms, num_minterms);
    

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

void check_conflict(Term minterms[], int num_minterms){
    int i = 0, j = 0;
    if(num_minterms == 0){
        printf("There must be minterms for this algorithm to work.");
        return;
    }
}

void init_groups(Group groups[]){
    int i, j, k = 7, t = 1;

    for (i = 0, j = 0; i < 36; i++){
        groups[i].id = i;
        groups[i].weight = j;
        groups[i].size_id = t;
        if (j == k){
            k--;
            j = 0;
            t++;
        } else {
            j++;
        }
    }
}

void calc_PIs(Group groups[], Term minterms[], int num_minterms){
    
    int i, j, k, u, size, t;
    for (i = 0; i < 8; i++){
        k = 0;
        for (j = 0; j < num_minterms; j++){
            if (hamming_weight(minterms[j].term) == groups[i].weight){
                groups[i].implicants[k].pass_digit = 0;
                groups[i].implicants[k++].minterm = minterms[j];
            }
        }
        groups[i].num_implicants = k;
    }

    for (i = 0; i < 30; i++){
        if (groups[i].num_implicants == 0) continue;
        for(j = 0; j < groups[i].num_implicants; j++){
            u = 0;
            for (k = 0; k < groups[i+1].num_implicants; k++){
                if(calc_available(groups[i].implicants[j], groups[i+1].implicants[k], &u)){
                    size = pow(2, groups[i].size_id - 1);
                    groups[size + u].implicants[]
                }
            }
        }
    }

}

int hamming_weight(unsigned int n) {
    int r = n ? 1 : 0;
    while (n &= (n - 1)) ++ r;
    return r;
}

int calc_available(Implicant prior, Implicant next, int *u){
    unsigned int mask = 1;
    int i, r = 0;
    const int start_weight = hamming_weight(prior.minterm.term);
    if(prior.pass_digit == next.pass_digit){
        for(i = 0; i < 8; i++){
            if((mask & prior.pass_digit) == 1){
                mask = mask << 1;
                continue;
            }
            prior.minterm.term = prior.minterm.term | next.minterm.term;
            if ((prior.minterm.term & mask) == 1) u++;
            mask = mask << 1;
        }
        if ((hamming_weight(prior.minterm.term) - start_weight) == 1) r = 1;
    }
    return r;
}


