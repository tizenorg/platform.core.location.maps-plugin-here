//
// Copyright (c) 2012 Samsung Electronics Co., Ltd.
//
// Licensed under the Apache License, Version 2.0 (the License);
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//

#ifndef HERE_GRAPHIC_UTILTYPE_H
#define HERE_GRAPHIC_UTILTYPE_H

#include "common/HereMaps_global.h"

TIZEN_MAPS_BEGIN_NAMESPACE

namespace _Util
{

template <unsigned int preFixed, unsigned int postFixed>
struct FixedPoint
{
	FixedPoint(void)
		: __fixedPoint(0)
	{
	}

	FixedPoint(const FixedPoint& rhs)
		: __fixedPoint(rhs.__fixedPoint)
	{
	}

	explicit FixedPoint(int value)
		: __fixedPoint(value << SHIFT)
	{
	}

	explicit FixedPoint(long value)
		: __fixedPoint(value << SHIFT)
	{
	}

	explicit FixedPoint(float value)
		: __fixedPoint(value * ((1 << SHIFT) * 1.0f))
	{
	}

	explicit FixedPoint(double value)
		: __fixedPoint(value * ((1 << SHIFT) * 1.0))
	{
	}

	inline int
	ToInt() const
	{
		return (__fixedPoint >> SHIFT);
	}

	inline float
	ToFloat() const
	{
		return (__fixedPoint / ((1 << SHIFT) * 1.0f));
	}

	inline double
	ToDouble() const
	{
		return (__fixedPoint / ((1 << SHIFT) * 1.0));
	}

	inline void
	Reset(int fixedPointValue)
	{
		__fixedPoint = fixedPointValue;
	}

	inline operator const int(void)
	{
		return __fixedPoint;
	}

// operator +
	inline FixedPoint
	operator +(const FixedPoint& rhs) const
	{
		FixedPoint<preFixed, SHIFT> tempFixed(0);

		tempFixed.__fixedPoint = __fixedPoint + rhs.__fixedPoint;

		return tempFixed;
	}

// operator -
	inline FixedPoint
	operator -(const FixedPoint& rhs) const
	{
		FixedPoint<preFixed, SHIFT> tempFixed(0);

		tempFixed.__fixedPoint = __fixedPoint - rhs.__fixedPoint;

		return tempFixed;
	}

// operator ==
	template <typename T>
	inline bool
	operator ==(const T& rhs) const
	{
		return (ToFloat() == rhs);
	}

	inline bool
	operator ==(const FixedPoint& rhs) const
	{
		return (ToFloat() == rhs.ToFloat);
	}

// operator !=
	template <typename T>
	inline bool
	operator !=(const T& rhs) const
	{
		return (ToFloat() != rhs);
	}

	inline bool
	operator !=(const FixedPoint& rhs) const
	{
		return (ToFloat() != rhs.ToFloat());
	}

// operator <=
	template <typename T>
	inline bool
	operator <=(const T& rhs) const
	{
		return (ToFloat() <= rhs);
	}

	inline bool
	operator <=(const FixedPoint& rhs) const
	{
		return (ToFloat() <= rhs.ToFloat());
	}

// operator >=
	template <typename T>
	inline bool
	operator >=(const T& rhs) const
	{
		return (ToFloat() >= rhs);
	}

	inline bool
	operator >=(const FixedPoint& rhs) const
	{
		return (ToFloat() >= rhs.ToFloat());
	}

// operator >
	template <typename T>
	inline bool
	operator >(const T& rhs) const
	{
		return (ToFloat() > rhs);
	}

	inline bool
	operator >(const FixedPoint& rhs) const
	{
		return (ToFloat() > rhs.ToFloat());
	}

// operator <
	template <typename T>
	inline bool
	operator <(const T& rhs) const
	{
		return (ToFloat() < rhs);
	}

	inline bool
	operator <(const FixedPoint& rhs) const
	{
		return (ToFloat() < rhs.ToFloat());
	}

	int __fixedPoint;
	enum { SHIFT = postFixed };
};

typedef FixedPoint<26, 6> FixedPoint26_6;
typedef FixedPoint<22, 10> FixedPoint22_10;


template <typename T>
struct Point
{
	T x;
	T y;
};

template <typename T>
struct Dimension
{
	T w;
	T h;
};

template <typename T>
struct Rectangle
{
	T x;
	T y;
	T w;
	T h;
};

template <typename T>
inline bool
operator ==(const Rectangle<T>& lhs, const Rectangle<T>& rhs)
{
	return (lhs.x == rhs.x) && (lhs.y == rhs.y) && (lhs.w == rhs.w) && (lhs.h == rhs.h);
}

template <typename T>
inline bool
operator !=(const Rectangle<T>& lhs, const Rectangle<T>& rhs)
{
	return !(operator ==(lhs, rhs));
}

template <typename T>
struct Bounds
{
	T x1;
	T y1;
	T x2;
	T y2;

	bool IsInside(T x, T y)
	{
		return ((x >= x1) && (x < x2) && (y >= y1) && (y < y2));
	}

	bool IsInsideX(T x)
	{
		return ((x >= x1) && (x < x2));
	}
};

////////////////////////////////////////////////////////////////////////////////
// String

struct String
{
	const wchar_t* pStart;
	int length;

	String(void)
		: pStart(L"")
		, length(0)
	{
	}

	String(const wchar_t* pInputString, int inputStringLength)
		: pStart(pInputString)
		, length(inputStringLength)
	{
	}

	String(const wchar_t* pInputString, int inputStringLength, int offset, int clippedLength)
	{
		const wchar_t* pInputStart = pInputString;
		const wchar_t* pInputEnd = pInputStart + inputStringLength;

		const wchar_t* pRevisedStart = pInputString + offset;
		const wchar_t* pRevisedEnd = pRevisedStart + clippedLength;

		const wchar_t* pClippedStart = (pInputStart > pRevisedStart) ? pInputStart : pRevisedStart;
		const wchar_t* pClippedEnd = (pInputEnd < pRevisedEnd) ? pInputEnd : pRevisedEnd;

		if (pClippedEnd - pClippedStart > 0)
		{
			this->pStart = pClippedStart;
			this->length = pClippedEnd - pClippedStart;
		}
		else
		{
			this->pStart = (pClippedStart == pInputString) ? pClippedStart : L"";
			this->length = 0;
		}
	}

	operator const wchar_t*(void)
	{
		return pStart;
	}
};

typedef std::wstring WString;

} // _Util

TIZEN_MAPS_END_NAMESPACE

#endif /* HERE_GRAPHIC_UTILTYPE_H */
