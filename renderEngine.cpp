#include "renderEngine.h"

#include <vector>
#include <iostream>

#include "transform2D.h"
#include "objects.h"

using namespace std;
using namespace PvZ;


void RenderEngine::Init() {
    const auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = 0; // logic x
    logicSpace.y = 0; // logic y
    logicSpace.width = 16; // logic width
    logicSpace.height = 9; // logic height

    logicsEngine.InitGrid();

    Mesh *endZone = objects::CreateRectangle(END_ZONE_MESH, END_ZONE_WIDTH, END_ZONE_HEIGHT, RED, true);
    AddMeshToList(endZone);

    Mesh *square = objects::CreateRectangle(SQUARE_MESH, SQUARE_SIDE, SQUARE_SIDE, GREEN, true);
    AddMeshToList(square);

    Mesh *defender = objects::CreateDefender(DEFENDER_MESH, DEFENDER_WIDTH, DEFENDER_HEIGHT, BLUE);
    AddMeshToList(defender);

    Mesh *enemy = objects::CreateEnemy(ENEMY_MESH, ENEMY_OUTER_RADIUS, ENEMY_INNER_RADIUS, RED, BLUE);
    AddMeshToList(enemy);

    Mesh *star = objects::CreateStar(STAR_MESH, STAR_RADIUS, RED);
    AddMeshToList(star);
}

void RenderEngine::FrameStart() {
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}


void RenderEngine::Update(float deltaTimeSeconds) {
    const glm::ivec2 resolution = window->GetResolution();
    viewSpace = ViewportSpace(0, 0, resolution.x, resolution.y);
    SetViewportArea(viewSpace, glm::vec3(0.1f, 0.1f, 0.1f), true);

    visMatrix = glm::mat3(1);
    visMatrix *= transform2D::VisualizationTransf2DUnif(logicSpace, viewSpace);

    DrawScene(visMatrix);
}


void RenderEngine::FrameEnd() {}


void RenderEngine::OnInputUpdate(float deltaTime, int mods) {
    // Treat continuous update based on input
}


void RenderEngine::OnKeyPress(int key, int mods) {
    // Add key press event
}


void RenderEngine::OnKeyRelease(int key, int mods) {
    // Add key release event
}


void RenderEngine::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) {
    // Add mouse move event
}


void RenderEngine::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button press event
}


void RenderEngine::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button release event
}


void RenderEngine::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) {
    // Treat mouse scroll event
}


void RenderEngine::OnWindowResize(int width, int height) {
    // Treat window resize event
}

void RenderEngine::SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor, bool clear) {
    glViewport(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    glEnable(GL_SCISSOR_TEST);
    glScissor(viewSpace.x, viewSpace.y, viewSpace.width, viewSpace.height);

    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(colorColor.r, colorColor.g, colorColor.b, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glDisable(GL_SCISSOR_TEST);

    GetSceneCamera()->SetOrthographic((float)viewSpace.x, (float)(viewSpace.x + viewSpace.width),
                                      (float)viewSpace.y, (float)(viewSpace.y + viewSpace.height), 0.1f, 400);
    GetSceneCamera()->Update();
}

void RenderEngine::DrawScene(const glm::mat3 &visMatrix) {

    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(logicsEngine.grid[1][1].position.x,
                                          logicsEngine.grid[1][1].position.y);
    RenderMesh2D(meshes[STAR_MESH], shaders["VertexColor"], modelMatrix);
    
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(logicsEngine.grid[2][2].position.x,
                                          logicsEngine.grid[2][2].position.y);
    RenderMesh2D(meshes[ENEMY_MESH], shaders["VertexColor"], modelMatrix);
    
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(logicsEngine.grid[0][0].position.x,
                                          logicsEngine.grid[0][0].position.y);
    RenderMesh2D(meshes[DEFENDER_MESH], shaders["VertexColor"], modelMatrix);

    // draw squares
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(logicsEngine.grid[i][j].position.x,
                                                  logicsEngine.grid[i][j].position.y);
            RenderMesh2D(meshes[SQUARE_MESH], shaders["VertexColor"], modelMatrix);
        }

    // draw end-zone
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(PADDING + END_ZONE_WIDTH / 2, PADDING + END_ZONE_HEIGHT / 2);
    RenderMesh2D(meshes[END_ZONE_MESH], shaders["VertexColor"], modelMatrix);
}
