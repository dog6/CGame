#include "../include/level.hpp"

ILevel::~ILevel(){
  TraceLog(LOG_INFO, "Closed level ", this->name);
};

void ILevel::setLevelName(const char* levelName){
  this->name = levelName;
}
const char* ILevel::getLevelName(){
  return this->name;
}

/*
void ILevel::start(){}
void ILevel::load(){}
void ILevel::render(){}
void ILevel::update(){}
*/