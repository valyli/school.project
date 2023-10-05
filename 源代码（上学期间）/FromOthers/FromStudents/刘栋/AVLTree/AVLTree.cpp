#include <stdio.h>

//#define N 4
#define  N 8

void main()
{
	int i, j, h, m,k;
	int p[N + 1], q[N + 2],
		W[N + 1][N + 1], C[N + 1][N + 1],
		r[N + 1][N + 1];
	FILE *pf;
	pf = fopen("Result.txt", "w");
/*	p[1] = 4;	p[2] = 2;	p[3] = 1;	p[4] = 1;

	q[1] = 2;   q[2] = 3;	q[3] = 1;	q[4] = 1;
	q[5] = 1;
*/

	p[1] = 2;	p[2] = 4;	p[3] = 1;	p[4] = 2;
	p[5] = 6;	p[6] = 1;	p[7] = 3;	p[8] = 1;

	q[1] = q[2] = q[3] = q[4] = q[5] = q[6] = q[7] = q[8] = 0;
	q[9] = 0;
	printf("h = 0\n");
	fprintf(pf, "h = 0\n");
	for( i = 0; i <= N; i++ )
	{
		W[i][i] = q[i + 1];
		C[i][i] = 0;
		printf("W%d, %d = %d ", i, i, W[i][i]);
		printf("C%d, %d = %d\n", i, i, C[i][i]);
		fprintf(pf, "W%d, %d = %d ", i, i, W[i][i]);
		fprintf(pf, "C%d, %d = %d\n", i, i, C[i][i]);
	}
	for( h = 1; h <= N; h++ )
	{
		printf("h = %d\n", h);
		fprintf(pf, "h = %d\n", h);
		for( i = 0; i <= N-h; i++ )
		{
			j = i + h;
			W[i][j] = W[i][j - 1] + p[j] + W[j][j];
			m = i + 1;
			for( k = m + 1; k <= j; k++ )
				if(C[i][k - 1] + C[k][j] < C[i][m - 1] + C[m][j])
					m = k;
			C[i][j] = C[i][m-1] +C[m][j] + W[i][j];
			r[i][j] = m;
			printf("W%d, %d = %d ", i, j, W[i][j]);
			printf("C%d, %d = %d ", i, j, C[i][j]);
			printf("r%d, %d = a%d\n", i, j, m);
			fprintf(pf, "W%d, %d = %d ", i, j, W[i][j]);
			fprintf(pf, "C%d, %d = %d ", i, j, C[i][j]);
			fprintf(pf, "r%d, %d = a%d\n", i, j, m);
		}
	}
	fclose(pf);
}