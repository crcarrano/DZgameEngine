/**************************************************************************
 *   Copyright (C) 2015 by Carlo Carrano                                  *
 *   crc@dazzlingsolutions.com                                            *
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU General Public License as published by *
 *   the Free Software Foundation; version 2 of the License.              *
 *   This program is distributed in the hope that it will be useful, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU     *
 *   General Public License for more details.                             *
 *   You should have received a copy of the GNU General Public License    *
 *   along with this program; if not, write to the Free Software          *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  *
 *   USA.  																  *
 **************************************************************************/

/**************************************************************************
 * Change Log                                                             *
 *------------------------------------------------------------------------*
 * 03-14-2015	file created                                              *
 **************************************************************************/


#include "DZsdlObject.h"
#include <cmath>


DZsdlObject::DZsdlObject(const DZparams* paramPtr,DZarray<DZobject*>* obj_list)
			: DZobject(param_ptr)
{
	param_ptr = new DZparams(paramPtr);
	object_list = obj_list;
}

DZsdlObject::~DZsdlObject()
{
	if (param_ptr != 0) delete param_ptr;
}

void	DZsdlObject::draw()
{
	if (param_ptr->NumFrames == 0)
	{
		param_ptr->TextureManagerPtr->draw(param_ptr->TextureID,
										   param_ptr->Position.getX(),
										   param_ptr->Position.getY(),
										   param_ptr->RotationCenter.getX(),
										   param_ptr->RotationCenter.getY(),
										   param_ptr->angular_position,
										   param_ptr->Width,
										   param_ptr->Height,
										   param_ptr->flip);
	}
	else
	{
		param_ptr->TextureManagerPtr->drawFrame(param_ptr->TextureID,
												param_ptr->Position.getX(),
												param_ptr->Position.getY(),
												param_ptr->RotationCenter.getX(),
												param_ptr->RotationCenter.getY(),
												param_ptr->angular_position,
												param_ptr->Width,
												param_ptr->Height,
												param_ptr->CurrentRow,
												param_ptr->CurrentFrame,
												param_ptr->flip);
	}
}


DZvector2D&	DZsdlObject::getPosition()
{
	return param_ptr->Position;
}


DZvector2D&	DZsdlObject::getVelocity()
{
	return param_ptr->Velocity;
}


DZvector2D&	DZsdlObject::getAcceleration()
{
	return param_ptr->Acceleration;
}


unsigned int	DZsdlObject::getWidth()
{
	return param_ptr->Width;
}


unsigned int	DZsdlObject::getHeight()
{
	return param_ptr->Height;
}


unsigned int	DZsdlObject::getCurrentRow()
{
	return param_ptr->CurrentRow;
}


unsigned int	DZsdlObject::getCurrentFrame()
{
	return param_ptr->CurrentFrame;
}


unsigned int	DZsdlObject::getNumRows()
{
	return param_ptr->NumRows;
}


unsigned int	DZsdlObject::getNumFrames()
{
	return param_ptr->NumFrames;
}


unsigned int	DZsdlObject::getTextureID()
{
	return param_ptr->TextureID;
}

DZtextureManager* DZsdlObject::getTextureManager()
{
	return param_ptr->TextureManagerPtr;
}


SDL_RendererFlip  DZsdlObject::getFlipFlag()
{
	return param_ptr->flip;
}

DZvector2D& DZsdlObject::getRotationCenter()
{
	return param_ptr->RotationCenter;
}

float DZsdlObject::getAngularPosition()
{
	return param_ptr->angular_position;
}

float DZsdlObject::getAngularVelocity()
{
	return param_ptr->angular_velocity;
}

float DZsdlObject::getAngularAcceleration()
{
	return param_ptr->angular_acceleration;
}

DZarray<DZobject*>* DZsdlObject::getObjectList()
{
	return object_list;
}

bool DZsdlObject::collision_check()
{
	DZsdlObject* obj_ptr;
	unsigned int num;

	num = object_list->getSize();

	for (unsigned int i = 0 ; i < num ; i++)
	{
		obj_ptr = (DZsdlObject*) (*object_list)[i];

		if (obj_ptr == 0)
		{
			continue;
		}

		if (obj_ptr == this)
		{
			continue;
		}

		if (param_ptr->box_collision == true)
		{
			if (obj_ptr->param_ptr->box_collision == true)
			{
				return bounding_box_collision_check(obj_ptr);
			}
			else if (obj_ptr->param_ptr->circular_collision == true)
			{
				return box_circular_collision_check(obj_ptr);
			}
		}

		if (param_ptr->circular_collision == true)
		{
			if (obj_ptr->param_ptr->box_collision == true)
			{
				return box_circular_collision_check(obj_ptr);
			}
			else if (obj_ptr->param_ptr->circular_collision == true)
			{
				return circular_collision_check(obj_ptr);
			}
		}
	}

	return false;
}

bool DZsdlObject::bounding_box_collision_check(DZsdlObject* obj_ptr)
{

	int leftA, rightA, topA, bottomA;
	int leftB, rightB, topB, bottomB;

	leftA =		param_ptr->Position.getX();
	rightA =	param_ptr->Position.getX() + param_ptr->Width;
	topA =		param_ptr->Position.getY();
	bottomA =	param_ptr->Position.getY() + param_ptr->Height;

	leftB =		obj_ptr->param_ptr->Position.getX();
	rightB =	obj_ptr->param_ptr->Position.getX() + obj_ptr->param_ptr->Width;
	topB =		obj_ptr->param_ptr->Position.getY();
	bottomB =	obj_ptr->param_ptr->Position.getY() + obj_ptr->param_ptr->Height;

	if (bottomA < bottomB && bottomA > topB && rightA > leftB && rightA < rightB)
	{
		return true;
	}

	if (topA < bottomB && topA > topB && rightA > leftB && rightA < rightB)
	{
		return true;
	}

	if (topB < bottomA && topB > topA && rightB > leftA && rightB < rightA)
	{
		return true;
	}

	if (bottomB < bottomA && bottomB > topA && rightB > leftA && rightB < rightA)
	{
		return true;
	}

	return false;
}


bool DZsdlObject::circular_collision_check(DZsdlObject* obj_ptr)
{
	int xA, yA, rA;
	int xB, yB, rB;

	rA = param_ptr->Width < param_ptr->Height ? param_ptr->Width/2 : param_ptr->Height/2;
	xA = param_ptr->Position.getX() + rA;
	yA = param_ptr->Position.getY() + rA;

	rB = obj_ptr->param_ptr->Width < obj_ptr->param_ptr->Height ? obj_ptr->param_ptr->Width/2 : obj_ptr->param_ptr->Height/2;
	xB = obj_ptr->param_ptr->Position.getX() + rB;
	yB = obj_ptr->param_ptr->Position.getY() + rB;

	if ((pow(xB - xA, 2) + pow(yB - yA, 2)) < pow(rA + rB, 2))
	{
		return true;
	}

	return false;
}


bool DZsdlObject::box_circular_collision_check(DZsdlObject* obj_ptr)
{
	int leftA, rightA, topA, bottomA;
	int xB, yB, rB;

	if (param_ptr->box_collision == true)
	{
		leftA =		param_ptr->Position.getX();
		rightA =	param_ptr->Position.getX() + param_ptr->Width;
		topA =		param_ptr->Position.getY();
		bottomA =	param_ptr->Position.getY() + param_ptr->Height;

		rB = obj_ptr->param_ptr->Width < obj_ptr->param_ptr->Height ? obj_ptr->param_ptr->Width/2 : obj_ptr->param_ptr->Height/2;
		xB = obj_ptr->param_ptr->Position.getX() + rB;
		yB = obj_ptr->param_ptr->Position.getY() + rB;
	}
	else
	{
		leftA =		obj_ptr->param_ptr->Position.getX();
		rightA =	obj_ptr->param_ptr->Position.getX() + param_ptr->Width;
		topA =		obj_ptr->param_ptr->Position.getY();
		bottomA =	obj_ptr->param_ptr->Position.getY() + param_ptr->Height;

		rB = param_ptr->Width < param_ptr->Height ? param_ptr->Width/2 : param_ptr->Height/2;
		xB = param_ptr->Position.getX() + rB;
		yB = param_ptr->Position.getY() + rB;
	}

	if (xB+rB <= leftA) return false;
	if (xB-rB >= rightA) return false;
	if (yB+rB <= topA) return false;
	if (yB-rB >= bottomA) return false;

	return true;
}



