#include "lab_m1/Tema1/Tema1.h"

#include <vector>
#include <iostream>

#include "lab_m1/Tema1/transform2D.h"
#include "lab_m1/Tema1/object2DTema1.h"
#include "lab_m1/Tema1/functions.h"


using namespace std;
using namespace m1;


/*
 *  To find out more about `FrameStart`, `Update`, `FrameEnd`
 *  and the order in which they are called, see `world.cpp`.
 */


Tema1::~Tema1()
{
}


void Tema1::Init()
{
    glm::ivec2 resolution = window->GetResolution();
    auto camera = GetSceneCamera();
    camera->SetOrthographic(0, (float)resolution.x, 0, (float)resolution.y, 0.01f, 400);
    camera->SetPosition(glm::vec3(0, 0, 50));
    camera->SetRotation(glm::vec3(0, 0, 0));
    camera->Update();
    GetCameraInput()->SetActive(false);

    glm::vec3 corner = glm::vec3(0, 0, 0);

    // TODO(student): Compute coordinates of a square's center, and store
    // then in the `cx` and `cy` class variables (see the header). Use
    // `corner` and `squareSide`. These two class variables will be used
    // in the `Update()` function. Think about it, why do you need them?

    // Initialize tx and ty (the translation steps)
    translateX = 0;
    translateY = 0;

    // Initialize sx and sy (the scale factors)
    scaleX = 1;
    scaleY = 1;
    
    // Initialize angularStep
    angularStep = 0;

    headPosX = resolution.x / 2;
    headPosY = resolution.y / 2;

    setTimerEnemy = glfwGetTime();
    setTimerBullet = glfwGetTime();
    setTimerHealthKit = glfwGetTime();

    numberOfEnemies = 5;
    bulletsOnScreen = 0;
    health = 3;
    score = 0;
    for (int i = 0; i < numberOfEnemies; i++)
    {
        modelMatrixEnemies.push_back(glm::mat3(1));
        Enemies enemy = Enemies::Enemies(-1.f, -1.f, 0.f, 0.f, 0.f, 0.f);
        enemies.push_back(enemy);
    }

    //Play area mesh
    Mesh* playArea = object2DTema1::CreateRectangle("playArea", glm::vec3(0, 0, 0), resolution.x + 300, resolution.y + 300, glm::vec3(1, 1, 1), true);
    AddMeshToList(playArea);
   

    //Player meshes
    Mesh* playerHead = object2DTema1::CreateCircle("playerHead", 15.f, glm::vec3(0, 1, 0), glm::vec3(0, 1, 0));
    AddMeshToList(playerHead);

    Mesh* playerHeadOutline = object2DTema1::CreateCircle("playerHeadOutline", 20.f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
    AddMeshToList(playerHeadOutline);

    Mesh* playerHand = object2DTema1::CreateCircle("playerHand", 5.f, glm::vec3(1, 1, 0), glm::vec3(1, 1, 0));
    AddMeshToList(playerHand);

    Mesh* playerHandOutline = object2DTema1::CreateCircle("playerHandOutline", 8.f, glm::vec3(0, 0, 0), glm::vec3(0, 0, 0));
    AddMeshToList(playerHandOutline);


    //Enemy meshes
    Mesh* enemyHead = object2DTema1::CreateSquare("enemyHead", glm::vec3(0, 0, 0), 50.f, glm::vec3(1, 0, 0), true);
    AddMeshToList(enemyHead);

    Mesh* enemyHeadOutline = object2DTema1::CreateSquare("enemyHeadOutline", glm::vec3(0, 0, 0), 60.f, glm::vec3(0, 0, 0), true);
    AddMeshToList(enemyHeadOutline);

    Mesh* enemyHand = object2DTema1::CreateSquare("enemyHand", glm::vec3(0, 0, 0), 20.f, glm::vec3(1, 0, 0), true);
    AddMeshToList(enemyHand);

    Mesh* enemyHandOutline = object2DTema1::CreateSquare("enemyHandOutline", glm::vec3(0, 0, 0), 30.f, glm::vec3(0, 0, 0), true);
    AddMeshToList(enemyHandOutline);


    //Projectile mesh
    Mesh* projectile = object2DTema1::CreateSquare("projectile", glm::vec3(0, 0, 0), 10.f, glm::vec3(0, 0, 1), true);
    AddMeshToList(projectile);


    //Obstacle meshes
    Mesh* obstacleSquare = object2DTema1::CreateSquare("obstacleSquare", glm::vec3(0, 0, 0), 200.f, glm::vec3(0, 1, 0), true);
    AddMeshToList(obstacleSquare);

    Mesh* obstacleRectangle = object2DTema1::CreateRectangle("obstacleRectangle", glm::vec3(0, 0, 0), 200.f, 100.f, glm::vec3(0, 1, 0), true);
    AddMeshToList(obstacleRectangle);

    //UI section
    Mesh* healthCage = object2DTema1::CreateRectangle("healthCage", glm::vec3(0, 0, 0), 200.f, 50.f, glm::vec3(0, 0, 1), false);
    AddMeshToList(healthCage);

    Mesh* healthBar = object2DTema1::CreateSquare("healthBar", glm::vec3(0, 0, 0), 50.f, glm::vec3(0, 0, 1), true);
    AddMeshToList(healthBar);

    Mesh* healthKit = object2DTema1::CreateSquare("healthKit", glm::vec3(0, 0, 0), 20.f, glm::vec3(1, 0, 1), true);
    AddMeshToList(healthKit);

    cout << "SCORE = " << score << endl;
}


void Tema1::FrameStart()
{
    // Clears the color buffer (using the previously set color) and depth buffer
    glClearColor(0, 0, 0, 1);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    glm::ivec2 resolution = window->GetResolution();
    // Sets the screen area where to draw
    glViewport(0, 0, resolution.x, resolution.y);
}


void Tema1::Update(float deltaTimeSeconds)
{
    {
        modelMatrix = glm::mat3(1);
        modelMatrixPlayArea = glm::mat3(1);
        modelMatrixHealth = glm::mat3(1);
        modelMatrixHealthKit = glm::mat3(1);
        if (health >= 0)
        {
            //Rendering Player
            glm::ivec2 resolution = window->GetResolution();
            modelMatrix = transform2D::Translate(headPosX, headPosY); //starting coordonates of the player head
            modelMatrix *= transform2D::Rotate(direction);
            RenderMesh2D(meshes["playerHead"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["playerHeadOutline"], shaders["VertexColor"], modelMatrix);

            modelMatrix *= transform2D::Translate(20, -15); //starting coorodnates of the player right hand
            RenderMesh2D(meshes["playerHand"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["playerHandOutline"], shaders["VertexColor"], modelMatrix);

            modelMatrix *= transform2D::Translate(0, 30); // starting coordonatess of the player left hand
            RenderMesh2D(meshes["playerHand"], shaders["VertexColor"], modelMatrix);
            RenderMesh2D(meshes["playerHandOutline"], shaders["VertexColor"], modelMatrix);

            FireBullet(deltaTimeSeconds);
            MoveEnemies(resolution);
            SpawnEnemy(resolution, deltaTimeSeconds);

            modelMatrixHealth = transform2D::Translate(1000, 600);
            RenderMesh2D(meshes["healthCage"], shaders["VertexColor"], modelMatrixHealth);
            for (int i = 0; i <= health; i++)
            {
                RenderMesh2D(meshes["healthBar"], shaders["VertexColor"], modelMatrixHealth);
                modelMatrixHealth *= transform2D::Translate(50, 0);
            }

            if (health < 3)
            {
                SpawnHealthKit(resolution);
                if (healthKit.getSpawnX() != -1 && healthKit.getSpawnY() != -1) 
                {
                    modelMatrixHealthKit = transform2D::Translate(healthKit.getSpawnX() + translateX, healthKit.getSpawnY() + translateY);
                    RenderMesh2D(meshes["healthKit"], shaders["VertexColor"], modelMatrixHealthKit);
                    if (CheckHealthPlayerCollision(resolution))
                    {
                        health++;
                        healthKit.setSpawnX(-1);
                        healthKit.setSpawnY(-1);
                    }
                }
            }

            //Rendering obstacles
            modelMatrixPlayArea = transform2D::Translate(translateX + 150, translateY + 200);
            RenderMesh2D(meshes["obstacleSquare"], shaders["VertexColor"], modelMatrixPlayArea);
            leftCornersSquareX.push_back(150.f);
            leftCornersSquareY.push_back(200.f);


            modelMatrixPlayArea = transform2D::Translate(translateX + 1300, translateY + 200);
            RenderMesh2D(meshes["obstacleSquare"], shaders["VertexColor"], modelMatrixPlayArea);
            leftCornersSquareX.push_back(1300.f);
            leftCornersSquareY.push_back(200.f);

            modelMatrixPlayArea = transform2D::Translate(translateX + 1300, translateY + 790);
            RenderMesh2D(meshes["obstacleSquare"], shaders["VertexColor"], modelMatrixPlayArea);
            leftCornersSquareX.push_back(1300.f);
            leftCornersSquareY.push_back(790.f);

            modelMatrixPlayArea = transform2D::Translate(translateX + 800, translateY + 300);
            RenderMesh2D(meshes["obstacleRectangle"], shaders["VertexColor"], modelMatrixPlayArea);
            leftCornersRectangleX.push_back(800.f);
            leftCornersRectangleY.push_back(300.f);

            modelMatrixPlayArea = transform2D::Translate(translateX + 1100, translateY + 500);
            RenderMesh2D(meshes["obstacleRectangle"], shaders["VertexColor"], modelMatrixPlayArea);
            leftCornersRectangleX.push_back(1100.f);
            leftCornersRectangleY.push_back(500.f);

            modelMatrixPlayArea = transform2D::Translate(translateX + 200, translateY + 900);
            RenderMesh2D(meshes["obstacleRectangle"], shaders["VertexColor"], modelMatrixPlayArea);
            leftCornersRectangleX.push_back(200.f);
            leftCornersRectangleY.push_back(900.f);

            

            //Rendering play area
            modelMatrixPlayArea = transform2D::Translate(translateX, translateY);
            RenderMesh2D(meshes["playArea"], shaders["VertexColor"], modelMatrixPlayArea);
        }
    }

}


void Tema1::FrameEnd()
{
}


/*
 *  These are callback functions. To find more about callbacks and
 *  how they behave, see `input_controller.h`.
 */


void Tema1::OnInputUpdate(float deltaTime, int mods)
{
    glm::ivec2 resolution = window->GetResolution();

    if (window->KeyHold(GLFW_KEY_D))
    {
        if ((resolution.x + 300 + translateX > resolution.x / 2 + 20.f) 
            && !functions::CheckRectangleCollisionLeft(leftCornersRectangleX, leftCornersRectangleY, translateX, translateY,
                resolution, 200.f, 100.f)
            && !functions::CheckRectangleCollisionLeft(leftCornersSquareX, leftCornersSquareY, translateX, translateY,
                resolution, 200.f, 200.f))
        {
            translateX -= MOVE_RATIO * deltaTime * resolution.x;
            for (int i = 0; i < bulletsOnScreen; i++)
            {
                bullets[i].setTranslateX(bullets[i].getTranslateX() - MOVE_RATIO * deltaTime * resolution.x);
            }
            for (int i = 0; i < numberOfEnemies; i++)
            {
                enemies[i].setTranslateX(enemies[i].getTranslateX() - MOVE_RATIO * deltaTime * resolution.x);
            }
        }
    }
    if (window->KeyHold(GLFW_KEY_A))
    {
        if (translateX < resolution.x /2 - 20.f //play area incepe din 0,0,0
            && !functions::CheckRectangleCollisionRight(leftCornersRectangleX, leftCornersRectangleY, translateX, translateY,
                resolution, 200.f, 100.f)
            && !functions::CheckRectangleCollisionRight(leftCornersSquareX, leftCornersSquareY, translateX, translateY,
                resolution, 200.f, 200.f))
        {
            translateX += MOVE_RATIO * deltaTime * resolution.x;
            for (int i = 0; i < bulletsOnScreen; i++)
            {
                bullets[i].setTranslateX(bullets[i].getTranslateX() + MOVE_RATIO * deltaTime * resolution.x);
            }
            for (int i = 0; i < numberOfEnemies; i++)
            {
                enemies[i].setTranslateX(enemies[i].getTranslateX() + MOVE_RATIO * deltaTime * resolution.x);
            }
        }
    }
    if (window->KeyHold(GLFW_KEY_W))
    {
        if (resolution.y + translateY + 300 > resolution.y/2 + 20.f
            && !functions::CheckRectangleCollisionDown(leftCornersRectangleX, leftCornersRectangleY, translateX, translateY,
                resolution, 200.f, 100.f)
            && !functions::CheckRectangleCollisionDown(leftCornersSquareX, leftCornersSquareY, translateX, translateY,
                resolution, 200.f, 200.f))
        {
            translateY -= MOVE_RATIO * deltaTime * resolution.y;
            for (int i = 0; i < bulletsOnScreen; i++)
            {
                bullets[i].setTranslateY(bullets[i].getTranslateY() - MOVE_RATIO * deltaTime * resolution.y);
            }
            for (int i = 0; i < numberOfEnemies; i++)
            {
                enemies[i].setTranslateY(enemies[i].getTranslateY() - MOVE_RATIO * deltaTime * resolution.y);
            }
        }
    }
    if (window->KeyHold(GLFW_KEY_S))
    {
        if (translateY < resolution.y/2 - 20.f
            && !functions::CheckRectangleCollisionUp(leftCornersRectangleX, leftCornersRectangleY, translateX, translateY,
                resolution, 200.f, 100.f)
            && !functions::CheckRectangleCollisionUp(leftCornersSquareX, leftCornersSquareY, translateX, translateY,
                resolution, 200.f, 200.f))
        {
            translateY += MOVE_RATIO * deltaTime * resolution.y;
            for (int i = 0; i < bulletsOnScreen; i++)
            {
                bullets[i].setTranslateY(bullets[i].getTranslateY() + MOVE_RATIO * deltaTime * resolution.y);
            }
            for (int i = 0; i < numberOfEnemies; i++)
            {
                enemies[i].setTranslateY(enemies[i].getTranslateY() + MOVE_RATIO * deltaTime * resolution.y);
            }
        }
    }
   
}


void Tema1::OnKeyPress(int key, int mods)
{
    // Add key press event
   
}


void Tema1::OnKeyRelease(int key, int mods)
{
    // Add key release event
}


void Tema1::OnMouseMove(int mouseX, int mouseY, int deltaX, int deltaY)
{
    // Add mouse move event
    glm::ivec2 pos;
    glm::ivec2 resolution = window->GetResolution();
    //getting cursor position
    pos = window->GetCursorPosition();
    float coordinateX = pos.x - resolution.x / 2; //head is always in the center
    float coordinateY = resolution.y - pos.y - resolution.y / 2; //head is always in the center
    direction = atan2(coordinateY, coordinateX);
   // cout << "Cursor Position at (" << pos.x << " : " << pos.y << endl;
   // cout << "Translation (" << translateX << " : " << translateY << endl;

}


void Tema1::OnMouseBtnPress(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button press event
    if (button == GLFW_MOUSE_BUTTON_2)
    {
        if (glfwGetTime() - setTimerBullet > 0.5f) {
            glm::ivec2 pos;
            glm::ivec2 resolution;
            setTimerBullet = glfwGetTime();
            resolution = window->GetResolution();
            pos = window->GetCursorPosition();
            float dirBulletX = pos.x - headPosX - 5;
            float dirBulletY = resolution.y - pos.y - headPosY;
            float hyp = sqrt(dirBulletX * dirBulletX + dirBulletY * dirBulletY);
            dirBulletX /= hyp;
            dirBulletY /= hyp;

            modelMatrixBullet.push_back(glm::mat3(1));
            Bullet bullet = Bullet::Bullet(headPosX + 5, headPosY);
            bullets.push_back(bullet);
            bullets[bulletsOnScreen].setTranslateX(headPosX + 5);
            bullets[bulletsOnScreen].setTranslateY(headPosY);
            bullets[bulletsOnScreen].setDirection(direction);
            bullets[bulletsOnScreen].setDirectonX(dirBulletX);
            bullets[bulletsOnScreen].setDirectionY(dirBulletY);
            bulletsOnScreen++;
        }

    }
}


void Tema1::OnMouseBtnRelease(int mouseX, int mouseY, int button, int mods)
{
    // Add mouse button release event
}


void Tema1::OnMouseScroll(int mouseX, int mouseY, int offsetX, int offsetY)
{
}


void Tema1::OnWindowResize(int width, int height)
{
}

int Tema1::CheckEnemyBulletCollision(std::vector<Enemies> enemies, glm::ivec2 resolution, float bulletPosX, float bulletPosY)
{
    for (int i = 0; i < enemies.size(); i++)
    {
        if (enemies[i].getSpawnX() != -1 && enemies[i].getSpawnY() != -1)
        {
            float rectXL = enemies[i].getSpawnX() + enemies[i].getTranslateX();
            float rectXR = enemies[i].getSpawnX() + enemies[i].getTranslateX() + 60;
            float rectYU = enemies[i].getSpawnY() + enemies[i].getTranslateY() + 60;
            float rectYD = enemies[i].getSpawnY() + enemies[i].getTranslateY();
            if ((rectXL < (bulletPosX + 10.f))
                && (rectXR > (bulletPosX - 10.f))
                && (rectYD < (bulletPosY + 10.f))
                && (rectYU > (bulletPosY - 10.f)))
            {
                return i;
            }
            else {
                rectXL = enemies[i].getSpawnX() + enemies[i].getTranslateX() - 60;
                rectXR = enemies[i].getSpawnX() + enemies[i].getTranslateX();
                rectYU = enemies[i].getSpawnY() + enemies[i].getTranslateY();
                rectYD = enemies[i].getSpawnY() + enemies[i].getTranslateY() - 60;
                if ((rectXL < (bulletPosX + 10.f))
                    && (rectXR > (bulletPosX - 10.f))
                    && (rectYD < (bulletPosY + 10.f))
                    && (rectYU > (bulletPosY - 10.f)))
                {
                    return i;
                }
            }
        }
    }
    return -1;
}

bool Tema1::CheckEnemyPlayerCollision(Enemies enemy, glm::ivec2 resolution)
{
    float rectXL = enemy.getSpawnX() + enemy.getTranslateX();
    float rectXR = enemy.getSpawnX() + enemy.getTranslateX() + 60;
    float rectYU = enemy.getSpawnY() + enemy.getTranslateY() + 60;
    float rectYD = enemy.getSpawnY() + enemy.getTranslateY();
    if ((rectXL < (resolution.x / 2 + 20.f))
        && (rectXR > (resolution.x / 2 - 20.f))
        && (rectYD < (resolution.y / 2 + 20.f))
        && (rectYU > (resolution.y / 2 - 20.f)))
    {
        return true;
    }
    rectXL = enemy.getSpawnX() + enemy.getTranslateX() - 60;
    rectXR = enemy.getSpawnX() + enemy.getTranslateX();
    rectYU = enemy.getSpawnY() + enemy.getTranslateY();
    rectYD = enemy.getSpawnY() + enemy.getTranslateY() - 60;
    if ((rectXL < (resolution.x / 2 + 20.f))
        && (rectXR > (resolution.x / 2 - 20.f))
        && (rectYD < (resolution.y / 2 + 20.f))
        && (rectYU > (resolution.y / 2 - 20.f)))
    {
        return true;
    }
    return false;
}

void Tema1::SpawnEnemy(glm::ivec2 resolution, float deltaTimeSeconds)
{
    for (int i = 0; i < numberOfEnemies; i++)
    {
        if ((enemies[i].getSpawnX() == -1.f || enemies[i].getSpawnY() == -1.f) && (glfwGetTime() - setTimerEnemy) >= 5)
        {
            modelMatrixEnemies[i] = glm::mat3(1);
            enemies[i].setSpawnX(rand() % (resolution.x + 240) + 60 + (int)translateX);
            enemies[i].setSpawnY(rand() % (resolution.y + 240) + 60 + (int)translateY);
            enemies[i].setTranslateX(0);
            enemies[i].setTranslateY(0);
            enemies[i].setSpeed((rand() % 100) + 20); //speed from 20 to 100
            setTimerEnemy = glfwGetTime();
        }
        if (enemies[i].getSpawnX() != -1.f && enemies[i].getSpawnX() != -1.f)
        {
            float spawnX = enemies[i].getSpawnX();
            float spawnY = enemies[i].getSpawnY();
            float dirX = resolution.x / 2 - spawnX - enemies[i].getTranslateX();
            float dirY = resolution.y / 2 - spawnY - enemies[i].getTranslateY();
            float hyp = sqrt(dirX * dirX + dirY * dirY);
            dirX /= hyp;
            dirY /= hyp;
            enemies[i].setTranslateX(enemies[i].getTranslateX() + dirX * enemies[i].getSpeed() * deltaTimeSeconds);
            enemies[i].setTranslateY(enemies[i].getTranslateY() + dirY * enemies[i].getSpeed() * deltaTimeSeconds);

            if (CheckEnemyPlayerCollision(enemies[i], resolution))
            {
                enemies[i].setSpawnX(-1);
                enemies[i].setSpawnY(-1);
                health--;
                if (health < 0)
                {
                    cout << "GAME OVER!" << endl;
                }
            }
            modelMatrixEnemies[i] = transform2D::Translate(spawnX + enemies[i].getTranslateX(), spawnY + enemies[i].getTranslateY());
            modelMatrixEnemies[i] *= transform2D::Rotate(enemies[i].getDirectionEnemy());
            RenderMesh2D(meshes["enemyHead"], shaders["VertexColor"], modelMatrixEnemies[i]);
            modelMatrixEnemies[i] *= transform2D::Translate(-5, -5);
            RenderMesh2D(meshes["enemyHeadOutline"], shaders["VertexColor"], modelMatrixEnemies[i]);

            modelMatrixEnemies[i] *= transform2D::Translate(50, 45);
            RenderMesh2D(meshes["enemyHand"], shaders["VertexColor"], modelMatrixEnemies[i]);
            modelMatrixEnemies[i] *= transform2D::Translate(-5, -5);
            RenderMesh2D(meshes["enemyHandOutline"], shaders["VertexColor"], modelMatrixEnemies[i]);

            modelMatrixEnemies[i] *= transform2D::Translate(5, -45);
            RenderMesh2D(meshes["enemyHand"], shaders["VertexColor"], modelMatrixEnemies[i]);
            modelMatrixEnemies[i] *= transform2D::Translate(-5, -5);
            RenderMesh2D(meshes["enemyHandOutline"], shaders["VertexColor"], modelMatrixEnemies[i]);
        }
    }
}

void Tema1::MoveEnemies(glm::ivec2 resolution)
{
    for (int i = 0; i < numberOfEnemies; i++)
    {
        if (enemies[i].getSpawnX() != -1.f && enemies[i].getSpawnY() != -1.f)
        {
            float spawnX = enemies[i].getSpawnX();
            float spawnY = enemies[i].getSpawnY();
            float coordinateX = resolution.x / 2 - spawnX - enemies[i].getTranslateX();
            float coordinateY = resolution.y / 2 - spawnY - enemies[i].getTranslateY();
            float directionEnemy = atan2(coordinateY, coordinateX);

            if (enemies[i].getDirectionEnemy() != directionEnemy) 
            {
                enemies[i].setDirectionEnemy(directionEnemy);
            }
        }
    }
}

void Tema1::FireBullet(float deltaTimeSeconds)
{
    glm::ivec2 resolution = window->GetResolution();
    for (int i = 0; i < bulletsOnScreen; i++) 
    {   
        float translateBulletX = bullets[i].getTranslateX();
        float translateBulletY = bullets[i].getTranslateY();
        if ((translateBulletX - translateX - 10.f < 0) //bullet collision left edge
            || (translateBulletX - translateX - resolution.x - 290 > 0) //bullet collision right edge
            || (resolution.y + 290 + translateY - translateBulletY < 0) //bullet collision upper edge
            || (translateY - translateBulletY + 10.f > 0) //bullet collision bottom edge
            || functions::CheckRectangleRectangleCollision(leftCornersRectangleX, leftCornersRectangleY,
                translateX, translateY, resolution, 200.f, 100.f, translateBulletX, translateBulletY)
            || functions::CheckRectangleRectangleCollision(leftCornersSquareX, leftCornersSquareY,
                translateX, translateY, resolution, 200.f, 200.f, translateBulletX, translateBulletY))
        {
            bullets.erase(bullets.begin() + i);
            bulletsOnScreen--;  
        }
        else if (CheckEnemyBulletCollision(enemies, resolution, translateBulletX, translateBulletY) != -1)
        {
            int enemyNumber = CheckEnemyBulletCollision(enemies, resolution, translateBulletX, translateBulletY);
            bullets.erase(bullets.begin() + i);
            bulletsOnScreen--;
            enemies[enemyNumber].setSpawnX(-1);
            enemies[enemyNumber].setSpawnY(-1);
            score++;
            cout << "SCORE = " << score << endl;
        } else
        {
            modelMatrixBullet[i] = glm::mat3(1);
            bullets[i].setTranslateX(translateBulletX + bullets[i].getDirectionX() * deltaTimeSeconds * BULLETSPEED);
            bullets[i].setTranslateY(translateBulletY + bullets[i].getDirectionY() * deltaTimeSeconds * BULLETSPEED);
            modelMatrixBullet[i] = transform2D::Translate(bullets[i].getTranslateX(), bullets[i].getTranslateY());
            modelMatrixBullet[i] *= transform2D::Rotate(bullets[i].getDirection());
            RenderMesh2D(meshes["projectile"], shaders["VertexColor"], modelMatrixBullet[i]); //starting coordonates of the bullet
        }
        
    }
}

void Tema1::SpawnHealthKit(glm::ivec2 resolution)
{
    if (glfwGetTime() - setTimerHealthKit > 10)
    {
        modelMatrixHealthKit = glm::mat3(1);
        healthKit.setSpawnX(rand() % (resolution.x + 240) + 60 + (int)translateX);
        healthKit.setSpawnY(rand() % (resolution.y + 240) + 60 + (int)translateY);
        setTimerHealthKit = glfwGetTime();
    }
}

bool Tema1::CheckHealthPlayerCollision(glm::ivec2 resolution)
{
    float rectXL = healthKit.getSpawnX() + translateX;
    float rectXR = healthKit.getSpawnX() + translateX + 20;
    float rectYU = healthKit.getSpawnY() + translateY + 20;
    float rectYD = healthKit.getSpawnY() + translateY;
    if ((rectXL < (resolution.x / 2 + 20.f))
        && (rectXR > (resolution.x / 2 - 20.f))
        && (rectYD < (resolution.y / 2 + 20.f))
        && (rectYU > (resolution.y / 2 - 20.f)))
    {
        return true;
    }
    return false;
}


