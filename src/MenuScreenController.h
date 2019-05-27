/*
 * Controller actions for Menu Screen
 */

#ifndef __MENUSCREENCONTROLLER_H__
#define __MENUSCREENCONTROLLER_H__

#include "Constants.h"
#include "AbstractScreenController.h"

class MenuScreenController : public AbstractScreenController {
    public:
        void goLeft() override;
        void goRight() override;
        void click() override;
        void longClick() override;

    private:
        short multiplier;
        
        template<typename T> T modify(T value, T delta, T min, T max);
        void updateItem(short);
};

#endif
