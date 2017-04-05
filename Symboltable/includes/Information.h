/*
 * Information.hpp
 *
 *  Created on: 13.04.2015
 *      Author: eriksteigert
 */

#ifndef INFORMATION_H_
#define INFORMATION_H_

#include "../../Automat/includes/Token.h"

using namespace std;

class Information {

	private:
	const char* name;
	TType typ;

public:
	const char* getName();
	TType getType();
	void setName(const char*);
	void setType(TType);
	Information(const char*, TType);

};





#endif /* INFORMATION_HPP_ */




