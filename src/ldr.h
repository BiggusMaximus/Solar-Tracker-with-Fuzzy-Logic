#define LDR_ATAS A7
#define LDR_KIRI A6
#define LDR_KANAN A5
#define LDR_BAWAH A4

float top, bottom, left, right = 0;
float diff_vertical, diff_horizontal = 0;
float CALIBRATION_TOP, CALIBRATION_BOTTOM, CALIBRATION_LEFT, CALIBRATION_RIGHT;

void ldr_innit()
{
    pinMode(LDR_ATAS, INPUT);
    pinMode(LDR_KIRI, INPUT);
    pinMode(LDR_KANAN, INPUT);
    pinMode(LDR_BAWAH, INPUT);
}

void read_value_ldr()
{
    top = analogRead(LDR_ATAS);
    bottom = analogRead(LDR_BAWAH);
    left = analogRead(LDR_KIRI);
    right = analogRead(LDR_KANAN);

    diff_vertical = top - bottom;
    diff_horizontal = right - left;
}

void show_ldr(bool show_text)
{
    top = analogRead(LDR_ATAS) + CALIBRATION_TOP;
    bottom = analogRead(LDR_BAWAH) + CALIBRATION_BOTTOM;
    left = analogRead(LDR_KIRI) + CALIBRATION_LEFT;
    right = analogRead(LDR_KANAN) + CALIBRATION_RIGHT;

    diff_vertical = top - bottom;
    diff_horizontal = right - left;
    if (show_text == true){
        Serial.println(
            "Top : " + String(top) +
            " | Bottom : " + String(bottom) +
            " | Left : " + String(left) +
            " | Right : " + String(right) +
            " | diff Vertical : " + String(diff_vertical) +
            " | diff Horizontalal : " + String(diff_horizontal));
    }
}
void calibration_ldr()
{
    float SET_LDR = 500;
    top = analogRead(LDR_ATAS);
    bottom = analogRead(LDR_BAWAH);
    left = analogRead(LDR_KIRI);
    right = analogRead(LDR_KANAN);

    CALIBRATION_TOP = SET_LDR - top;
    CALIBRATION_BOTTOM = SET_LDR - bottom;
    CALIBRATION_LEFT = SET_LDR - left;
    CALIBRATION_RIGHT = SET_LDR - right;
}