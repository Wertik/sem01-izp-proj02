#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct set_t {
    unsigned identifier;

    unsigned size;
    char elements[][30];
};

typedef struct set_t Set;

struct pair_t {
    char *first;
    char *second;
};

typedef struct pair_t Pair;

struct relation_t {
    unsigned identifier;

    unsigned size;
    Pair elements[];
};

typedef struct relation_t Relation;

// print a set
void prints(Set *set) {
    printf("%u:[", set->identifier);
    for (unsigned i = 0; i < set->size; i++) {
        printf("%s", set->elements[i]);
        if (i < set->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void add_element(Set *set, char *element) {
    set = realloc(set, sizeof(Set) + sizeof(char[30]) * (set->size + 1));

    if (!set) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(1);
        return;
    }

    int i;
    for (i = 0; element[i] != '\0'; i++) {
        set->elements[set->size][i] = element[i];
    }
    set->elements[set->size][i] = '\0';

    set->size += 1;
}

Set *create_set(unsigned identifier) {
    Set *set = malloc(sizeof(Set) + sizeof(char *));

    if (!set) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(1);
        return NULL;
    }

    set->size = 0;
    set->identifier = identifier;

    return set;
}

void printr(Relation *relation) {
    printf("%u:[", relation->identifier);
    for (unsigned i = 0; i < relation->size; i++) {
        printf("(%s, %s)", relation->elements[i].first,
               relation->elements[i].second);
        if (i < relation->size - 1) {
            printf(", ");
        }
    }
    printf("]\n");
}

void add_pair(Relation *relation, Pair pair) {
    relation = realloc(relation,
                       sizeof(Relation) + sizeof(Pair) * (relation->size + 1));

    if (!relation) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(1);
        return;
    }

    relation->elements[relation->size] = pair;
    relation->size += 1;
}

Relation *create_relation(unsigned identifier) {
    Relation *relation = malloc(sizeof(Relation) + sizeof(Pair));

    if (!relation) {
        fprintf(stderr, "Failed to allocate memory.\n");
        exit(1);
        return NULL;
    }

    relation->size = 0;
    relation->identifier = identifier;

    return relation;
}

void add_set(Set *sets, Set set) {}

int main(int argc, const char *argv[]) {
    (void)argc;
    (void)argv;

    FILE *file = fopen("./cmds.txt", "r");

    if (!file) {
        fprintf(stderr, "Couldn't open file.\n");
        return EXIT_FAILURE;
    }

    char buffer[102];

    Set sets[0];           // sets
    Relation relation[0];  // relations

    while (fgets(buffer, 102, file)) {
        for (int n = 0; n < 102; n++) {
            if (buffer[n] == '\n') {
                buffer[n] = '\0';
                break;
            }
        }

        switch (buffer[0]) {
            case 'U':
                // define a universum
                break;
            case 'S':
                // define a set
                break;
            case 'R':
                // define a relation
                break;
            case 'C':
                // run a command
                break;
        }
    }

    return 0;
}