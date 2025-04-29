#pragma once
#include <vector>
#include <string>
#include <memory>

template<class DerivedState, class DerivedMove>
class State
{
public:
	virtual void displayState() = 0;
	virtual std::unique_ptr<DerivedState> getNextState(DerivedMove m) = 0;
};

