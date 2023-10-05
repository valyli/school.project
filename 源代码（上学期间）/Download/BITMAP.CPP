#include<stdio.h>
    #include<dos.h>
    #include<stdio.h>
    #include<conio.h>
    #define NoError 0
    #define ErrorFileOpen1
    #define ErrorFileType 2
    #define ErrorImageColor 3
    typedef struct tagBITMAPFILEHEADER {
        unsigned int   bfType;
        unsigned longbfSize;
        unsigned intbfReserved1;  unsigned intbfReserved2;
        unsigned longbfoffBits;
    } BITMAPFILEHEADER;
    typedef struct tagBITMAPINFOHEADER {
        unsigned longbiSize;
        unsigned long  biWidth;
        unsigned longbiHeight;
        unsigned intbiPlanes;
        unsigned intbiBitCount;
        unsigned long biCompression;
        unsigned long biSizeImage;
        unsigned long biXPelsPerMeter;
        unsigned long biYPelsPerMeter;
        unsigned long biClrUsed;
        unsigned long biClrImportant;
    } BITMAPINFOHEADER;
    typedef struct tagRGBQUAD {
        unsigned char rgbBlue;
        unsigned char rgbGreen;
        unsigned charrgbRed;
        unsigned char rgbReserved;
    } RGBQUAD;
    void main(int argc,char *argv[]);
    int ShowBmp(char *FileName);
    int GetColor(unsigned char R,unsigned char G, unsigned char B,int X,int Y)
;
    void SetVideoMode(unsigned char Mode);
    void SetPalReg(unsigned char *palReg);
    void SetDacReg(unsigned char *DacReg, int Color, int Count);
    void PutPixel(int X, int Y,unsigned char Color);
    unsigned char PalReg[17]= {  0,1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,0};
    unsigned char StandardPal[48]= {
    0, 0, 0, 32, 0, 0, 0,32, 0, 32,32, 0,   0, 0,32, 32, 0,32, 0,32,32, 32,32,
32,  48,48,48, 63, 0, 0, 0,63, 0, 63,63, 0,   0, 0,63, 63, 0,63, 0,63,63, 63,63,63,};
    unsigned char LightnessMatrix [16][16]= {
    { 0,235,59,219,15,231,55,215,2,232,56,217,12,229,52,213},
    {128,64,187,123,143,79,183,119,130,66,184,120,140,76,180,116},
    {33,192,16,251,47,207,31,247,34,194,18,248,44,204,28,244},
    {161,97,144,80,175,111,159,95,162,98,146,82,172,108,156,92},
    {8,225,48,208,5,239,63,223,10,226,50,210,6,236,60,220},
    {136,72,176,112,133,69,191,127,138,74,178,114,134,70,188,124},
    {41,200,24,240,36,197,20,255,42,202,26,242,38,198,22,252},
    {169,105,152,88,164,100,148,84,170,106,154,90,166,102,150,86},
    {3,233,57,216,13,228,53,212,1,234,58,218,14,230,54,214},
    {131,67,185,121,141,77,181,117,129,65,186,122,142,78,182,118},
    {35,195,19,249,45,205,29,245,32,193,17,250,46,206,30,246},
    {163,99,147,83,173,109,157,93,160,96,145,81,174,110,158,94},
    {11,227,51,211,7,237,61,221,9,224,49,209,4,238,62,222},
    {139,75,179,115,135,71,189,125,137,73,177,113,132,68,190,126},
    {43,203,27,243,39,199,23,253,40,201,25,241,37,196,21,254},
    {171,107,155,91,167,103,151,87,168,104,153,89,165,101,149,85},
    };
    unsigned char ColorTable[2][2][2]= {
    {{0,12},{10,14}},{{9,13},{11,15}}};
    unsigned char ColorMap[256][3];
    void main (int argc, char *argv[])
    {
        if(argc!=2) {
                printf("Usage:\n\tSHOW Filename.BMP\n");
                exit(1);
        }
        ShowBmp(argv[1]);
    }
    int ShowBmp(char *FileName)
    {
        FILE *Fp;
        BITMAPFILEHEADER FileHead;
        BITMAPINFOHEADER InfoHead;
        RGBQUAD RGB;
        int N, W,Y,X,C,Color;
        unsigned char Buffer[4096];
        if (!(Fp=fopen(FileName,"rb")))
                return(ErrorFileOpen);
        fread(&FileHead,siazeof(BITMAPFILEHEADER),1,Fp);
        if(FileHead.bfType!='BM')
                return(ErrorFileType);
        fread(&InfoHead,sizeof(BITMAPFILEHEADER),1,Fp);
        if(InfoHead.biBitcount!=8 && InfoHead.biBitCount!=24) {
                fclose(Fp);
                return(ErrorImageColor);
        }
        SetVideoMode(0x12);
        SetPalReg(PalReg);
        SetDacReg(StandardPa1,0,16);
        if(InfoHead.biBitcount==8) {
                for (N=0;N<256;N++) {
                        fread(&RGB, sizeof(RGBQUAD),1,Fp);
                        ColorMap[N][0]=RGB.rgbRed;
                        ColorMap[N][1]=RGB.rgbGreen;
                        ColorMap[N][2]=RGB.rgbBlue;
                }
                W=(InfoHead.biwidth+3)/4*4;
                for(Y=InfoHead.biHeight-1;Y>=480;Y--)
                        fread(Buffer,sizeof(unsigned char),W,Fp);
                for(;Y>0;Y--) {
                        fread(Buffer, sizeof(unsigned char),w,FP);
                        for (X=0;X<InfoHead.biWidth && X<640;X++) {
                                C=Buffer[X];
                                Color=GetColor(ColorMap[C][0],ColorMap[C][1],C
olorMap[C][2],X,Y);
                                PutPixel (X,Y,color);
                        }
                }
        }
        else {
                W=(infoHead.biWidth*3+3)/4*4;
                for(Y=InfoHead.biHeight-1;Y>639;Y--)
                        fread(Buffer,sizeof(unsigned char),W,Fp);
                for(;Y>=0;Y--) {
                        fread(Buffer,sizeof(unsigned char),W,Fp);
                        for (X=0;X<InfoHead.biWidth && X<640;X++) {
                                C=X*3;
                                Color=GetColor(Buffer[C+2],Buffer[C+1],Buffer[
C],X,Y);
                                PutPixel(X,Y,color);
                        }
                }
        }
        getch();
        fclose(Fp);
        SetVideoMode(0x03);
        return(NoError);
        }
        int GetColor(unsigned char R, unsigned char G,unsigned char B, int X,
int Y){
        unsigned int L=LightnessMatrix[Y & 0x0F][X & 0x0F];
        return(colorTable[(
                        unsigned int)R*256/255>L][(
                        unsigned int)G*256/255>L][(
                        unsigned int)B*256/255>L]);}
        void SetVideoMode(unsigned char Mode){
                -H=0x00;
                -AL=Mode;
                geninterrupt(0x10);
        }
        voidSetPalReg(unsigned char *PalReg){
                -ES=FP-SEG((unsigned char far*)PalReg);
                -DX=FP-OFF((unsigned char far*)PalReg;
                -AX=0x1002;
                geninterrupt(0x10);
        }
        void SetDacReg(unsigned char *DacReg,int Color,int Count){
                -ES=FP-SEG((unsigned char far*)DacReg);
                -DX=FP-OFF((unsigned char far*)DacReg);
                -AX=0x1012;
                -BX=Color;
                -CX=Count;
                geninterrupt(0x10);
        }
        void PutPixel(int X, int Y, unsigned charColor){
                -AH=0x0C;
                -AL=Color;
                -CX=X;
                -DX=Y;
                geninterrupt(0x10);
        }
    } 