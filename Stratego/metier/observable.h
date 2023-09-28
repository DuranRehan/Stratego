#ifndef OBSERVABLE_H
#define OBSERVABLE_H
#include <string>
#include <set>
#include "observers.h"
namespace utils {
namespace observable {

/**
 * @brief Define the Observable 'interface'
 *
 */
class Observable{
    std::set<utils::observers::Observers *> observers{};
public:
    /**
     * Default destructor
     */
    ~Observable() =default;

    /**
     * @brief Notify all observers of the subject
     * @param toUpdate the change that has to be notified
     */

    void notify(const std::string& toUpdate)const;

    /**
     * @brief Subscribe an observer to the subject
     * @param obsv observer to subscribe
     */
    void subscribe(utils::observers::Observers * obsv);

    /**
     * @brief Unsubscribe an observer to the subject
     * @param obsv observer to unsubscribe
     */
    void unsubscribe(utils::observers::Observers * obsv);
};

}//end of observable namespace
}//end of utils namespace
#endif // OBSERVABLE_H
