/*
 * Thermometer screen controller
 */

#include "ThermometerScreenController.h"
#include "Controller.h"

void ThermometerScreenController::goLeft() {

}

void ThermometerScreenController::goRight() {

}

void ThermometerScreenController::click() {
    static Controller &controller = Controller::instance();
    controller.switchToMode();
}