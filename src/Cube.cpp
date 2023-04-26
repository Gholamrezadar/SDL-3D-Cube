#include "Cube.h"

std::vector<glm::vec2>
generateCube(float angle, bool isOrthographic)
{
    // Actual cube points in 3d space (between -1 and 1)
    const std::vector<glm::vec3> points3D{
        {-0.5, 0.5, 0.5},
        {0.5, 0.5, 0.5},
        {0.5, -0.5, 0.5},
        {-0.5, -0.5, 0.5},
        {-0.5, 0.5, -0.5},
        {0.5, 0.5, -0.5},
        {0.5, -0.5, -0.5},
        {-0.5, -0.5, -0.5},
    };

    // Define model and view matrices
    glm::mat4 model = glm::mat4(1.0f); // identity matrix

    // Rotate model matrix
    model = glm::rotate(
        model,
        glm::radians(angle), // angle in radians    
        glm::vec3(0.0f, 1.0f, 0.0f) // axis of rotation
    );

    glm::mat4 view = glm::lookAt(
        glm::vec3(0.0f, 1.0f, 3.0f), // camera position
        glm::vec3(0.0f, 0.0f, 0.0f), // target position
        glm::vec3(0.0f, 1.0f, 0.0f)  // up vector
    );

    // Define projection matrix
    glm::mat4 projection;
    if (isOrthographic)
    {
        projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, 0.1f, 100.0f);
    }
    else
    {
        // Define projection matrix parameters
        float fov = glm::radians(35.0f); // field of view in radians
        float aspectRatio = 1.0f;        // aspect ratio of the screen
        float nearPlane = 0.1f;          // distance to the near plane
        float farPlane = 100.0f;         // distance to the far plane

        projection = glm::perspective(fov, aspectRatio, nearPlane, farPlane);
    }

    // Combine matrices to create MVP matrix
    glm::mat4 MVP = projection * view * model;

    // Apply MVP matrix to each point
    std::vector<glm::vec3> points2D;
    for (const auto &point : points3D)
    {
        glm::vec4 transformedPoint = MVP * glm::vec4(point, 1.0f);
        transformedPoint /= transformedPoint.w;
        points2D.push_back(glm::vec3(transformedPoint));
    }

    // Map points to screen coordinates
    std::vector<glm::vec2> screenPoints;
    for (const auto &point : points2D)
    {
        screenPoints.push_back(glm::vec2(
            (point.x + 1.0f) * 0.5f * WINDOW_W, // map x coordinate to screen width
            (-point.y + 1.0f) * 0.5f * WINDOW_H // map y coordinate to screen height ( - because y is inverted)
            ));
    }
    return screenPoints;
}
