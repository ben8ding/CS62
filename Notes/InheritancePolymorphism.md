# Inheritance and Polymorphism

**Inheritance**

* Used when you want to make a more specific version of a class you already have.
* Benefit of reusing functionality

**Jargon**

* Parent/Base class: The class that is being inherited from
* Child/Derived: the class that is inheriting 
* Generally has an "is a" realtionship. *i.e.* an employee is a person

* The child class gets all of the parent classs' members (fields/methods)
* The child can also add and re-define parent public members

```c++
#include <iostream>
#include <string>

using namespace std;

class Person{
  private: 
    string name;//Private fields not accessible from child class

  public:
    Person() {
      name = "";
      cout << "New Person" << endl;
    }
    Person(string n) {
      name = n;
      cout << "New Person: " << n<< endl;
    }
    void foo () {
      cout << "Person foo" << endl;
    }
    void bar () {
      cout << "Person bar" << endl;
    }
    string toString(){
      return name;
    }
};
class Employee: public Person{
  private:
    int id;
  public:
    Employee(){ // implicitly calls the Person constructor (it has to call the person constructor)
      cout << "New Employee" << endl;
    }
    Employee(string n, int i): Person(n){ // call the constructor with a paramater so the person object is created first and then the employee is built around it
      //name = n;//Can't directly access, but could if it was protected instead of private
      id = i;
      cout << "New Employee" << endl;
    }
    void foo () {
      cout << "Employee foo" << endl;
    }
    void pay () {
      cout << "Employee pay" << endl;
    }
    string toString() {
      //return "Employee " + name + ", ID: " + std::to_string(id);
      return "Employee " + Person::toString() + ", ID: " + std::to_string(id);
    }
}
```

* It's okay to treat a cat as an animal cuz every animal is a cat, but it's not okay to treat an animal as a cat because not every animal is a cat.
* You can cast an object as its parent object where the child methods are just cut.
* So if an employee was cast as a person, they'd still have a name but they just wouldn't have an ID.

# Polymorphism
* Parameter of parent type (Animal) will accept objects of parent or child (Bird/Cat)
* Doing this by refernce is important for some reason
* Virtual Figures out at runtime what object it is pointing to and will call the more specific function. Otherwise it will determine at compilation. 
* Virtual still has to be valid at compliation, a virtual function in a child class cannot be called by the parent class even if the pointer is pointing to the child class.
* Virtual has to be part of the parent class, but doesn't need to part of the child function

```c++
int main(){
  Animal a;
  Bird b;
  Cat c;

  vector<Animal> v;
  v.push_back(a);
  v.push_back(b); // really: v.push_back((Animal) b);
  v.push_back(c);
  for (auto x: v) {
    x.sleep(); // all objects get cast as Animal
  }     

  Animal* ap = new Animal();
  Bird* bp = new Bird();
  Cat* cp = new Cat();

  cout << "bp: " << bp << endl;
  Animal* bp2 = bp;
  cout << "(Animal*) bp: " << bp2 << endl; // same as bp

  vector<Animal*> vp;
  vp.push_back(ap);
  vp.push_back(bp);
  //equivalent: vp.push_back((Animal*)bp);
  vp.push_back(cp);
  for (Animal* x: vp) {
    x->sleep();
  }
}
  ```

  * Child class does not have to inherit all virtual functions in parent class
  * Pure virtual method
  * Class becomes abstract class, cannot be instantiated and can only be implemented through child classes
  * Opposite of abstract class: concrete
  * Child class can inherit from multiple parents