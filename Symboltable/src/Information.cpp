/*
 * Information.cpp
 *
 *  Created on: 15.04.2015
 *      Author: eriksteigert
 */

#include "../includes/Information.h"

const char* name;
TType typ;

Information::Information(const char* name, TType typ) {
	this->name = name;
	this->typ = typ;
}

const char* Information::getName() {
	return this->name;
}

TType Information::getType() {
	return this->typ;
}

void Information::setName(const char* name) {
	this->name = name;
}

void Information::setType(TType typ) {
	this->typ = typ;
}
