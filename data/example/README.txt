Ukázka možného použití programu flow.exe v tomto adresáři nad testovacími daty:

> flow.exe -s 0 -t 6 -v example_nodds.csv -e example_edges.csv
Invalid vertex file.
> flow.exe -s 0 -t 6 -v example_nodes.csv -e example_edzis.csv
Invalid edge file.
> flow.exe -s 115 -t 6 -v example_nodes.csv -e example_edges.csv
Invalid source vertex.
> flow.exe -s 0 -t 7 -v example_nodes.csv -e example_edges.csv
Invalid sink vertex.
> flow.exe -s 6 -t 6 -v example_nodes.csv -e example_edges.csv
Invalid sink vertex.
> flow.exe -s 0 -t 6 -v example_nodes.csv -e example_edges.csv
Max network flow is |x| = 4.
> flow.exe -v ./example/example_nodes.csv -s 0 -e ./example/example_edges.csv -t 6 -a
Max network flow is |x| = 9.
>


Soubor example_output.csv vznikl spuštěním programu flow.exe v tomto adresáři následujícím způsobem:

> flow.exe -v example_nodes.csv -e example_edges.csv -out example_output.csv -s 0 -t 6
Max network flow is |x| = 4.
> 











==32606== Memcheck, a memory error detector
==32606== Copyright (C) 2002-2017, and GNU GPL'd, by Julian Seward et al.
==32606== Using Valgrind-3.14.0 and LibVEX; rerun with -h for copyright info
==32606== Command: ./flow.exe -e /var/courses/pc/bin/w3test/invalidedges/invalidedges_edges.csv -v /var/courses/pc/bin/w3test/invalidedges/invalidedges_nodes.csv -s 1 -t 6 -out w3-test_1_out.csv
==32606== Parent PID: 32605
==32606==
==32606== Conditional jump or move depends on uninitialised value(s)
==32606== at 0x10A940: dfs (in /var/courses/pc/data/janrubas/flow.exe)
==32606== by 0x10ABE2: ford_fulkerson (in /var/courses/pc/data/janrubas/flow.exe)
==32606== by 0x109D1B: main (in /var/courses/pc/data/janrubas/flow.exe)
==32606==
==32606== Conditional jump or move depends on uninitialised value(s)
==32606== at 0x10AC2D: ford_fulkerson (in /var/courses/pc/data/janrubas/flow.exe)
==32606== by 0x109D1B: main (in /var/courses/pc/data/janrubas/flow.exe)
==32606==
==32606== Conditional jump or move depends on uninitialised value(s)
==32606== at 0x10AC14: ford_fulkerson (in /var/courses/pc/data/janrubas/flow.exe)
==32606== by 0x109D1B: main (in /var/courses/pc/data/janrubas/flow.exe)
==32606==
==32606== Conditional jump or move depends on uninitialised value(s)
==32606== at 0x4838CD8: __strlen_sse2 (vg_replace_strmem.c:462)
==32606== by 0x4A4B4A4: fputs (iofputs.c:33)
==32606== by 0x109316: print_output (in /var/courses/pc/data/janrubas/flow.exe)
==32606== by 0x109D87: main (in /var/courses/pc/data/janrubas/flow.exe)
==32606==
==32606==
==32606== HEAP SUMMARY:
==32606== in use at exit: 504 bytes in 2 blocks
==32606== total heap usage: 56 allocs, 54 frees, 30,452 bytes allocated
==32606==
==32606== LEAK SUMMARY:
==32606== definitely lost: 24 bytes in 1 blocks
==32606== indirectly lost: 480 bytes in 1 blocks
==32606== possibly lost: 0 bytes in 0 blocks
==32606== still reachable: 0 bytes in 0 blocks
==32606== suppressed: 0 bytes in 0 blocks
==32606== Rerun with --leak-check=full to see details of leaked memory
==32606==
==32606== For counts of detected and suppressed errors, rerun with: -v
==32606== Use --track-origins=yes to see where uninitialised values come from
==32606== ERROR SUMMARY: 39 errors from 4 contexts (suppressed: 0 from 0)