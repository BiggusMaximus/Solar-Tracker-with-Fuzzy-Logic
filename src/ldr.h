#define LDR_ATAS 3
#define LDR_KIRI 2
#define LDR_KANAN 5
#define LDR_BAWAH 4
#define THRESHOLD 100

float top, bottom, left, right;
float diff_vertical, diff_horizontal;

void ldr_innit()
{
    pinMode(LDR_ATAS, INPUT);
    pinMode(LDR_KIRI, INPUT);
    pinMode(LDR_KANAN, INPUT);
    pinMode(LDR_BAWAH, INPUT);
}

void read_value_ldr()
{
    top     = analogRead(LDR_ATAS);
    bottom  = analogRead(LDR_BAWAH);
    left    = analogRead(LDR_KIRI);
    right   = analogRead(LDR_KANAN);

    diff_vertical   = top - bottom;
    diff_horizontal = right - left;
}