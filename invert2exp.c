/*   
 *  
 * 
 *  Copyright 2023 Clara Lafip <clara.lafip@gmail.com>
 *
 *  This program is free software: you can redistribute it and/or modify
 *  it under the terms of the GNU General Public License as published by
 *  the Free Software Foundation, either version 3 of the License, or
 *  (at your option) any later version.
 *
 *  This program is distributed in the hope that it will be useful,
 *  but WITHOUT ANY WARRANTY; without even the implied warranty of
 *  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the
 *  GNU General Public License for more details.
 *
 *  You should have received a copy of the GNU General Public License
 *  along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

#include <stdint.h>
#include <stdio.h>
#include <assert.h>
/*
 * 
 * Fast invert by modulo 2^e  O(e)
 * 
 */
uint64_t invert2exp(uint64_t a, short exp){
    uint64_t r = 1;
    uint64_t mask = 0b11;
    uint64_t mod = 0b10;
    uint64_t t = a; 
    if (!(a & 1)) return 0; // no inversion for even value
    for (unsigned i=2; i<=exp; i++){
        if ((t & mask) != 1){
            r += mod;
            t = r * a;
        }
        mod <<= 1;
        mask = (mask << 1) | 1;
    }
    return r;
}

/*
 * Fast inversion by modulo 2*n
 * an - inversion by modulo n
 * a - initial value
 */
uint64_t invert2n(uint64_t a, uint64_t an, short n){
    uint64_t mask = (1<<(n+1)) - 1;
    if (!(a & 1)) return 0; // no inversion for even value
    if ((an & mask) != 1){
        return an + (1<<n);
    }
    return an;
}

int main(){
    assert(invert2exp(131, 11) == 1579); // 1/131 mod 2**11
    assert(invert2exp(31, 15) == 31711); // 1/31 mod 2**15
    assert(invert2exp(2, 11) == 0); 
    assert(invert2exp(79, 7) == 47);
    
    assert(invert2n(131, 1579, 11)==3627); // 1/131 mod 2**12
    puts("passed");
}
