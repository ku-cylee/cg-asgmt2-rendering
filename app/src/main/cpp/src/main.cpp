#include "main.h"

void surfaceCreated(AAssetManager* aAssetManager) {
    // 1. Implement z-buffering

    // 4. Implement alpha blending

    Scene::setup(aAssetManager);
}

void surfaceChanged(int width, int height) {
    glViewport(0, 0, width, height);
    Scene::screen(width, height);
}

void drawFrame(float deltaTime) {
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    Scene::update(deltaTime);
}

