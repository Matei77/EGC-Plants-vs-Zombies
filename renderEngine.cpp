#include "renderEngine.h"

#include <vector>
#include <iostream>
#include <iso646.h>

#include "transform2D.h"
#include "objects.h"
#include "animations.h"
#include "lab_m1/lab3/transform2D.h"

using namespace std;
using namespace PvZ;


void RenderEngine::Init() {
    const auto camera = GetSceneCamera();
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    logicSpace.x = LOGIC_SPACE_X;
    logicSpace.y = LOGIC_SPACE_Y;
    logicSpace.width = LOGIC_SPACE_WIDTH;
    logicSpace.height = LOGIC_SPACE_HEIGHT;

    logicsEngine.InitLogicsEngine();

    // map meshes
    Mesh *endZoneMesh = objects::CreateRectangle(END_ZONE_MESH, END_ZONE_WIDTH, END_ZONE_HEIGHT, RED, true);
    AddMeshToList(endZoneMesh);
    Mesh *squareMesh = objects::CreateRectangle(SQUARE_MESH, SQUARE_SIDE, SQUARE_SIDE, GREEN, true);
    AddMeshToList(squareMesh);
    Mesh *guiSquareMesh = objects::CreateRectangle(GUI_SQUARE_MESH, SQUARE_SIDE, SQUARE_SIDE, BLACK, false);
    AddMeshToList(guiSquareMesh);
    Mesh *guiLivesMesh = objects::CreateRectangle(GUI_LIVES_MESH, LIFE_SIDE, LIFE_SIDE, RED, true);
    AddMeshToList(guiLivesMesh);

    // defender meshes
    Mesh *orangeDefenderMesh = objects::CreateDefender(ORANGE_DEFENDER_MESH, DEFENDER_WIDTH, DEFENDER_HEIGHT, ORANGE);
    AddMeshToList(orangeDefenderMesh);
    Mesh *blueDefenderMesh = objects::CreateDefender(BLUE_DEFENDER_MESH, DEFENDER_WIDTH, DEFENDER_HEIGHT, BLUE);
    AddMeshToList(blueDefenderMesh);
    Mesh *yellowDefenderMesh = objects::CreateDefender(YELLOW_DEFENDER_MESH, DEFENDER_WIDTH, DEFENDER_HEIGHT, YELLOW);
    AddMeshToList(yellowDefenderMesh);
    Mesh *purpleDefenderMesh = objects::CreateDefender(PURPLE_DEFENDER_MESH, DEFENDER_WIDTH, DEFENDER_HEIGHT, PURPLE);
    AddMeshToList(purpleDefenderMesh);

    // enemy meshes
    Mesh *orangeEnemyMesh = objects::CreateEnemy(ORANGE_ENEMY_MESH, ENEMY_OUTER_RADIUS, ENEMY_INNER_RADIUS, ORANGE,
                                                 LIGHT_ORANGE);
    AddMeshToList(orangeEnemyMesh);
    Mesh *blueEnemyMesh = objects::CreateEnemy(BLUE_ENEMY_MESH, ENEMY_OUTER_RADIUS, ENEMY_INNER_RADIUS, BLUE,
                                               LIGHT_BLUE);
    AddMeshToList(blueEnemyMesh);
    Mesh *yellowEnemyMesh = objects::CreateEnemy(YELLOW_ENEMY_MESH, ENEMY_OUTER_RADIUS, ENEMY_INNER_RADIUS, YELLOW,
                                                 LIGHT_YELLOW);
    AddMeshToList(yellowEnemyMesh);
    Mesh *purpleEnemyMesh = objects::CreateEnemy(PURPLE_ENEMY_MESH, ENEMY_OUTER_RADIUS, ENEMY_INNER_RADIUS, PURPLE,
                                                 LIGTH_PURPLE);
    AddMeshToList(purpleEnemyMesh);

    // star meshes
    Mesh *orangeDtarMesh = objects::CreateStar(ORANGE_STAR_MESH, STAR_RADIUS, ORANGE);
    AddMeshToList(orangeDtarMesh);
    Mesh *blueStarMesh = objects::CreateStar(BLUE_STAR_MESH, STAR_RADIUS, BLUE);
    AddMeshToList(blueStarMesh);
    Mesh *yellowStarMesh = objects::CreateStar(YELLOW_STAR_MESH, STAR_RADIUS, YELLOW);
    AddMeshToList(yellowStarMesh);
    Mesh *purpleStarMesh = objects::CreateStar(PURPLE_STAR_MESH, STAR_RADIUS, PURPLE);
    AddMeshToList(purpleStarMesh);
    Mesh *pinkStarMesh = objects::CreateStar(PINK_STAR_MESH, STAR_RADIUS, PINK);
    AddMeshToList(pinkStarMesh);
    Mesh *grayStarMesh = objects::CreateStar(GRAY_STAR_MESH, GRAY_STAR_RADIUS, GRAY);
    AddMeshToList(grayStarMesh);
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
    logicsEngine.Update(deltaTimeSeconds);
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
    glm::vec3 viewMouse = glm::vec3(mouseX, viewSpace.height - mouseY, 1);
    glm::vec3 logicMouse = glm::inverse(visMatrix) * viewMouse;

    float logicMouseX = logicMouse[0];
    float logicMouseY = logicMouse[1];

    logicsEngine.SetDragDefenderPos({logicMouseX, logicMouseY});
}


void RenderEngine::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button press event
    glm::vec3 viewMouse = glm::vec3(mouseX, viewSpace.height - mouseY, 1);
    glm::vec3 logicMouse = glm::inverse(visMatrix) * viewMouse;

    float logicMouseX = logicMouse[0];
    float logicMouseY = logicMouse[1];

    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        // ---- click stars ----
        for (auto &star : logicsEngine.GetCreditStars()) {
            if ((logicMouseX - star.GetPosition().x) * (logicMouseX - star.GetPosition().x) +
                (logicMouseY - star.GetPosition().y) * (logicMouseY - star.GetPosition().y) <= STAR_RADIUS *
                STAR_RADIUS) {
                star.SetTimer(-1);
                logicsEngine.SetPlayerCredit(logicsEngine.GetPlayerCredit() + 1);
            }
        }

        // ---- select drag and drop defender ----
        // orange defender select
        float defenderPosX = PADDING + SQUARE_SIDE / 2;
        float defenderPosY = GUI_Y;
        logicsEngine.SetSelectedDefender(noType);

        if (logicsEngine.GetPlayerCredit() >= 1) {
            if (defenderPosX - SQUARE_SIDE / 2 < logicMouseX && logicMouseX < defenderPosX + SQUARE_SIDE / 2 &&
                defenderPosY - SQUARE_SIDE / 2 < logicMouseY && logicMouseY < defenderPosY + SQUARE_SIDE / 2) {
                logicsEngine.SetSelectedDefender(orangeType);
            }
        }

        // blue defender select
        defenderPosX += PADDING + SQUARE_SIDE;
        if (logicsEngine.GetPlayerCredit() >= 2) {
            if (defenderPosX - SQUARE_SIDE / 2 < logicMouseX && logicMouseX < defenderPosX + SQUARE_SIDE / 2 &&
                defenderPosY - SQUARE_SIDE / 2 < logicMouseY && logicMouseY < defenderPosY + SQUARE_SIDE / 2) {
                logicsEngine.SetSelectedDefender(blueType);
            }
        }

        // yellow defender select
        defenderPosX += PADDING + SQUARE_SIDE;
        if (logicsEngine.GetPlayerCredit() >= 2) {
            if (defenderPosX - SQUARE_SIDE / 2 < logicMouseX && logicMouseX < defenderPosX + SQUARE_SIDE / 2 &&
                defenderPosY - SQUARE_SIDE / 2 < logicMouseY && logicMouseY < defenderPosY + SQUARE_SIDE / 2) {
                logicsEngine.SetSelectedDefender(yellowType);
            }
        }

        // purple defender select
        defenderPosX += PADDING + SQUARE_SIDE;
        if (logicsEngine.GetPlayerCredit() >= 3) {
            if (defenderPosX - SQUARE_SIDE / 2 < logicMouseX && logicMouseX < defenderPosX + SQUARE_SIDE / 2 &&
                defenderPosY - SQUARE_SIDE / 2 < logicMouseY && logicMouseY < defenderPosY + SQUARE_SIDE / 2) {
                logicsEngine.SetSelectedDefender(purpleType);
            }
        }
    }

    if (button == GLFW_MOUSE_BUTTON_MIDDLE) {
        // ---- delete defender with right click ----
        for (auto &defender : logicsEngine.GetDefenders()) {
            float defX = defender.GetPosition().x;
            float defY = defender.GetPosition().y;
            
            if (defX - SQUARE_SIDE / 2 < logicMouseX && logicMouseX < defX + SQUARE_SIDE / 2 &&
                defY - SQUARE_SIDE / 2 < logicMouseY && logicMouseY < defY + SQUARE_SIDE / 2) {
                defender.SetAlive(false);
                logicsEngine.GetGridSquare(logicToGridIndexX(defX), logicToGridIndexY(defY)).occupied = false;
            }
        }
    }
}


void RenderEngine::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) {
    // Add mouse button release event
    glm::vec3 viewMouse = glm::vec3(mouseX, viewSpace.height - mouseY, 1);
    glm::vec3 logicMouse = glm::inverse(visMatrix) * viewMouse;

    float logicMouseX = logicMouse[0];
    float logicMouseY = logicMouse[1];

    if (button == GLFW_MOUSE_BUTTON_RIGHT) {
        for (int i = 0; i < GRID_SIDE; i++) {
            for (int j = 0; j < GRID_SIDE; j++) {
                float squarePosX = logicsEngine.GetGridSquare(i, j).position.x;
                float squarePosY = logicsEngine.GetGridSquare(i, j).position.y;

                if (squarePosX - SQUARE_SIDE / 2 < logicMouseX && logicMouseX < squarePosX + SQUARE_SIDE / 2 &&
                    squarePosY - SQUARE_SIDE / 2 < logicMouseY && logicMouseY < squarePosY + SQUARE_SIDE / 2 &&
                    logicsEngine.GetGridSquare(i, j).occupied == false && logicsEngine.GetSelectedDefender() !=
                    noType) {
                    logicsEngine.SpawnDefender({squarePosX, squarePosY}, logicsEngine.GetSelectedDefender());

                    // charge the player the appropriate number of stars for placing a defender
                    logicsEngine.SetPlayerCredit(
                        logicsEngine.GetPlayerCredit() - logicsEngine.GetPrices().
                                                                      at(logicsEngine.GetSelectedDefender()));
                    logicsEngine.GetGridSquare(i, j).occupied = true;
                }
            }
        }
    }

    logicsEngine.SetSelectedDefender(noType);
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
    DrawGUI(visMatrix);
    DrawCreditStars(visMatrix);
    DrawEnemies(visMatrix);
    DrawDefenders(visMatrix);
    DrawMap(visMatrix);
}

void RenderEngine::DrawMap(const glm::mat3 &visMatrix) {
    // draw squares
    for (int i = 0; i < 3; i++)
        for (int j = 0; j < 3; j++) {
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(logicsEngine.GetGridSquare(i, j).position.x,
                                                  logicsEngine.GetGridSquare(i, j).position.y);
            RenderMesh2D(meshes[SQUARE_MESH], shaders["VertexColor"], modelMatrix);
        }

    // draw end-zone
    modelMatrix = visMatrix;
    modelMatrix *= transform2D::Translate(PADDING + END_ZONE_WIDTH / 2, PADDING + END_ZONE_HEIGHT / 2);
    RenderMesh2D(meshes[END_ZONE_MESH], shaders["VertexColor"], modelMatrix);
}

void RenderEngine::DrawEnemies(const glm::mat3 &visMatrix) {
    for (const auto &enemy : logicsEngine.GetEnemies()) {
        modelMatrix = visMatrix;
        modelMatrix *= animations::MoveEnemy(enemy.GetPosition().x, enemy.GetPosition().y);
        modelMatrix *= animations::DestroyObject(enemy.GetScale());

        RenderMesh2D(meshes[enemy.GetMeshType()], shaders["VertexColor"], modelMatrix);
    }
}

void RenderEngine::DrawDefenders(const glm::mat3 &visMatrix) {
    for (const auto &defender : logicsEngine.GetDefenders()) {
        modelMatrix = visMatrix;
        modelMatrix *= animations::MoveEnemy(defender.GetPosition().x, defender.GetPosition().y);
        modelMatrix *= animations::DestroyObject(defender.GetScale());
        RenderMesh2D(meshes[defender.GetMeshType()], shaders["VertexColor"], modelMatrix);
    }
}

void RenderEngine::DrawCreditStars(const glm::mat3 &visMatrix) {
    for (const auto &star : logicsEngine.GetCreditStars()) {
        if (star.IsVisible()) {
            modelMatrix = visMatrix;
            modelMatrix *= animations::MoveEnemy(star.GetPosition().x, star.GetPosition().y);
            RenderMesh2D(meshes[PINK_STAR_MESH], shaders["VertexColor"], modelMatrix);
        }
    }
}

void RenderEngine::DrawGUI(const glm::mat3 &visMatrix) {
    // draw defender types squares with prices
    for (int i = 0; i < 4; i++) {
        float priceX = PADDING * (i + 1) + SQUARE_SIDE * i + GRAY_STAR_RADIUS;
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(PADDING * (i + 1) + SQUARE_SIDE * i + SQUARE_SIDE / 2, GUI_Y);
        // draw square
        RenderMesh2D(meshes[GUI_SQUARE_MESH], shaders["VertexColor"], modelMatrix);
        switch (i) {
        case 0:
            // draw defender
            RenderMesh2D(meshes[ORANGE_DEFENDER_MESH], shaders["VertexColor"], modelMatrix);

        // draw price
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(priceX, PRICE_Y);
            RenderMesh2D(meshes[GRAY_STAR_MESH], shaders["VertexColor"], modelMatrix);
            break;
        case 1:
            // draw defender
            RenderMesh2D(meshes[BLUE_DEFENDER_MESH], shaders["VertexColor"], modelMatrix);

        // draw price
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(priceX, PRICE_Y);
            RenderMesh2D(meshes[GRAY_STAR_MESH], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Translate(GRAY_STAR_RADIUS * 2, 0);
            RenderMesh2D(meshes[GRAY_STAR_MESH], shaders["VertexColor"], modelMatrix);
            break;
        case 2:
            // draw defender
            RenderMesh2D(meshes[YELLOW_DEFENDER_MESH], shaders["VertexColor"], modelMatrix);

        // draw price
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(priceX, PRICE_Y);
            RenderMesh2D(meshes[GRAY_STAR_MESH], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Translate(GRAY_STAR_RADIUS * 2, 0);
            RenderMesh2D(meshes[GRAY_STAR_MESH], shaders["VertexColor"], modelMatrix);
            break;
        case 3:
            // draw defender
            RenderMesh2D(meshes[PURPLE_DEFENDER_MESH], shaders["VertexColor"], modelMatrix);

        // draw price
            modelMatrix = visMatrix;
            modelMatrix *= transform2D::Translate(priceX, PRICE_Y);
            RenderMesh2D(meshes[GRAY_STAR_MESH], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Translate(GRAY_STAR_RADIUS * 2, 0);
            RenderMesh2D(meshes[GRAY_STAR_MESH], shaders["VertexColor"], modelMatrix);
            modelMatrix *= transform2D::Translate(GRAY_STAR_RADIUS * 2, 0);
            RenderMesh2D(meshes[GRAY_STAR_MESH], shaders["VertexColor"], modelMatrix);
            break;
        default: ;
        }
    }

    // draw lives
    for (int i = logicsEngine.GetPlayerLives() - 1; i >= 0; i--) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(
            LOGIC_SPACE_WIDTH - PADDING - PADDING * (i + 1) - LIFE_SIDE * i - LIFE_SIDE / 2, GUI_Y);
        RenderMesh2D(meshes[GUI_LIVES_MESH], shaders["VertexColor"], modelMatrix);
    }

    // draw credit stars
    for (int i = 0; i < logicsEngine.GetPlayerCredit(); i++) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(CREDIT_STAR_START_X + GRAY_STAR_RADIUS + (GRAY_STAR_RADIUS * 2) * (i % 9),
                                              CREDIT_STAR_START_Y - (GRAY_STAR_RADIUS * 2) * (i / 9));
        RenderMesh2D(meshes[GRAY_STAR_MESH], shaders["VertexColor"], modelMatrix);
    }

    // draw defender drag and drop
    if (logicsEngine.GetSelectedDefender() != noType) {
        modelMatrix = visMatrix;
        modelMatrix *= transform2D::Translate(logicsEngine.GetDragDefenderPos().x, logicsEngine.GetDragDefenderPos().y);
        modelMatrix *= transform2D::Scale(DRAG_AND_DROP_SCALE, DRAG_AND_DROP_SCALE);
        switch (logicsEngine.GetSelectedDefender()) {
        case orangeType:
            RenderMesh2D(meshes[ORANGE_DEFENDER_MESH], shaders["VertexColor"], modelMatrix);
            break;
        case blueType:
            RenderMesh2D(meshes[BLUE_DEFENDER_MESH], shaders["VertexColor"], modelMatrix);
            break;
        case yellowType:
            RenderMesh2D(meshes[YELLOW_DEFENDER_MESH], shaders["VertexColor"], modelMatrix);
            break;
        case purpleType:
            RenderMesh2D(meshes[PURPLE_DEFENDER_MESH], shaders["VertexColor"], modelMatrix);
            break;
        }
    }
}
