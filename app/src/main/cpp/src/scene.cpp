#include "scene.h"
#include "binary/teapot.h"
#include "binary/rgb.h"
#include "binary/cloud.h"
#include "binary/tex_flower.h"
#include "checker.h"

Shader* Scene::vertexShader = nullptr;
Shader* Scene::fragmentShader = nullptr;
Program* Scene::program = nullptr;
Camera* Scene::camera = nullptr;
Object* Scene::teapot = nullptr;
Texture* Scene::diffuse = nullptr;
Texture* Scene::dissolve = nullptr;
Material* Scene::material = nullptr;
Light* Scene::light = nullptr;

void Scene::setup(AAssetManager* aAssetManager) {
    Asset::setManager(aAssetManager);

    Scene::vertexShader = new Shader(GL_VERTEX_SHADER, "vertex.glsl");
    Scene::fragmentShader = new Shader(GL_FRAGMENT_SHADER, "fragment.glsl");

    Scene::program = new Program(Scene::vertexShader, Scene::fragmentShader);

    Scene::camera = new Camera(Scene::program);
    Scene::camera->eye = vec3(20.0f, 30.0f, 20.0f);

    Scene::light = new Light(program);
    Scene::light->direction = vec3(0.0f, 0.6f, 1.0f);

    // 3. Change the texture to RGB texture
    Scene::diffuse  = new Texture(Scene::program, 0, "textureDiff", rgbTexels, rgbSize);
    Scene::material = new Material(Scene::program, diffuse);
    Scene::teapot = new Object(program, material, teapotVertices, teapotIndices);
}

void Scene::screen(int width, int height) {
    Scene::camera->aspect = (float) width/height;
}

void Scene::update(float deltaTime) {
    static float time = 0.0f;

    Scene::program->use();

    // 2. Implement Phong lighting
    Scene::light->direction = mat3(cos(deltaTime), 0.0f, sin(deltaTime),
                                   0.0f, 1.0f, 0.0f,
                                   -sin(deltaTime), 0, cos(deltaTime)) * Scene::light->direction;

    // 4. Implement alpha blending
    // Compute current alpha blending state and ssign it to uniform variable
    GLint blendStateLocation = glGetUniformLocation(program->get(), "blendState");
    glUniform1i(blendStateLocation, (int(time) % 6) / 2);
    time += deltaTime;

    Scene::camera->update();
    Scene::light->update();

    Scene::teapot->draw();
}