#pragma once

#include "components/simple_scene.h"
#include <lab_m1/Tema1/Enemies.h>
#include <lab_m1/Tema1/Bullet.h>
#include <lab_m1/Tema1/HealthKit.h>


#define MOVE_RATIO			(.25f)
#define BULLETSPEED         (300)
#define FIRERATE            (5.f)



namespace m1
{
    class Tema1 : public gfxc::SimpleScene
    {
    public:
        Tema1();
        ~Tema1();

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
        void SpawnEnemy(glm::ivec2 resolution, float deltaTimeSeconds);
        void MoveEnemies(glm::ivec2 resoultion);
        void FireBullet(float deltaTimeSeconds);
        bool CheckEnemyPlayerCollision(Enemies enemy, glm::ivec2 resolution);
        int CheckEnemyBulletCollision(std::vector<Enemies> enemies, glm::ivec2 resolution, float bulletPosX, float bulletPosY);
        void SpawnHealthKit(glm::ivec2 resolution);
        bool Tema1::CheckHealthPlayerCollision(glm::ivec2 resolution);


    protected:
        glm::mat3 modelMatrix;
        float translateX, translateY;
        float scaleX, scaleY;
        float angularStep;

        // TODO(student): If you need any other class variables, define them here.
        std::vector<float> leftCornersRectangleX, leftCornersRectangleY, leftCornersSquareX, leftCornersSquareY;
        glm::mat3 modelMatrixPlayArea, modelMatrixHealth, modelMatrixHealthKit;
        std::vector<glm::mat3> modelMatrixEnemies, modelMatrixBullet;
        std::vector<Enemies> enemies;
        std::vector<Bullet> bullets;
        HealthKit healthKit;
        int numberOfEnemies, bulletsOnScreen, health, score;
        float direction;
        float headPosX, headPosY;
        float leftHandPosX, leftHandPosY;
        float rightHandPosX, rightHandPosY;
        float angularStepBullet;
        float setTimerEnemy, setTimerBullet, setTimerHealthKit;


    };
}   // namespace m1
