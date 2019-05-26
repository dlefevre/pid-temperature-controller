/*
 * Controller actions for the Mode Selection
 */

#ifndef __MODESCREENCONTROLLER_H__
#define __MODESCREENCONTROLLER_H__

#include "Constants.h"
#include "AbstractScreenController.h"

class ModeScreenController : public AbstractScreenController {
    public:
        void goLeft() override;
        void goRight() override;
        void click() override;
};

#endif
