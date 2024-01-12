/*****************************************************************
/*  File:   FPack.h                                            
/*  Desc:   Packing routines                                     
/*  Author: Falinc, Copyright (C) GSC Game World                 
/*  Date:   Mar 2002                                             
/*****************************************************************/

void G16SetNationalColor(unsigned int R, unsigned int G, unsigned int B);
bool G16UnpackSegment(unsigned char* inbuf,     // - ����������� ������
                      unsigned int inlen,
                      unsigned char* outbuf,    // - ������������� �������
                      unsigned char* workbuf,   // - ������� �����
                      unsigned int* fbuf,       // - ������ �������� ������
                      unsigned int Frames,      // - ���������� ������ � ��������
                      unsigned int Flags);      // - ����� (����� ��������)
void G16SetPalette(BYTE* pPal235, BYTE* pPalRGB);
unsigned G15UnpackSquare(unsigned short* InData, unsigned short* OutData, int R);
void G16PaintNationColor(int R, int G, int B, int Range, unsigned short* InData);
int G2DUnpackTexture(unsigned char* InData, unsigned short* OutData, int W, int H, int Flags);