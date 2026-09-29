#include "fia.hpp"
#include <iostream>

int fia_Asss::idnext = 0;
void fia_Asss::print() const{
    std::cout << "Name: " << getName() << std::endl;
}
void Team::checkTeam(){
    for (auto subteam : subteams){
        subteam->getDriver()->print();
        for (auto mechanic : subteam->getPitCrew()){
            mechanic->print();
        }
    }
} 
int main(){
    Driver driver1("Driver1", true, "USA");
    Mechanic mechanic1("Mechanic1", true, "Engine");
    Mechanic mechanic2("Mechanic2", true, "Tires");

    Subteam subteam(driver1);
    subteam.addMechanic(mechanic1);
    subteam.addMechanic(mechanic2);

    Team team;
    team.addSubteam(subteam);

    team.checkTeam();

    return 0;
}