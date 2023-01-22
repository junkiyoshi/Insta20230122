#include "ofApp.h"

//--------------------------------------------------------------
void ofApp::setup() {

	ofSetFrameRate(30);
	ofSetWindowTitle("openframeworks");

	ofBackground(255);
	ofSetColor(0);
	ofFill();
	ofSetLineWidth(1.5);

	this->font.loadFont("fonts/Kazesawa-Bold.ttf", 90, true, true, true);
}

//--------------------------------------------------------------
void ofApp::update() {

}

//--------------------------------------------------------------
void ofApp::draw() {

	ofTranslate(ofGetWindowSize() * 0.5);

	string word = "From Code";
	for (int y = -240 + 40; y < ofGetHeight() - 480; y += 120) {

		auto path_list = font.getStringAsPoints(word, true, false);

		for (auto path : path_list) {

			auto outline = path.getOutline();

			ofBeginShape();
			for (int outline_index = 0; outline_index < outline.size(); outline_index++) {

				if (outline_index != 0) { ofNextContour(true); }

				outline[outline_index] = outline[outline_index].getResampledByCount(300);
				auto vertices = outline[outline_index].getVertices();
				for (int vertices_index = 0; vertices_index < vertices.size(); vertices_index++) {

					auto location = glm::vec3(vertices[vertices_index].x - this->font.stringWidth(word) * 0.5, y + vertices[vertices_index].y + this->font.stringHeight(word) * 0.5, 0);
					auto len = glm::length(location);
					auto noise_value = ofNoise(len * 0.01 - ofGetFrameNum() * 0.05);
					float deg = 0;
					if (noise_value < 0.35) {

						deg = ofMap(noise_value, 0, 0.35, -360, 0);
					}
					else if (noise_value > 0.65) {

						deg = ofMap(noise_value, 0.65, 1, 0, 360);
					}

					auto rotation = glm::rotate(glm::mat4(), deg * (float)DEG_TO_RAD, glm::vec3(0, 0, 1));
					location = glm::vec4(location, 0) * rotation;

					ofVertex(location);
				}
			}
			ofEndShape(true);
		}
	}
}

//--------------------------------------------------------------
int main() {

	ofSetupOpenGL(720, 720, OF_WINDOW);
	ofRunApp(new ofApp());
}