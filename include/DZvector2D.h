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

/***************************************************************************
 * Change Log                                                              *
 *-------------------------------------------------------------------------*
 * 03-09-2015	file created                                               *
 ***************************************************************************/



#ifndef DZVECTOR2D_H
#define DZVECTOR2D_H


#include <math.h>



/*****************************************************************
 *
 * Class:		DZvector2D
 *
 * Description:	Implementation of a cinematic vector in 2D
 *
 * Interface:	getX		return x value
 *				getY		return y value
 *				setX		set x value
 *				setY		set Y value
 *				length		return lenght of the vector
 *				+			operator +
 *				+=			operator +=
 *				*			operator * (scalar)
 *				*=			operator *= (scalar)
 *				-			operator -
 *				-=			operator -=
 *				/			operator / (scalar)
 *				/=			operator /= (scalar)
 *				normalize	make it a versor
 *				getVersor	get versor
 *
 ****************************************************************/
class DZvector2D
{
	public:
		//--------------------------------------------------------
		// Name:		DZvector2D::DZvector2D
		// Description:	Constructor
		// Arguments:	void
		//--------------------------------------------------------
		DZvector2D()
		{
			X = 0;
			Y = 0;
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::DZvecotr2D
		// Description:	Constructor
		// Arguments:	x, y coordinates
		//--------------------------------------------------------
		DZvector2D(float x, float y)
		{
			X = x;
			Y = y;
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::getX
		// Description:	return x value
		// Arguments:	void
		//--------------------------------------------------------
		const float getX()
		{
			return X;
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::getY
		// Description:	return y value
		// Arguments:	void
		//--------------------------------------------------------
		const float getY()
		{
			return Y;
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::setX
		// Description:	sets x value
		// Arguments:	the new x value
		//--------------------------------------------------------
		void setX(float x)
		{
			X = x;
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::setY
		// Description:	sets y value
		// Arguments:	the new y value
		//--------------------------------------------------------
		void setY(float y)
		{
			Y = y;
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::length
		// Description:	return length of the vector
		// Arguments:	void
		//--------------------------------------------------------
		float length()
		{
			return sqrt(X*X + Y*Y);
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::operator+
		// Description:	addition operator
		// Arguments:	v2 the vector to add to this one
		//--------------------------------------------------------
		DZvector2D operator+(const DZvector2D& v2) const
		{
			return DZvector2D(X + v2.X, Y + v2.Y);
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::operator+=
		// Description:	add and assign operator
		// Arguments:	v1, v2 operands
		//--------------------------------------------------------
		friend DZvector2D& operator+=(DZvector2D& v1, DZvector2D& v2)
		{
			v1.X += v2.X;
			v1.Y += v2.Y;
			return v1;
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::operator*
		// Description:	multiplication with a scalar
		// Arguments:	scalar value
		//--------------------------------------------------------
		DZvector2D operator*(float scalar)
		{
			return DZvector2D(scalar * X, scalar * Y);
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::operator *=
		// Description:	multiply with scalar and assign operator
		// Arguments:	scalar
		//--------------------------------------------------------
		DZvector2D operator*=(float scalar)
		{
			X *= scalar;
			Y *= scalar;
			return *this;
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::operator-
		// Description:	subtraction operator
		// Arguments:	v2
		//--------------------------------------------------------
		DZvector2D operator-(const DZvector2D& v2) const
		{
			return DZvector2D(X - v2.X, Y - v2.Y);
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::operator-=
		// Description:	subtract and assign operator
		// Arguments:	v1, v2
		//--------------------------------------------------------
		friend DZvector2D& operator-=(DZvector2D& v1, const DZvector2D& v2)
		{
			v1.X -= v2.X;
			v1.Y -= v2.Y;
			return v1;
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::operator/
		// Description:	division with scalar operator
		// Arguments:	scalar
		//--------------------------------------------------------
		DZvector2D operator/(float scalar)
		{
			return DZvector2D(X/scalar, Y/scalar);
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::operator/=
		// Description:	divide with scalar and assign operator
		// Arguments:	scalar
		//--------------------------------------------------------
		DZvector2D& operator /=(float scalar)
		{
			X /= scalar;
			Y /= scalar;
			return *this;
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::normalize
		// Description:	make a versor of this vector
		// Arguments:	void
		//--------------------------------------------------------
		void normalize()
		{
			float len = length();
			if (len > 0)
			{
				(*this) *= (1/len);
			}
		}

		//--------------------------------------------------------
		// Name:		DZvector2D::getVersor
		// Description:	return the versor of given vector
		// Arguments:	void
		//--------------------------------------------------------
		DZvector2D getVersor()
		{
			float len = length();
			return DZvector2D(X/len, Y/len);
		}

	protected:
	private:
		float X;
		float Y;
};

#endif // DZVECTOR2D_H
