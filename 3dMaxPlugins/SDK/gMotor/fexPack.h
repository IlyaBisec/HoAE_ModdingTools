/*****************************************************************
/*  File:   fexPack.h                                            *
/*  Desc:   Packing routines                                     *
/*  Author: Falinc, Copyright (C) GSC Game World                 *
/*  Date:   Mar 2002                                             *
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
