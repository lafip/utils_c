/* 
 *   Copyright 2022 Clara Lafip <clara.lafip@gmail.com>
 *
 *   This program is free software: you can redistribute it and/or modify
 *   it under the terms of the GNU General Public License as published by
 *   the Free Software Foundation, either version 3 of the License, or
 *   (at your option) any later version.
 *
 *   This program is distributed in the hope that it will be useful,
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *   GNU General Public License for more details.
 *
 *   You should have received a copy of the GNU General Public License
 *   along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdio.h>
#include <stdlib.h>

int smallprime(int max_prime){
    //Small prime number generator
    int i, j;
    int found = 1;
    int *primes;
    if ((primes = malloc(max_prime * sizeof(int) << 1)) == NULL){
        fprintf(stderr, "Out of memory!\n");
        exit(EXIT_FAILURE);
    }
    
    primes[0] = 2;
    printf("2, ");
    for (i = 3; i < max_prime; i+=2){
        for (j = 1; j < found; j++){
            if (i % primes[j] == 0)
                goto next;
        }
        if (j == found){
            printf("%d, ", i);
            primes[found++] = i;
            if (found % 16 == 0)
                puts("");
        }
next: 1;
    }
    free(primes);
    printf("\nFound %d primes\n", found);
    return 0;
}

int main(int argc, char **argv){
    int limit;
    if (argc > 1 && (limit = atoi(argv[1])) > 0)
        smallprime(limit);
    else
        puts("Use primelist max_prime");
        
    exit(0);
}
