#include <stdio.h>

/*filecopy : copy file ifp to file ofp*/
void filecopy(FILE *ifp, FILE *ofp)
{
	int c;
	while ((c = getc(ifp)) != EOF)
		putc(c, ofp);

}


int main(int argc, char *argv[])
{
	FILE *fp;

	char * prog = argv[0]; /*program name for errors*/

	if (argc == 1)/*no args; copy standard input*/
		filecopy(stdin, stdout);
	else 
		while (--argc > 0)
			if ((fp = fopen(*++argv, "r")) == NULL)
			{
				fprintf(stderr, "%s: can't open %s\n", prog, *argv);
				exit(1);
			}
			else
			{
				filecopy(fp, stdout);
				fclose(fp);
			}
	if (ferror(stdout))
	{
		fprintf(stderr, "%s: error writing stdout\n", prog);
		exit(2);
	}

	return 0;
}
