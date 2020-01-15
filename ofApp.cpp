#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(1.5);
	ofEnableDepthTest();

	for (int i = 0; i < 12; i++) {

		this->noise_seed_list.push_back(glm::vec3(ofRandom(1000), ofRandom(1000), ofRandom(1000)));
	}

	this->mesh.setMode(ofPrimitiveMode::OF_PRIMITIVE_LINES);
}

//--------------------------------------------------------------
void ofApp::update() {

	this->mesh.clear();
	this->top_list.clear();

	this->cam_position = glm::vec3(
		ofMap(ofNoise(this->noise_seed_list[0].x, (ofGetFrameNum() - 50) * 0.003), 0, 1, -300, 300),
		ofMap(ofNoise(this->noise_seed_list[0].y, (ofGetFrameNum() - 50) * 0.003), 0, 1, -300, 300),
		ofMap(ofNoise(this->noise_seed_list[0].z, (ofGetFrameNum() - 50) * 0.003), 0, 1, -300, 300)
	);

	auto first = true;
	for (auto& noise_seed : this->noise_seed_list) {

		auto location = glm::vec3(
			ofMap(ofNoise(noise_seed.x, ofGetFrameNum() * 0.003), 0, 1, -300, 300),
			ofMap(ofNoise(noise_seed.y, ofGetFrameNum() * 0.003), 0, 1, -300, 300),
			ofMap(ofNoise(noise_seed.z, ofGetFrameNum() * 0.003), 0, 1, -300, 300)
		);
		this->top_list.push_back(location);

		auto next = glm::vec3(
			ofMap(ofNoise(noise_seed.x, (ofGetFrameNum() + 1) * 0.003), 0, 1, -300, 300),
			ofMap(ofNoise(noise_seed.y, (ofGetFrameNum() + 1) * 0.003), 0, 1, -300, 300),
			ofMap(ofNoise(noise_seed.z, (ofGetFrameNum() + 1) * 0.003), 0, 1, -300, 300)
		);
		auto distance = location - next;
		distance *= 2;

		auto future = location + distance * 30;
		auto random_deg_1 = ofRandom(360);
		auto random_deg_2 = ofRandom(360);
		future += glm::vec3(
			30 * cos(random_deg_1 * DEG_TO_RAD) * sin(random_deg_2 * DEG_TO_RAD),
			30 * sin(random_deg_1 * DEG_TO_RAD) * sin(random_deg_2 * DEG_TO_RAD),
			30 * cos(random_deg_2 * DEG_TO_RAD)
		);

		auto future_distance = future - location;

		this->location_list.push_back(location);
		this->velocity_list.push_back(glm::normalize(future_distance) * glm::length(distance));
		first ? this->color_list.push_back(ofColor(239, 39, 39)) : this->color_list.push_back(ofColor(39));
		first = false;
	}

	for (int i = this->location_list.size() - 1; i > -1; i--) {

		this->location_list[i] += this->velocity_list[i];
		this->velocity_list[i] *= 1.01;

		if (glm::length(this->location_list[i]) > 720) {

			this->location_list.erase(this->location_list.begin() + i);
			this->velocity_list.erase(this->velocity_list.begin() + i);
			this->color_list.erase(this->color_list.begin() + i);
		}
	}

	for (int i = 0; i < this->location_list.size(); i++) {

		this->mesh.addVertex(this->location_list[i]);
		this->mesh.addColor(this->color_list[i]);
	}

	for (int i = 0; i < this->mesh.getNumVertices(); i++) {

		for (int k = i + 1; k < this->mesh.getNumVertices(); k++) {

			if (glm::distance(this->mesh.getVertex(i), this->mesh.getVertex(k)) < 50) {

				this->mesh.addIndex(i);
				this->mesh.addIndex(k);
			}
		}
	}
}

//--------------------------------------------------------------
void ofApp::draw() {

	this->cam.setPosition(this->cam_position + glm::vec3(0, 0, 250));
	this->cam.lookAt(this->top_list[0]);
	this->cam.begin();

	this->mesh.drawWireframe();

	for (int i = 0; i < this->location_list.size(); i++) {

		ofSetColor(this->color_list[i]);
		ofDrawSphere(this->location_list[i], 1.5);
	}

	this->cam.end();
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(1280, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}