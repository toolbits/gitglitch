#pragma once

#include "ofMain.h"
#include "textWriter.h"

class ofApp : public ofBaseApp, private ofThread {
    private:
        bool _init;
        std::string _cmd;
        std::string _buf;
        bool _update;
        textWriter _out;
        ofMutex _mutex;
        ofImage _warning;
    
	public:
		void setup();
        void exit();
		void update();
		void draw();
		
		void keyPressed(int key);
		void keyReleased(int key);
		void mouseMoved(int x, int y);
		void mouseDragged(int x, int y, int button);
		void mousePressed(int x, int y, int button);
		void mouseReleased(int x, int y, int button);
		void windowResized(int w, int h);
		void dragEvent(ofDragInfo dragInfo);
		void gotMessage(ofMessage msg);
    private:
        virtual void threadedFunction(void);
        void append(std::string const& param);
};
