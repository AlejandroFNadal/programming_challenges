The compiled is 16K vs the 10M of the buffer. That is because the buffer is not really initialized,
so only a reference to the buffer is kept in bss (uninitialized data) section. We can prove this
by running objdump on the compiled binary with the -x flag.

The output includes this line as part of the symbol table:

```
0000000000014060 l     O .bss	00000000009c4000              mbuf.0
```

Showing that the buffer is in the bss section. Only the size is stored: 9c4000 is 10M in decimal.
The first value is the address of the buffer in memory.

Running with the -D flag we get

```
Disassembly of section .bss:

0000000000004040 <completed.0>:
	...

0000000000004060 <globBuf>:
	...

0000000000014060 <mbuf.0>:
```

When the program is run, the buffer is allocated in memory and the size is 10M.
