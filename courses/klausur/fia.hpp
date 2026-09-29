#ifndef fia_hpp
#define fia_hpp
#include <iostream>
#include <vector>

#include <string>
class fia_Asss{
    private:
        std::string name;
        const int id;
        static int idnext;
        bool acc;
    public:
        fia_Asss(const std::string& name, bool acc) :name(name), id(idnext++), acc(acc) {};
        virtual void print() const = 0;
        virtual ~fia_Asss() = default;

        const std::string& getName()const{ return this -> name; }
        void setName(const std::string& name){ this -> name = name; }
        int getId(){ return this -> id; }
        bool getAcc(){ return this -> acc; }
        void setAcc(bool acc){ this -> acc = acc; }
};

class Driver : public fia_Asss{
    private:
        std::string nationality;
    public:
        Driver(const std::string& name, bool acc, const std::string& nationality) : fia_Asss(name, acc), nationality(nationality) {};
        void print() const override {};
        void setNationality(const std::string& nationality){ this -> nationality = nationality; }
        const std::string& getNationality()const{ return this -> nationality; }
};
class Mechanic : public fia_Asss{
    private:
        std::string specitlisation;
    public:
        Mechanic(const std::string& name, bool acc, const std::string& specitlisation) : fia_Asss(name, acc), specitlisation(specitlisation) {};
        void print() const override {};
        void setNationality(const std::string& nationality){ this -> specitlisation = nationality; }
        const std::string& getNationality()const{ return this -> specitlisation; }
};
class Subteam{
    private:
        const Driver* driver;
        std::vector<const Mechanic*> pitCrew;
    public:        
        Subteam(const Driver& driver):driver(&driver){};
        void addMechanic(const Mechanic& mechanic){pitCrew.push_back(&mechanic); }
        const Driver* getDriver() const { return this -> driver; }
        const std::vector<const Mechanic*>& getPitCrew() const { return this -> pitCrew; }

};
class Team{
    private:
        std::vector<Subteam*> subteams;
    public:
        Team(){};
        void addSubteam(Subteam& subteam)
        {
            subteams.push_back(&subteam);
        }
        void addMechanic(const Mechanic& mechanic, int idx)
        {
            subteams[idx]->addMechanic(mechanic);
        }
        void addMeachanic(std::string name, bool acc, std::string specitlisation, int idx)
        {
            Mechanic* mechanic = new Mechanic(name, acc, specitlisation);
            subteams[idx]->addMechanic(*mechanic);
        }
        void checkTeam();

};
#endif