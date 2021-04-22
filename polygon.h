#ifndef POLY_H
#define POLY_H
#include <vector>
#include "vec2.h"
#include "color.h"

/* simple data representation of a convex polygon - defined by a list of vertices */
class Polygon {
  public:
	Polygon(std::vector<vec2>& inVerts, double d, color C) : theVerts(inVerts), inC(C), depth(d) {
		if (this->concave()) {
			std::cerr << "Not convex will not draw as expected" << std::endl;
		}
	}

	bool eval(double x, double y);
	void addVert(vec2 inV) { theVerts.push_back(inV); }
	color getInC() const {return inC; }
	double getDepth() const {return depth; }
	bool concave();

	// range based for loop of just vec2 is making a copy of it, for vec2 vert : theVerts is incorrect
	// for vec2 &vert: theVerts works
	void translate(vec2 translation) {	
		for (int i = 0; i < theVerts.size(); i++) {
			theVerts[i]+=translation;
		}
	}

  private:
	std::vector<vec2>& theVerts; //reference
	color inC;
	double depth;
};

#endif