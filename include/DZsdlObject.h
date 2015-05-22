/**************************************************************************
 *   Copyright (C) 2015 by Carlo Carrano                                  *
 *   crc@dazzlingsolutions.com                                            *
 *                                                                        *
 *   This program is free software; you can redistribute it and/or modify *
 *   it under the terms of the GNU Lesser General Public License as       *
 *   published by the Free Software Foundation; version 3 of the License. *
 *   This program is distributed in the hope that it will be useful, but  *
 *   WITHOUT ANY WARRANTY; without even the implied warranty of           *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE. See the GNU     *
 *   Lesser General Public License for more details.                      *
 *   You should have received a copy of the Lesser GNU General Public     *
 *   License along with this program; if not, write to the Free Software  *
 *   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307  *
 *   USA.  																  *
 **************************************************************************/

/**************************************************************************
 * Change Log                                                             *
 *------------------------------------------------------------------------*
 * 05-21-2015	modified distribution license                             *
 * 03-14-2015	file created                                              *
 **************************************************************************/


#ifndef DZSDLOBJECT_H
#define DZSDLOBJECT_H

#include <DZobject.h>
#include "DZparams.h"


/*****************************************************************
 *
 * Class:		DZsdlObject
 *
 * Description:	Derived by DZobject.
 *				Implements the general application object
 *				using polymorphism.
 *
 * Interface:	draw()
 *				update()
 *				getPosition()
 *				getVelocity()
 *				getAcceleration()
 *				getWidth()
 *				getHeight()
 *				getCurrentRow()
 *				getCurrentFrame()
 *				getNumRows()
 *				getNumFrames()
 *				getTextureID()
 *				getTextureManager()
 *				getFlipFlag()
 *				collision_check()
 *
 ****************************************************************/


class DZsdlObject : public DZobject
{
	public:
		DZsdlObject(const DZparams* paramPtr, DZarray<DZobject*>* obj_list);
		~DZsdlObject();

		virtual void	draw();
		virtual void	update() = 0;

		virtual DZvector2D&	getPosition();
		virtual DZvector2D&	getVelocity();
		virtual DZvector2D&	getAcceleration();

		virtual DZvector2D&	getRotationCenter();
		virtual float		getAngularPosition();
		virtual float		getAngularVelocity();
		virtual float		getAngularAcceleration();

		virtual unsigned int	getWidth();
		virtual unsigned int	getHeight();
		virtual unsigned int	getCurrentRow();
		virtual unsigned int	getCurrentFrame();
		virtual unsigned int	getNumRows();
		virtual unsigned int	getNumFrames();
		virtual unsigned int	getTextureID();

		virtual DZtextureManager* getTextureManager();
		virtual SDL_RendererFlip  getFlipFlag();

		virtual DZarray<DZobject*>* getObjectList();

		virtual bool collision_check();

	protected:
		DZparams* param_ptr;
		DZarray<DZobject*>*  object_list;

	private:
		bool	bounding_box_collision_check(DZsdlObject* obj_ptr);
		bool	circular_collision_check(DZsdlObject* obj_ptr);
		bool	box_circular_collision_check(DZsdlObject* obj_ptr);
};

#endif // DZSDLOBJECT_H
