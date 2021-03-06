/*
 * Controller actions for Pid Screen
 */

#ifndef __PIDSCREENCONTROLLER_H__
#define __PIDSCREENCONTROLLER_H__

#include "Constants.h"
#include "AbstractScreenController.h"

class PidScreenController : public AbstractScreenController {
    public:
        void goLeft() override;
        void goRight() override;
        void click() override;
};

#endif
