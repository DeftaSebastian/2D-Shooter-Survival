#pragma once

#include "utils/glm_utils.h"
#include "lab_m1/Tema1/Enemies.h"

using namespace std;
namespace functions
{
    // Translate matrix
    inline glm::mat3 Translate(float translateX, float translateY)
    {
        // TODO(student): Implement the translation matrix
        return glm::mat3(
            1.f, 0.f, 0.f,
            0.f, 1.f, 0.f,
            translateX, translateY, 1.f);
    }

    inline bool CheckRectangleRectangleCollision(std::vector<float> leftCornersX,
        std::vector<float> leftCornersY, float rectangleX, float rectangleY, glm::ivec2 resolution,
        float width, float height, float bulletPosX, float bulletPosY)
    {
        for (int i = 0; i < leftCornersX.size(); i++)
        {
            float rectXL = leftCornersX[i] + rectangleX;
            float rectXR = leftCornersX[i] + rectangleX + width;
            float rectYU = leftCornersY[i] + height + rectangleY;
            float rectYD = leftCornersY[i] + rectangleY;
            if ((rectXL < (bulletPosX + 10.f))
                && (rectXR > (bulletPosX - 10.f))
                && (rectYD < (bulletPosY + 10.f))
                && (rectYU > (bulletPosY - 10.f)))
            {
                return true;
            }
        }
        return false;
    }

    inline bool CheckRectangleCollisionLeft(std::vector<float> leftCornersX, 
        std::vector<float> leftCornersY, float posX, float posY, glm::ivec2 resolution,
        float width, float height)
    {
        for (int i = 0; i < leftCornersX.size(); i++)
        {
            float rectXL = leftCornersX[i] + posX;
            float rectXR = leftCornersX[i] + posX + width;
            float rectYU = leftCornersY[i] + height + posY;
            float rectYD = leftCornersY[i] + posY;
            if ((rectXL < (resolution.x / 2 + 20.f))
                && (rectXR > (resolution.x / 2 - 20.f))
                && (rectYD < (resolution.y / 2 + 20.f))
                && (rectYU > (resolution.y / 2 - 20.f)))
            {
                if (rectXL > (resolution.x / 2))
                    return true;
                else
                    return false;
            }
        }
        return false;
    }

    inline bool CheckRectangleCollisionRight(std::vector<float> leftCornersX,
        std::vector<float> leftCornersY, float posX, float posY, glm::ivec2 resolution,
        float width, float height)
    {
        for (int i = 0; i < leftCornersX.size(); i++)
        {
            float rectXL = leftCornersX[i] + posX;
            float rectXR = leftCornersX[i] + posX + width;
            float rectYU = leftCornersY[i] + height + posY;
            float rectYD = leftCornersY[i] + posY;
            if ((rectXL < (resolution.x / 2 + 20.f))
                && (rectXR > (resolution.x / 2 - 20.f))
                && (rectYD < (resolution.y / 2 + 20.f))
                && (rectYU > (resolution.y / 2 - 20.f)))
            {

                if (rectXR < (resolution.x / 2))
                    return true;
                else
                    return false;
            }
        }
        return false;
    }

    inline bool CheckRectangleCollisionDown(std::vector<float> leftCornersX,
        std::vector<float> leftCornersY, float posX, float posY, glm::ivec2 resolution,
        float width, float height)
    {
        for (int i = 0; i < leftCornersX.size(); i++)
        {
            float rectXL = leftCornersX[i] + posX;
            float rectXR = leftCornersX[i] + posX + width;
            float rectYU = leftCornersY[i] + height + posY;
            float rectYD = leftCornersY[i] + posY;
            if ((rectXL < (resolution.x / 2 + 20.f))
                && (rectXR > (resolution.x / 2 - 20.f))
                && (rectYD < (resolution.y / 2 + 20.f))
                && (rectYU > (resolution.y / 2 - 20.f)))
            {
                if (rectYD > (resolution.y / 2 ))
                    return true;
                else
                    return false;
            }
        }
        return false;
    }

    inline bool CheckRectangleCollisionUp(std::vector<float> leftCornersX,
        std::vector<float> leftCornersY, float posX, float posY, glm::ivec2 resolution,
        float width, float height)
    {
        for (int i = 0; i < leftCornersX.size(); i++)
        {
            float rectXL = leftCornersX[i] + posX;
            float rectXR = leftCornersX[i] + posX + width;
            float rectYU = leftCornersY[i] + height + posY;
            float rectYD = leftCornersY[i] + posY;
            if ((rectXL < (resolution.x / 2 + 20.f))
                && (rectXR > (resolution.x / 2 - 20.f))
                && (rectYD < (resolution.y / 2 + 20.f))
                && (rectYU > (resolution.y / 2 - 20.f)))
            {
                if (rectYU < (resolution.y / 2 ))
                    return true;
                else
                    return false;
            }
        }
        return false;
    }
}   // namespace transform2D
