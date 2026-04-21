#include "nnxt.h"

// test 1
/*
int main() {

    sensor_touch_clicked_t touch;
    SensorConfig (Port_0, SensorTouch);

    while(1) {
        Touch_Clicked(Port_0, &touch);
        if(touch == SensorTouch_clicked)
            NNXT_LCD_DisplayStringAtLine(0, "Button pressed");
        else
            NNXT_LCD_DisplayStringAtLine(0, "Button released");
    }
}
*/

//test 2
/*
int main() {
    sensor_touch_clicked_t touch;
    char msg[20];
    uint16_t counter = 0;
    SensorConfig(Port_0, SensorTouch);

    while(1) {
        Delay(20);
        Touch_Clicked(Port_0, &touch);
        if(touch == SensorTouch_clicked)
            counter++;
        else
            counter = 0;
        if (counter > 0) {
            sprintf(msg, "Duration: %d", (int)counter*20);
            NNXT_LCD_DisplayStringAtLine(0, msg);
        } else
            NNXT_LCD_DisplayStringAtLine(0, "");
    }
}
*/

//test 2 improved
int main() {
    sensor_touch_clicked_t touch;
    SensorConfig(Port_0, SensorTouch);

    uint32_t start_time;
    uint32_t time;

    char msg[20];

    while(1) {
        Delay(20);
        Touch_Clicked(Port_0, &touch);
        if(touch == SensorTouch_clicked) {
            time = GetSysTime() - start_time;
            sprintf(msg, "time: %d", (int)time);
            NNXT_LCD_DisplayStringAtLine(0, msg);
        } else {
            start_time = GetSysTime();
            NNXT_LCD_DisplayStringAtLine(0, "                  ");
        }
    }
}
