#include "register_access.hpp"

int main()
{
    read_only<unsigned char> r(0xFF0FD00);
    write_only<unsigned char> w(0xFF0FD01);
    read_write<unsigned char> rw1(0xFF0FD02);
    read_write<unsigned char> rw2(0xFF0FD03);
    
    w = r;              // No problem
    w = r + 1;          // No problem
    
    w = w;              // Won't compile. Can't read from RHS
    
    r = r;              // Won't compile. Can't write the LHS 
    r = w;              // Won't compile. Can't read from RHS and can't write the LHS 
    
    w = rw1;            // No problem
    r = rw1;            // Won't compile. Can't write to LHS
    
    rw1 = rw2;          // No problem
    rw1 = rw2 = rw1;    // No problem
    rw1 = r;            // No problem
    rw = w;             // Won't compile. Can't read from RHS

    return 0;
}
