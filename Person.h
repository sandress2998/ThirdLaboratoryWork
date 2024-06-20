#include <iostream>
#include <string>


class PersonID {
private:
    inline static int lastNumber;
    inline static int lastSeries;
    int number;
    int series;
public:
    PersonID() {}

    int getSeries() const {
        return series;
    }

    int getNumber() const {
        return number;
    }

    std::string getID() const {
        return std::to_string(series) + " " + std::to_string(number);
    }

    void increaseID() {
        if (lastNumber == 9) {
            ++lastSeries;
            lastNumber = 0;
        }
        series = lastSeries;
        number = lastNumber++;
    }
};

class Person {
private:
    PersonID personID;
    std::string firstName = "";
    std::string secondName = "";
    std::string thirdName = "";
    std::string dateOfBirth = "";

public:
    Person() {}

    Person(std::string firstName, std::string secondName, std::string thirdName, std::string dateOfBirth): firstName(firstName), secondName(secondName), thirdName(thirdName), dateOfBirth(dateOfBirth) {
        personID.increaseID();
    }
    Person(std::string firstName, std::string secondName, std::string dateOfBirth): firstName(firstName), secondName(secondName), dateOfBirth(dateOfBirth) {
        personID.increaseID();
    }
    Person(std::string firstName, std::string secondName): firstName(firstName), secondName(secondName) {
        personID.increaseID();
    }
    Person(const Person& other): firstName(other.firstName), secondName(other.secondName) {}

    std::string getID() const {
        return personID.getID();
    }

    int getSeries() const {
        return personID.getSeries();
    }

    int getNumber() const {
        return personID.getNumber();
    }

    std::string getFullName() const {
        return firstName + " " + secondName + " " + thirdName;
    }

    std::string getFirstName() const {
        return firstName;
    }

    std::string getSecondName() const {
        return secondName;
    }

    friend std::ostream& operator<<(std::ostream& os, const Person& person) {
        os << "| ";
        if (person.thirdName == "" && person.dateOfBirth == "") {
            os << person.firstName << " " << person.secondName;
        }
        if (person.thirdName == "") {
            os << person.firstName << " " << person.secondName << " " << person.dateOfBirth;
        } else {
            os << person.firstName << " " << person.secondName << " " << person.thirdName << " " << person.dateOfBirth;
        }
        os << " ID: " << person.getID() << " |";
        return os;
    }

    friend std::istream& operator>>(std::istream& is, Person& person) {
        if (person.firstName != "") return is;
        std::cout << "\nFirst name = ";
        is >> person.firstName;
        std::cout << "Second name = ";
        is >> person.secondName;
        std::cout << "Date of birth = ";
        is >> person.dateOfBirth;
        person.personID.increaseID();
        return is;
    }
};
