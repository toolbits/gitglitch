/*
**      textWriter
**
**      Original Copyright (C) 2012 - 2012 HORIGUCHI Junshi.
**                                          http://iridium.jp/
**                                          zap00365@nifty.com
**      Portions Copyright (C) <year> <author>
**                                          <website>
**                                          <e-mail>
**      Version     openFrameworks
**      Website     http://iridium.jp/
**      E-mail      zap00365@nifty.com
**
**      This source code is for Xcode.
**      Xcode 4.2 (LLVM compiler 3.0)
**
**      textWriter.cpp
**
**      ------------------------------------------------------------------------
**
**      The MIT License (MIT)
**
**      Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
**      associated documentation files (the "Software"), to deal in the Software without restriction,
**      including without limitation the rights to use, copy, modify, merge, publish, distribute,
**      sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
**      furnished to do so, subject to the following conditions:
**      The above copyright notice and this permission notice shall be included in all copies or
**      substantial portions of the Software.
**      THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING
**      BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.
**      IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY,
**      WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
**      OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
**
**      以下に定める条件に従い、本ソフトウェアおよび関連文書のファイル（以下「ソフトウェア」）の複製を
**      取得するすべての人に対し、ソフトウェアを無制限に扱うことを無償で許可します。
**      これには、ソフトウェアの複製を使用、複写、変更、結合、掲載、頒布、サブライセンス、および、または販売する権利、
**      およびソフトウェアを提供する相手に同じことを許可する権利も無制限に含まれます。
**      上記の著作権表示および本許諾表示を、ソフトウェアのすべての複製または重要な部分に記載するものとします。
**      ソフトウェアは「現状のまま」で、明示であるか暗黙であるかを問わず、何らの保証もなく提供されます。
**      ここでいう保証とは、商品性、特定の目的への適合性、および権利非侵害についての保証も含みますが、それに限定されるものではありません。
**      作者または著作権者は、契約行為、不法行為、またはそれ以外であろうと、ソフトウェアに起因または関連し、
**      あるいはソフトウェアの使用またはその他の扱いによって生じる一切の請求、損害、その他の義務について何らの責任も負わないものとします。
*/

#include "textWriter.h"

//#define __USE_FBO
//#define __USE_VIEW
//#define __USE_SHAPE

textWriter::textWriter(void)
{
    _viewX = 0;
    _viewY = 0;
    _viewWidth = 0;
    _viewHeight = 0;
    _backColor.set(0xFF, 0xFF, 0xFF);
    _fontColor.set(0x00, 0x00, 0x00);
    _ascent = 0;
    _descent = 0;
    _lineHeight = 0;
    _textWidth = 0;
    _textHeight = 0;
    _limit = true;
    _scrollX = 0;
    _scrollY = 0;
}

textWriter::~textWriter(void)
{
}

void textWriter::setViewOrigin(ofPoint const& param)
{
    setViewX(param.x);
    setViewY(param.y);
    return;
}

void textWriter::setViewOrigin(float x, float y)
{
    setViewX(x);
    setViewY(y);
    return;
}

void textWriter::setViewWidth(float param)
{
    if (param < 0) {
        param = 0;
    }
    _viewWidth = param;
    adjustX();
    return;
}

void textWriter::setViewHeight(float param)
{
    if (param < 0) {
        param = 0;
    }
    _viewHeight = param;
    adjustY();
    return;
}

void textWriter::setViewSize(ofPoint const& param)
{
    setViewWidth(param.x);
    setViewHeight(param.y);
    return;
}

void textWriter::setViewSize(float width, float height)
{
    setViewWidth(width);
    setViewHeight(height);
    return;
}

void textWriter::setLineHeight(float param)
{
    if (param < 0) {
        param = 0;
    }
    _lineHeight = param;
    refresh();
    return;
}

float textWriter::getLimitWidth(void) const
{
    float result(0);
    
    if (_textWidth > _viewWidth) {
        result = _textWidth - _viewWidth;
    }
    return result;
}

float textWriter::getLimitHeight(void) const
{
    float result(0);
    
    if (_textHeight > _viewHeight) {
        result = _textHeight - _viewHeight;
    }
    return result;
}

void textWriter::setLimitScroll(bool param)
{
    _limit = param;
    if (_limit) {
        adjustX();
        adjustY();
    }
    return;
}

void textWriter::setScrollX(float param)
{
    _scrollX = param;
    adjustX();
    return;
}

void textWriter::setScrollY(float param)
{
    _scrollY = param;
    adjustY();
    return;
}

void textWriter::setScrollOffset(ofPoint const& param)
{
    setScrollX(param.x);
    setScrollY(param.y);
    return;
}

void textWriter::setScrollOffset(float x, float y)
{
    setScrollX(x);
    setScrollY(y);
    return;
}

bool textWriter::loadFont(string const& path, int size)
{
    ofRectangle bound;
    bool result(false);
    
    _ascent = 0;
    _descent = 0;
    _lineHeight = 0;
#ifdef __USE_SHAPE
    if (_font.loadFont(path, size, true, true)) {
#else
    if (_font.loadFont(path, size, true)) {
#endif
        _font.setSpaceSize(0.5);
        bound = _font.getStringBoundingBox("ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz", 0, 0);
        _ascent = -bound.y;
        _descent = bound.height - _ascent;
        _lineHeight = _font.getSize();
        result = true;
    }
    refresh();
    return result;
}

bool textWriter::loadFile(string const& path)
{
    ofBuffer buffer;
    
    buffer = ofBufferFromFile(path);
    return loadData(&buffer);
}

bool textWriter::loadText(string const& text)
{
    ofBuffer buffer;
    
    buffer = text;
    return loadData(&buffer);
}

ofTexture textWriter::render(void)
{
    ofFbo fbo;
    float y;
    int i;
    
    fbo.allocate(_viewWidth, _viewHeight, GL_RGBA);
    fbo.begin();
    ofPushStyle();
    ofClear(_backColor);
    if (_font.isLoaded() && _lines.size() > 0) {
#ifdef __USE_SHAPE
        glPushAttrib(GL_ENABLE_BIT);
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
#endif
        ofSetColor(_fontColor);
        y = (_lineHeight - _ascent - _descent) / 2 + _ascent - _scrollY;
        for (i = 0; i < _lines.size(); ++i) {
            if (y > -_descent) {
                if (y - _ascent >= _viewHeight) {
                    break;
                }
#ifdef __USE_SHAPE
                _font.drawStringAsShapes(_lines[i], -_scrollX, y);
#else
                _font.drawString(_lines[i], -_scrollX, y);
#endif
            }
            y += _lineHeight;
        }
#ifdef __USE_SHAPE
        glPopAttrib();
#endif
    }
    ofPopStyle();
    fbo.end();
    return fbo.getTextureReference();
}

void textWriter::draw(void)
{
#ifdef __USE_FBO
    render().draw(_viewX, _viewY);
#else
    float y;
    int i;
    
#ifdef __USE_VIEW
    ofPushView();
    ofViewport(_viewX, _viewY, _viewWidth, _viewHeight);
    ofSetupScreenOrtho(_viewWidth, _viewHeight);
#else
    ofPushMatrix();
    ofTranslate(_viewX, _viewY);
#endif
    ofPushStyle();
    ofSetColor(_backColor);
    ofFill();
    ofRect(0, 0, _viewWidth, _viewHeight);
    if (_font.isLoaded() && _lines.size() > 0) {
#ifdef __USE_SHAPE
        glPushAttrib(GL_ENABLE_BIT);
        glEnable(GL_POLYGON_SMOOTH);
        glHint(GL_POLYGON_SMOOTH_HINT, GL_NICEST);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA , GL_ONE_MINUS_SRC_ALPHA);
#endif
        ofSetColor(_fontColor);
        y = (_lineHeight - _ascent - _descent) / 2 + _ascent - _scrollY;
        for (i = 0; i < _lines.size(); ++i) {
            if (y > -_descent) {
                if (y - _ascent >= _viewHeight) {
                    break;
                }
#ifdef __USE_SHAPE
                _font.drawStringAsShapes(_lines[i], -_scrollX, y);
#else
                _font.drawString(_lines[i], -_scrollX, y);
#endif
            }
            y += _lineHeight;
        }
#ifdef __USE_SHAPE
        glPopAttrib();
#endif
    }
    ofPopStyle();
#ifdef __USE_VIEW
    ofPopView();
#else
    ofPopMatrix();
#endif
#endif
    return;
}

bool textWriter::loadData(ofBuffer* buffer)
{
    bool result(false);
    
    _lines.clear();
    if (buffer != NULL) {
        if (buffer->size() > 0) {
            _lines.push_back(buffer->getFirstLine());
            while (!buffer->isLastLine()) {
                _lines.push_back(buffer->getNextLine());
            }
            result = true;
        }
    }
    refresh();
    return result;
}

void textWriter::refresh(void)
{
    float hack_;
    InfoRec info;
    int i;
    
    _infos.clear();
    _textWidth = 0;
    _textHeight = 0;
    if (_font.isLoaded() && _lines.size() > 0) {
        hack_ = _font.stringWidth("__");
        for (i = 0; i < _lines.size(); ++i) {
            info.bound = _font.getStringBoundingBox("_" + _lines[i] + "_", 0, 0);
            info.bound.y = -_ascent;
            info.bound.width -= hack_;
            info.bound.height = _ascent + _descent;
            _infos.push_back(info);
            _textWidth = max(_textWidth, info.bound.width);
            _textHeight += _lineHeight;
        }
    }
    adjustX();
    adjustY();
    return;
}

void textWriter::adjustX(void)
{
    float delta;
    
    if (_limit) {
        delta = _textWidth - _viewWidth;
        if (delta <= 0) {
            _scrollX = 0;
        }
        else if (_scrollX < 0) {
            _scrollX = 0;
        }
        else if (_scrollX > delta) {
            _scrollX = delta;
        }
    }
    return;
}

void textWriter::adjustY(void)
{
    float delta;
    
    if (_limit) {
        delta = _textHeight - _viewHeight;
        if (delta <= 0) {
            _scrollY = 0;
        }
        else if (_scrollY < 0) {
            _scrollY = 0;
        }
        else if (_scrollY > delta) {
            _scrollY = delta;
        }
    }
    return;
}
