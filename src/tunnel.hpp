#pragma once

#include "grid_cell.hpp"

class tunnel : public grid_cell
{
public:
	tunnel(float x, float y, float width, float height);
	virtual void draw() override;
};