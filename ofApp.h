﻿#pragma once
#include "ofMain.h"

class ofApp : public ofBaseApp {

public:
	void setup();
	void update();
	void draw();

	void keyPressed(int key) {};
	void keyReleased(int key) {};
	void mouseMoved(int x, int y) {};
	void mouseDragged(int x, int y, int button) {};
	void mousePressed(int x, int y, int button) {};
	void mouseReleased(int x, int y, int button) {};
	void windowResized(int w, int h) {};
	void dragEvent(ofDragInfo dragInfo) {};
	void gotMessage(ofMessage msg) {};

	ofEasyCam cam;
	glm::vec3 cam_position;

	ofMesh mesh;

	vector<glm::vec3> top_list;
	vector<glm::vec3> noise_seed_list;
	vector<glm::vec3> location_list;
	vector<ofColor> color_list;
	vector<glm::vec3> velocity_list;
};