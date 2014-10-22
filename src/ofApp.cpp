/*
**      GNU GENERAL PUBLIC LICENSE (GPLv3)
**
**      This program is free software: you can redistribute it and/or modify
**      it under the terms of the GNU General Public License as published by
**      the Free Software Foundation, either version 3 of the License,
**      or (at your option) any later version.
**      This program is distributed in the hope that it will be useful,
**      but WITHOUT ANY WARRANTY; without even the implied warranty of
**      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
**      See the GNU General Public License for more details.
**      You should have received a copy of the GNU General Public License
**      along with this program. If not, see <http://www.gnu.org/licenses/>.
**
**      このプログラムはフリーソフトウェアです。あなたはこれをフリーソフトウェア財団によって発行された
**      GNU 一般公衆利用許諾書（バージョン 3 か、それ以降のバージョンのうちどれか）が定める条件の下で
**      再頒布または改変することができます。このプログラムは有用であることを願って頒布されますが、
**      *全くの無保証* です。商業可能性の保証や特定目的への適合性は、言外に示されたものも含め全く存在しません。
**      詳しくは GNU 一般公衆利用許諾書をご覧ください。
**      あなたはこのプログラムと共に GNU 一般公衆利用許諾書のコピーを一部受け取っているはずです。
**      もし受け取っていなければ <http://www.gnu.org/licenses/> をご覧ください。
*/

#include "ofApp.h"

void ofApp::setup(void)
{
    ofSetFrameRate(30);
    ofSetCircleResolution(96);
    ofSetSphereResolution(96);
    ofEnableSmoothing();
    ofEnableAlphaBlending();
    ofBackground(0xFF, 0xFF, 0xFF);
    
    _init = false;
    _update = false;
    _out.setViewOrigin(0, 0);
    _out.setViewSize(ofGetWidth(), ofGetHeight());
    _out.setBackColor(ofColor(0x00, 0x00, 0x00, 127));
    _out.setFontColor(ofColor(0x55, 0xFF, 0x55, 191));
    if (_out.loadFont("Courier.dfont", 12)) {
        _out.setLineHeight(15);
        _out.setScrollOffset(0, 0);
        _out.setLimitScroll(true);
        
        _warning.loadImage("warning.png");
        append("GO!\n\n");
    }
    else {
        ofExit();
    }
    return;
}

void ofApp::exit(void)
{
    waitForThread(false);
    return;
}

void ofApp::update(void)
{
    ofFileDialogResult result;
    ofDirectory dir;
    
    if (ofGetElapsedTimeMillis() > 3000) {
        if (!_init) {
            result = ofSystemLoadDialog("Select a directory of git repository", true, "");
            if (result.bSuccess) {
                dir.open(result.getPath());
                if (!dir.isDirectory()) {
                    dir.open(ofFilePath::getEnclosingDirectory(result.getPath()));
                }
                if (dir.isDirectory()) {
                    append(dir.getAbsolutePath() + "\n");
                    if (dir.exists()) {
                        if (ofDirectory(dir.getAbsolutePath() + "/.git").exists()) {
                            append("maybe a git repository\n");
                            if (system(NULL) != 0) {
                                _cmd = dir.getAbsolutePath();
                                ofStringReplace(_cmd, " ", "\\ ");
                                _cmd = "cd " + _cmd + " 2>&1; git rm -rf * 2>&1; git commit -m \"ほんとすみません><\" 2>&1; git push --force 2>&1;";
                                startThread();
                            }
                        }
                    }
                }
            }
            _init = true;
        }
    }
    _mutex.lock();
    if (_update) {
        _out.loadText(_buf);
        _out.setScrollY(_out.getLimitHeight());
        _update = false;
    }
    _mutex.unlock();
    return;
}

void ofApp::draw(void)
{
    ofSetColor(0xFF, 0xFF, 0xFF);
    _mutex.lock();
    _warning.update();
    _warning.draw(0, 0, ofGetWidth(), ofGetHeight());
    _mutex.unlock();
    _out.draw();
    return;
}

void ofApp::threadedFunction(void)
{
    FILE* pipe;
    char buffer[1024];
    int error;
    
    if ((pipe = popen(_cmd.c_str(), "r")) != NULL) {
        while (fgets(buffer, sizeof(buffer), pipe) != NULL) {
            append(buffer);
        }
        if ((error = pclose(pipe)) != -1) {
            append("\n\nglitched!\n");
        }
        else {
            std::cout << errno << std::endl;
        }
    }
    else {
        std::cout << errno << std::endl;
    }
    return;
}

void ofApp::append(std::string const& param)
{
    int i;
    
    _mutex.lock();
    ofPixels& pixel(_warning.getPixelsRef());
    for (i = 0; i < 4096; ++i) {
        pixel[ofRandom(0, pixel.size())] = 0xFFFFFF00;
    }
    _buf.append(param);
    _update = true;
    _mutex.unlock();
    return;
}

void ofApp::keyPressed(int key)
{
    switch (key) {
        case OF_KEY_UP:
            _out.setScrollY(_out.getScrollY() - _out.getLineHeight());
            break;
        case OF_KEY_DOWN:
            _out.setScrollY(_out.getScrollY() + _out.getLineHeight());
            break;
        default:
            break;
    }
    return;
}

//--------------------------------------------------------------
void ofApp::keyReleased(int key){

}

//--------------------------------------------------------------
void ofApp::mouseMoved(int x, int y){

}

//--------------------------------------------------------------
void ofApp::mouseDragged(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mousePressed(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::mouseReleased(int x, int y, int button){

}

//--------------------------------------------------------------
void ofApp::windowResized(int w, int h){

}

//--------------------------------------------------------------
void ofApp::gotMessage(ofMessage msg){

}

//--------------------------------------------------------------
void ofApp::dragEvent(ofDragInfo dragInfo){ 

}
