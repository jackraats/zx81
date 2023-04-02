/*
	Jack Raats
	van Nispenstraat 7
	4651 XH Steenbergen
	Tel: 00-31-167-540044
	E-mail: jack@raats.oorg

	version:	08-05-1993	DeSmet C / C68 v3.05
	update: 	02-04-2023	FreeBSD 13.2-RC6
*/

#include <stdio.h>
#include <stdlib.h>

char *tabel[] =
{
    " ","{1}","{2}","{7}","{4}",
    "{5}","{T}","{E}","{A}","{D}",
    "{S}","\"","#","$",":",
    "?","(",")",">","<",
    "=","+","-","*","/",
    ";",",",".","0","1",
    "2","3","4","5","6",
    "7","8","9","A","B",
    "C","D","E","F","G",
    "H","I","J","K","L",
    "M","N","O","P","Q",
    "R","S","T","U","V",
    "W","X","Y","Z"
};

int 	c, nl;
FILE 	*fi, *fo;

int main ( argc, argv )
int 	argc;
char	*argv[];
{
    printf ("\nZXAS convert ZXAS2 assembler output to ASCII");
    printf ("\nCopyright Jack Raats 1993-2023, Steenbergen, Holland");
    printf ("\nEmail:    jack@raats.org\n");

    if ( argc != 3 )
    {
        printf ("\nUSAGE:");
        printf ("\nA:>ZXAS filename.L filename.TXT\n\n");
        exit ( 1 );
    }

    if ( ( fi = fopen ( argv[1], "rb" ) ) == 0 )
    {
        printf ("\nERROR: cannot open %s\n\n", argv[1]);
        exit (2);
    }

    if ( ( fo = fopen ( argv[2], "wb" ) ) == 0 )
    {
        printf ("\nERROR: cannot open %s\n\n", argv[2]);
        exit (3);
    }

    if ( fseek ( fi, 7L, 0 ) != 7L )
    {
        printf ("\nERROR: %s is too short!\n\n", argv[1]);
        exit (4);
    }

    nl = 0;
    while ( 1 )
    {
        if ( ( c = fgetc (fi) ) == EOF ) break;
        switch (c)
        {
            case 0x76:
                fprintf ( fo,"%c",10);
                nl = 1;
                break;
            case 0x82:
                nl = 0;
                break;
            default:
                if ( nl == 1 ) fprintf ( fo, "      ");
                nl = 0;
				if ( c <= 64 ) fprintf ( fo, "%s", tabel[c]);
                break;
        }
    }
    fclose ( fi );
    fclose ( fo );
    printf ("\nZXAS ready\n\n");
    exit (0);
}
