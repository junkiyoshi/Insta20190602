#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(60);
	ofSetWindowTitle("openframeworks");

	ofBackground(239);
	ofSetColor(39);
	ofSetLineWidth(3);
	ofEnableDepthTest();
}

//--------------------------------------------------------------
void ofApp::update() {

	ofSeedRandom(39);
}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWidth() * 0.5, ofGetHeight() * 0.5);

	auto radius_min = 120;
	auto radius_max = 320;
	vector<glm::vec2> random_locations;

	ofFill();
	for (int i = 0; i < 120; i++) {

		auto random_radius = ofRandom(radius_min + 10, radius_max - 10);
		auto random_deg = ofRandom(360) + ofGetFrameNum() * ofRandom(0.5, 1.5) * (ofRandom(1) < 0.5 ? 1 : -1);
		auto random_location = glm::vec2(random_radius * cos(random_deg * DEG_TO_RAD), random_radius * sin(random_deg * DEG_TO_RAD));
		random_locations.push_back(random_location);

		ofDrawCircle(random_location, 5);
	}

	for (auto& location : random_locations) {

		for (auto& other : random_locations) {

			if (location == other) { continue; }

			auto distance = glm::distance(location, other);
			if (distance < 40) {

				ofDrawLine(location, other);
			}
		}
	}

	vector<glm::vec2> vertices_min, vertices_max;
	for (int deg = 0; deg < 360; deg++) {

		vertices_min.push_back(glm::vec2(radius_min * cos(deg * DEG_TO_RAD), radius_min * sin(deg * DEG_TO_RAD)));
		vertices_max.push_back(glm::vec2(radius_max * cos(deg * DEG_TO_RAD), radius_max * sin(deg * DEG_TO_RAD)));
	}

	ofNoFill();
	ofBeginShape();
	ofVertices(vertices_min);
	ofEndShape(true);

	ofBeginShape();
	ofVertices(vertices_max);
	ofEndShape(true);
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}