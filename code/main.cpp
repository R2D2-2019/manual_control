#include <comm.hpp>
#include <dummy_controller.hpp>
#include <hwlib.hpp>
#include <manual_control.hpp>
#include <steering_wheel_controller.hpp>


int main(void) {
    // kill the watchdog
    WDT->WDT_MR = WDT_MR_WDDIS;
    hwlib::wait_ms(1000);
    hwlib::cout << "starting up.../n";
    hwlib::wait_ms(1000);

    auto button1 = hwlib::pin_in(hwlib::pins::d2);
    auto button2 = hwlib::pin_in(hwlib::pins::d3);
    auto button3 = hwlib::pin_in(hwlib::pins::d4);
    auto button4 = hwlib::pin_in(hwlib::pins::d5);
    auto wheel = hwlib::adc(hwlib::ad_pins::a0);
    auto pedals = hwlib::adc(hwlib::ad_pins::a1);

    auto test = r2d2::manual_control::steering_wheel_controller_c(
        1, button1, button2, button3, button4, wheel, pedals);

    r2d2::comm_c comm;
    r2d2::manual_control::module_c controller(comm, test);

    for (;;) {
        controller.process();

        hwlib::wait_ms(10);
    }
}