#include <iostream>
#include <cmath>
#include <ctime>
#include <iomanip>
#include "domain2D.hpp"

class myDomain : public domain2D {
public:
	myDomain(long double xcenter, long double ycenter, long double Lx, long double Ly, int nNodes) {
		this->xcenter	=	xcenter;
		this->ycenter	=	ycenter;
		this->Lx		=	Lx;
		this->Ly		=	Ly;
		this->nNodes	=	nNodes;
	};
	long double integrand(long double x, long double y) {
		return log(x*x+y*y)+1.0/sqrt((x-1)*(x-1)+(y-1)*(y-1));
	};
	~myDomain() {};
};

int main() {
	long double xcenter	=	0.0;	//	'x' coordinate of the center of the domain
	long double ycenter	=	0.0;	//	'y' coordinate of the center of the domain
	long double Lx		=	3.0;	//	Semi-length of the domain along X axis
	long double Ly		=	4.0;	//	Semi-length of the domain along Y axis
	int nNodes		=	6;		//	Nodes of integration along one dimension for each panel

	// std::cout << std::endl << mine->integrand(1.0,1.0) << std::endl;
	long double epsilon	=	1e-15;	//	Accuracy of the quadrature
	long double start, end;
	long double CPS		=	CLOCKS_PER_SEC;
	start	=	clock();
	myDomain* mine	=	new myDomain(xcenter, ycenter, Lx, Ly, nNodes);
	mine->obtain_Quadrature(epsilon);
	end		=	clock();

	std::cout << std::endl << std::setprecision(ceil(-log10(epsilon))) << "Quadrature is: " << mine->integral << std::endl;
	std::cout << std::endl << "Total number of panels: " << mine->leafNodes.size() << std::endl;
	std::cout << std::endl << "Total number of nodes: " << mine->leafNodes.size()*mine->nNodes*mine->nNodes << std::endl;
	std::cout << std::endl << "Number of levels of adaptivity: " << mine->tree.size() << std::endl;
	std::cout << std::endl << "Time taken: " << (end-start)/CPS << " seconds" << std::endl;
	mine->outputAdaptiveGrid("Domain2D.tex");
	delete mine;
}