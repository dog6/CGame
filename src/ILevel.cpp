#include "../include/level.hpp"

ILevel::~ILevel(){
  TraceLog(LOG_INFO, "CGOL closed");
};

void ILevel::start(){}
void ILevel::load(){}
void ILevel::render(){}
void ILevel::update(){}