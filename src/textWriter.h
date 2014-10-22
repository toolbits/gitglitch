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
**      textWriter.h
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

#ifndef __TEXTWRITER_H
#define __TEXTWRITER_H

#include "ofMain.h"
#include "ofxTrueTypeFontUC.h"

class textWriter {
    private:
        struct InfoRec {
            ofRectangle bound;
        };
    
    private:
                float               _viewX;
                float               _viewY;
                float               _viewWidth;
                float               _viewHeight;
                ofColor             _backColor;
                ofColor             _fontColor;
                ofxTrueTypeFontUC   _font;
                float               _ascent;
                float               _descent;
                float               _lineHeight;
                vector<string>      _lines;
                vector<InfoRec>     _infos;
                float               _textWidth;
                float               _textHeight;
                bool                _limit;
                float               _scrollX;
                float               _scrollY;
    
    public:
        explicit                    textWriter          (void);
                                    ~textWriter         (void);
        // You can use below functions after calling constructor.
                void                setViewX            (float param);
                float               getViewX            (void) const;
                void                setViewY            (float param);
                float               getViewY            (void) const;
                void                setViewOrigin       (ofPoint const& param);
                void                setViewOrigin       (float x, float y);
                ofPoint             getViewOrigin       (void) const;
                void                setViewWidth        (float param);
                float               getViewWidth        (void) const;
                void                setViewHeight       (float param);
                float               getViewHeight       (void) const;
                void                setViewSize         (ofPoint const& param);
                void                setViewSize         (float width, float height);
                ofPoint             getViewSize         (void) const;
                void                setBackColor        (ofColor const& param);
                ofColor const&      getBackColor        (void) const;
                void                setFontColor        (ofColor const& param);
                ofColor const&      getFontColor        (void) const;
        // You can use below functions after calling loadFont().
                float               getFontAscent       (void) const;
                float               getFontDescent      (void) const;
                void                setLineHeight       (float param);
                float               getLineHeight       (void) const;
        // You can use below functions after calling loadFile() or loadText().
                float               getTextWidth        (void) const;
                float               getTextHeight       (void) const;
                ofPoint             getTextSize         (void) const;
                float               getLimitWidth       (void) const; // get scrollable X range
                float               getLimitHeight      (void) const; // get scrollable Y range
                ofPoint             getLimitSize        (void) const;
                void                setLimitScroll      (bool param);
                bool                getLimitScroll      (void) const;
                void                setScrollX          (float param);
                float               getScrollX          (void) const;
                void                setScrollY          (float param);
                float               getScrollY          (void) const;
                void                setScrollOffset     (ofPoint const& param);
                void                setScrollOffset     (float x, float y);
                ofPoint             getScrollOffset     (void) const;
        // You can use below functions after calling constructor.
                bool                loadFont            (string const& path, int size);
                bool                loadFile            (string const& path);
                bool                loadText            (string const& text);
                ofTexture           render              (void);
                void                draw                (void);
    private:
                bool                loadData            (ofBuffer* buffer);
                void                refresh             (void);
                void                adjustX             (void);
                void                adjustY             (void);
};

inline void textWriter::setViewX(float param)
{
    _viewX = param;
    return;
}

inline float textWriter::getViewX(void) const
{
    return _viewX;
}

inline void textWriter::setViewY(float param)
{
    _viewY = param;
    return;
}

inline float textWriter::getViewY(void) const
{
    return _viewY;
}

inline ofPoint textWriter::getViewOrigin(void) const
{
    return ofPoint(getViewX(), getViewY());
}

inline float textWriter::getViewWidth(void) const
{
    return _viewWidth;
}

inline float textWriter::getViewHeight(void) const
{
    return _viewHeight;
}

inline ofPoint textWriter::getViewSize(void) const
{
    return ofPoint(getViewWidth(), getViewHeight());
}

inline void textWriter::setBackColor(ofColor const& param)
{
    _backColor = param;
    return;
}

inline ofColor const& textWriter::getBackColor(void) const
{
    return _backColor;
}

inline void textWriter::setFontColor(ofColor const& param)
{
    _fontColor = param;
    return;
}

inline ofColor const& textWriter::getFontColor(void) const
{
    return _fontColor;
}

inline float textWriter::getFontAscent(void) const
{
    return _ascent;
}

inline float textWriter::getFontDescent(void) const
{
    return _descent;
}

inline float textWriter::getLineHeight(void) const
{
    return _lineHeight;
}

inline float textWriter::getTextWidth(void) const
{
    return _textWidth;
}

inline float textWriter::getTextHeight(void) const
{
    return _textHeight;
}

inline ofPoint textWriter::getTextSize(void) const
{
    return ofPoint(getTextWidth(), getTextHeight());
}

inline ofPoint textWriter::getLimitSize(void) const
{
    return ofPoint(getLimitWidth(), getLimitHeight());
}

inline bool textWriter::getLimitScroll(void) const
{
    return _limit;
}

inline float textWriter::getScrollX(void) const
{
    return _scrollX;
}

inline float textWriter::getScrollY(void) const
{
    return _scrollY;
}

inline ofPoint textWriter::getScrollOffset(void) const
{
    return ofPoint(getScrollX(), getScrollY());
}

#endif
