#include <iostream>
#include <string>
#include <vector>

using namespace std;

void Checking(const string& type, const string& namePoliceman, const string& nameHumn);

class Humans {
public:
    Humans(const string& type, const string& name) : type_(type), Name_(name)
    {
    }

    virtual void Walk(const string& destination) const
    {
        cout << type_ << ": " << Name_ << " walks to: " << destination << endl;
    }

    string Log() const {
        return type_ + ": " + Name_;
    }

public:
    const string Name_;
    const string type_;
};

class Student : public Humans {
public:

    Student(const string& name, const string& favouriteSong) : Humans("Student", name), FavouriteSong_(favouriteSong) {
    }

    void Learn() const {
        cout << Log() << " learns" << endl;
    }

    void Walk(const string& destination) const override {
        cout << Log() << " walks to: " << destination << endl
             << Log() << " sings a song: " << FavouriteSong_ << endl;
    }

    void SingSong() const {
        cout << Log() << " sings a song: " << FavouriteSong_ << endl;
    }

private:
    const string FavouriteSong_;
};

class Teacher : public Humans {
public:

    Teacher(const string& name, const string& subject) : Humans("Teacher", name), Subject_(subject) {
    }

    void Teach() const {
        cout << Log() << " teaches: " << Subject_ << endl;
    }

private:
    const string Subject_;
};

class Policeman : public Humans {
public:
    Policeman(const string& name) : Humans("Policeman", name) {
    }

    void Check(const Humans& h) const {
        cout << Log() << " checks " << h.type_ << ". " << h.type_ << "'s name is: " << h.Name_ << endl;
    }
};

void VisitPlaces(const Humans& h, const vector<string>& places) {
    for (const auto& p : places) {
        h.Walk(p);
    }
}

int main() {
    Teacher t("Jim", "Math");
    Student s("Ann", "We will rock you");
    Policeman p("Bob");

    VisitPlaces(t, { "Moscow", "London" });
    p.Check(s);
    VisitPlaces(s, { "Moscow", "London" });

    return 0;
}