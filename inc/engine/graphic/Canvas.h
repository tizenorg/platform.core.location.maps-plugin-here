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

#ifndef HERE_GRAPHIC_CANVAS_H
#define HERE_GRAPHIC_CANVAS_H

#include <cairo/cairo.h>
#include <vector>
#include "common/HereMaps_global.h"
#include "base/BaseObject.h"
#include "graphic/Color.h"
#include "graphic/BufferInfo.h"
#include "graphic/FloatPoint.h"

TIZEN_MAPS_BEGIN_NAMESPACE

class Canvas : public Object
{
public:
	typedef enum
	{
		LINESTYLE_SOLID,
		LINESTYLE_DOTTED,
		LINESTYLE_MAX,
	} LineStyleType;

	typedef std::vector<FloatPoint*> tPoint;
	Canvas(void);
	virtual ~Canvas(void);
	result Construct(const BufferInfo& bufferInfo);
	result FillPolygon(const Color& color, const tPoint& points);
	result DrawPolyline(const tPoint& points);
	result SetLineWidth(int width);
	result SetLineStyle(LineStyleType lineStyle);
	void SetForegroundColor(const Color& fgColor);
protected:
	void* _pNativeGfxEngine;
private:
	unsigned long __ComposeColor(unsigned long color32, int opacity);
	void __SetColor(cairo_t* pCairo, unsigned long composedColor);
	void __SetLineStyle(cairo_t* pCairo, LineStyleType lineStyle);

	unsigned long* __pBuffer;
	unsigned long __fgColor;
	int __lineWidth;
	cairo_operator_t __cairo_operator;
	Color __fgColorNative;
	int __fgOpacity;
	LineStyleType __lineStyle;
};

TIZEN_MAPS_END_NAMESPACE

#endif /* HERE_GRAPHIC_CANVAS_H */
