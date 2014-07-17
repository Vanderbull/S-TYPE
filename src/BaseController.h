#include <iostream>
using namespace std;
class BaseController
{
public:
	virtual void CreateAnimal(){cout << "RESPOND GOT DAMN IT!!" << endl;};
	virtual void CreateAnimals(){cout << "RESPOND GOT DAMN IT!!" << endl;};
	virtual void DrawAnimals(){cout << "RESPOND GOT DAMN IT!!" << endl;};
};

class IComponent {
public:
  virtual void OnCreate() = 0;
  virtual void OnDestroy() = 0;
};

class Renderable : public IComponent {
public:
  virtual void OnCreate() {
	  cout << "Creating a component" << endl;
	  //register this 
  }
  virtual void OnDestroy() {
	  //unregister this 
  }
};


