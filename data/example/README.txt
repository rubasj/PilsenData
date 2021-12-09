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
> flow.exe -v example_nodes.csv -s 0 -e example_edges.csv -t 6 -a
Max network flow is |x| = 9.
>


Soubor example_output.csv vznikl spuštěním programu flow.exe v tomto adresáři následujícím způsobem:

> flow.exe -v example_nodes.csv -e example_edges.csv -out example_output.csv -s 0 -t 6
Max network flow is |x| = 4.
> 
