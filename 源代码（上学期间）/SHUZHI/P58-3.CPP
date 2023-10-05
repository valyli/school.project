//shu zhi fen xi p58 3rd
double X[5]={0.4,0.5,0.6,0.7,0.8};
double Y[5]={-0.916291,-0.693147,-0.510826,-0.357765,-0.223144};
void L1(double x)
{int i;
double y;
for (i=0;i<4;i++)
 {y=Y[i]+(Y[i+1]-Y[i])*(x-X[i])/(X[i+1]-X[i]);
  printf("ln(x)=%lf(parameter:x%d,x%d)\n",y,i,i+1);
 }
}

void L2(double x)
{int i;
double y;
for (i=0;i<3;i++)
 {y=Y[i]*(x-X[i+1])*(x-X[i+2])/(X[i]-X[i+1])/(X[i]-X[i+2])+Y[i+1]*(x-X[i])*(x-X[i+2])/(X[i+1]-X[i])/(X[i+1]-X[i+2])+Y[i+2]*(x-X[i])*(x-X[i+1])/(X[i+2]-X[i])/(X[i+2]-X[i+1]);
  printf("ln(x)=%lf (parameter:x%d,x%d,x%d)\n",y,i,i+1,i+2);
 }
}

void main()
{double x;
printf("Please input x=");
scanf("%lf",&x);
printf("Results:\n");
L1(x);
printf("\n");
L2(x);
}
