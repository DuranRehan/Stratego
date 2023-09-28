#ifndef ROLE_H
#define ROLE_H
namespace model {

/**
 * @brief The Role enum define the 'rank' of the piece in army
 */
enum Role{
    MARECHAL='M',
    GENERAL ='9',
    COLONEL = '8',
    MAJOR= '7',
    COMMANDANT='6',
    LIEUTENANT ='5',
    SERGENT ='4',
    DEMINEUR ='3',
    ECLAIREUR ='2',
    ESPIONNE ='1',
    FLAG ='D',
    BOMBE='B',
    WALL='W',
    NOTHING='.',
};
}
#endif // ROLE_H
