#ifndef ROUTINE_H_INCLUDED
#define ROUTINE_H_INCLUDED

unsigned char *dummy( unsigned char *TempIndx );

unsigned char *CntlChar( unsigned char *TempIndx );
unsigned char *PuncChar( unsigned char *TempIndx );
unsigned char *TermChar( unsigned char *TempIndx );
unsigned char *FCPuncChar( unsigned char *TempIndx );

unsigned char *ThaiEngCutRtn( unsigned char *TempIndx );

unsigned char *LeadConRtn( register unsigned char *TempIndx );

unsigned char *HorHeebRtn( unsigned char *TempIndx );
unsigned char *HunAkadRtn( register unsigned char *TempIndx );
unsigned char *KaranRtn( unsigned char *TempIndx );
unsigned char *MaiMalaiRtn( register unsigned char *TempIndx );
unsigned char *MaiMuanRtn( unsigned char *TempIndx );
unsigned char *MaiTaiKuuRtn( unsigned char *TempIndx );
unsigned char *MaiYamokRtn( unsigned char *TempIndx );
unsigned char *OrAngRtn( unsigned char *TempIndx );
unsigned char *PaiYarnnoyRtn( unsigned char *TempIndx );
unsigned char *RoreReoRtn( register unsigned char *TempIndx );
unsigned char *RoreRuRtn( unsigned char *TempIndx );
unsigned char *SaraARtn( unsigned char *TempIndx );
unsigned char *SaraAERtn( unsigned char *TempIndx );
unsigned char *SaraAEEkRtn( unsigned char *TempIndx );
unsigned char *SaraAEJatRtn( unsigned char *TempIndx );
unsigned char *SaraAEToeRtn( unsigned char *TempIndx );
unsigned char *SaraAETriRtn( unsigned char *TempIndx );
unsigned char *SaraAhRtn( register unsigned char *TempIndx );
unsigned char *SaraAirRtn( register unsigned char *TempIndx );
unsigned char *SaraArWithoutTnl( );
unsigned char *SaraERtn( unsigned char *TempIndx );
unsigned char *SaraErEkRtn( unsigned char *TempIndx );
unsigned char *SaraErRtn( unsigned char *TempIndx );
unsigned char *SaraErToeRtn( unsigned char *TempIndx );
unsigned char *SaraIeRtn( unsigned char *TempIndx );
unsigned char *SaraORtn( register unsigned char *TempIndx );
unsigned char *SaraRRtn( register unsigned char *TempIndx );
unsigned char *SaraRWithMaiTri( register unsigned char *TempIndx );
unsigned char *SaraRWithoutTnl( register unsigned char *TempIndx );
unsigned char *SaraRWithTonal( register unsigned char *TempIndx );
unsigned char *SaraURtn( register unsigned char *TempIndx );
unsigned char *SaraUeRtn( unsigned char *TempIndx );
unsigned char *SaraUeeRtn( register unsigned char *TempIndx );
unsigned char *SaraUmRtn( register unsigned char *TempIndx );
unsigned char *SaraUURtn( unsigned char *TempIndx );
unsigned char *WoreWaanRtn( register unsigned char *TempIndx );

#endif
