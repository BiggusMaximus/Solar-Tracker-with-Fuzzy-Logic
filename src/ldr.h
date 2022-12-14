#define LDR_KIRI_ATAS 2
#define LDR_KIRI_BAWAH 3
#define LDR_KANAN_ATAS 4
#define LDR_KANAN_BAWAH 5


float top, bottom, left, right;

void ldr_innit()
{
    pinMode(LDR_KIRI_ATAS, INPUT);
    pinMode(LDR_KIRI_BAWAH, INPUT);
    pinMode(LDR_KANAN_ATAS, INPUT);
    pinMode(LDR_KANAN_BAWAH, INPUT);
}

void read_value_ldr()
{
    top     = (analogRead(LDR_KIRI_ATAS)    + analogRead(LDR_KANAN_ATAS)) / 2.0;
    bottom  = (analogRead(LDR_KIRI_BAWAH)   + analogRead(LDR_KANAN_BAWAH)) / 2.0;
    left    = (analogRead(LDR_KIRI_ATAS)    + analogRead(LDR_KIRI_BAWAH)) / 2.0;
    right   = (analogRead(LDR_KIRI_BAWAH)   + analogRead(LDR_KANAN_ATAS)) / 2.0;
}