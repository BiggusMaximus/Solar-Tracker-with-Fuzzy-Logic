#define LDR_KIRI_ATAS 3
#define LDR_KIRI_BAWAH 2
#define LDR_KANAN_ATAS 5
#define LDR_KANAN_BAWAH 4


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
    top     = (digitalRead(LDR_KIRI_ATAS)    + digitalRead(LDR_KANAN_ATAS)) / 2.0;
    bottom  = (digitalRead(LDR_KIRI_BAWAH)   + digitalRead(LDR_KANAN_BAWAH)) / 2.0;
    left    = (digitalRead(LDR_KIRI_ATAS)    + digitalRead(LDR_KIRI_BAWAH)) / 2.0;
    right   = (digitalRead(LDR_KANAN_ATAS)   + digitalRead(LDR_KANAN_BAWAH)) / 2.0;
}