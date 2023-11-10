#pragma once

#include "logicsEngine.h"
#include "utils.h"
#include "components/simple_scene.h"

namespace PvZ {
    class RenderEngine final : public gfxc::SimpleScene {
    public:
        RenderEngine() {
            modelMatrix = glm::mat3(1);
            visMatrix = glm::mat3(1);
        }
        
        void Init() override;

    private:
        void FrameStart() override;
        void Update(float deltaTimeSeconds) override;
        void FrameEnd() override;

        void OnInputUpdate(float deltaTime, int mods) override;
        void OnKeyPress(int key, int mods) override;
        void OnKeyRelease(int key, int mods) override;
        void OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY) override;
        void OnMouseBtnPress(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods) override;
        void OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY) override;
        void OnWindowResize(int width, int height) override;

        void SetViewportArea(const ViewportSpace &viewSpace, glm::vec3 colorColor = glm::vec3(0), bool clear = true);
        void DrawScene(const glm::mat3 &visMatrix);
        void DrawMap(const glm::mat3 &visMatrix);
        void DrawEnemies(const glm::mat3 &visMatrix);
        void DrawDefenders(const glm::mat3 &visMatrix);
        void DrawCreditStars(const glm::mat3 &visMatrix);
        void DrawGUI(const glm::mat3 &visMatrix);

    protected:
        glm::mat3 modelMatrix, visMatrix;
        LogicSpace logicSpace;
        ViewportSpace viewSpace;
        LogicsEngine logicsEngine;
    };
} // namespace PvZ
