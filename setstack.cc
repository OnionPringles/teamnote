
//change esp, eax to rsp, rax in 64-bit machine=
int main2(){
    return 0;
}
int main(){
    size_t sz = 1<<29; //512MB
    void* newstack = malloc(sz);
    void* sp_dest = newstack + sz - sizeof(void*);
    asm __volatile__("mov %0, %%rax\n\t"
                     "mov %%rsp, (%%rax)\n\t"   //save current stack pointer at the new address
                     "mov %0, %%rsp\n\t"
                     :
                     : "r"(sp_dest));
    main2();
    asm __volatile__("pop %rsp\n\t");           //restore the saved stack pointer
    return 0;
}