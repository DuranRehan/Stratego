#ifndef OBSERVERS_H
#define OBSERVERS_H
#include <string>
namespace utils {

namespace observers {

/**
 * @brief Define the Observer 'interface'
 *
 */

class Observers{

public:
    /**
     * Default destructor
     */
    virtual ~Observers() = default;

    /**
     * Update all Observers of the subject, needs to be reimplemented in child class
     */
    virtual void update(const std::string & toUpdate) = 0;
};

}// end of observers namespace
}// end of utils namespace
#endif // OBSERVERS_H
