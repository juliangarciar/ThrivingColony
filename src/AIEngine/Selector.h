#ifndef SELECTOR_H
#define SELECTOR_H

#include "Composite.h"

/**
 * @class Selector
 * @brief Crea un objeto tipo Selector
 */
class Selector : public Composite {
    
    public:
        /**
         * @brief Constructor de Selector
         */
        Selector(std::vector<Behaviour*>);
        /**
         * @brief Destructor de Selector
         */
        virtual ~Selector();

        Enumeration::BehaviourState Update();

    private:

};

#endif