#include "Renderer.h"
#include "Pong.h"
#include <glm/ext/matrix_clip_space.hpp>
#include <glm/gtx/transform.hpp>

Pong::Pong()
	:m_PaddleLeftPos(glm::vec3(-0.9f, 0.0f, 0.0f)),
    m_PaddleRightPos(glm::vec3(0.9f, 0.0f, 0.0f)),
    m_BallPos(glm::vec3(0.0f, 0.0f, 0.0f)),
    m_BallVelocity(glm::vec3(0.5f, 0.5f, 0.0f)),
    m_PaddleSpeed(1.0f)
{
    m_Projection = glm::ortho(-1.0f, 1.0f, -1.0f, 1.0f, -1.0f, 1.0f);
    m_View = glm::mat4(1.0f);
    Init();
}

Pong::~Pong()
{
    delete m_VBO;
    delete m_IBO;
    delete m_Shader;
}

void Pong::Init()
{
    float positions[] = {
        -0.05f, -0.2f, 0.0f, // Bottom-left
         0.05f, -0.2f, 0.0f, // Bottom-right
         0.05f,  0.2f, 0.0f, // Top-right
        -0.05f,  0.2f, 0.0f, // Top-left
    };

    unsigned int indices[] = {
       0, 1, 2, // First triangle
       2, 3, 0  // Second triangle
    };

    // Approximation of a circle for the ball
    const int numSegments = 30; // Higher number for smoother circle
    float ballPositions[(numSegments + 2) * 3]; // +2 for center and duplicate vertex

    // Center vertex of the circle
    ballPositions[0] = 0.0f; // X
    ballPositions[1] = 0.0f; // Y
    ballPositions[2] = 0.0f; // Z

    float angleStep = 2.0f * 3.14159f / numSegments;

    for (int i = 1; i <= numSegments + 1; i++) {
        float angle = (i - 1) * angleStep;
        ballPositions[i * 3] = 0.05f * cos(angle); // X
        ballPositions[i * 3 + 1] = 0.05f * sin(angle); // Y
        ballPositions[i * 3 + 2] = 0.0f;              // Z
    }

    unsigned int ballIndices[numSegments * 3];
    for (int i = 0; i < numSegments; i++) {
        ballIndices[i * 3] = 0;           // Center vertex
        ballIndices[i * 3 + 1] = i + 1;   // Current outer vertex
        ballIndices[i * 3 + 2] = i + 2;   // Next outer vertex
    }

    m_VBO = new VertexBuffer(positions, sizeof(positions));
    m_IBO = new IndexBuffer(indices, 6);

    VertexBufferLayout layout;
    layout.push<float>(3);
    m_VAO.addBuffer(*m_VBO, layout);

    m_BallVBO = new VertexBuffer(ballPositions, sizeof(ballPositions));
    m_BallIBO = new IndexBuffer(ballIndices, numSegments * 3);

    m_BallVAO.addBuffer(*m_BallVBO, layout);

    m_VAO.bind();

    m_Shader = new Shader("res/Basic.shader");
    m_Shader->bind();
    m_Shader->setUniformMat4f("u_Projection", m_Projection);
    m_Shader->setUniformMat4f("u_View", m_View);

    ResetBall();
    ResetPaddles();

}

void Pong::Update(float deltaTime) {
    m_BallPos += m_BallVelocity * deltaTime;

    CheckCollisions();
}

void Pong::Render() 
{
    GLCall(glClear(GL_COLOR_BUFFER_BIT));

    m_Shader->bind();

    glm::mat4 modelLeft = glm::translate(glm::mat4(1.0f), m_PaddleLeftPos);
    m_Shader->setUniformMat4f("u_Model", modelLeft);
    m_Shader->setUniform4f("uColor", 1.0f, 0.0f, 0.0f, 1.0f); // Red color
    m_VAO.bind();
    m_IBO->Bind();
    m_Renderer->draw(m_VAO,*m_IBO, *m_Shader, GL_TRIANGLES);

    glm::mat4 modelRight = glm::translate(glm::mat4(1.0f), m_PaddleRightPos);
    m_Shader->setUniformMat4f("u_Model", modelRight);
    m_Shader->setUniform4f("uColor", 0.0f, 0.0f, 1.0f, 1.0f); // Blue color
    m_Renderer->draw(m_VAO, *m_IBO, *m_Shader, GL_TRIANGLES);

    glm::mat4 modelBall = glm::translate(glm::mat4(1.0f), m_BallPos);
    m_Shader->setUniformMat4f("u_Model", modelBall);
    m_BallVAO.bind();
    m_BallIBO->Bind();
    m_Renderer->draw(m_BallVAO, *m_BallIBO, *m_Shader, GL_TRIANGLES);

}

void Pong::ProcessInput(float deltaTime) {
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_W) == GLFW_PRESS) {
        m_PaddleLeftPos.y += m_PaddleSpeed * deltaTime;
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_S) == GLFW_PRESS) {
        m_PaddleLeftPos.y -= m_PaddleSpeed * deltaTime;
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_UP) == GLFW_PRESS) {
        m_PaddleRightPos.y += m_PaddleSpeed * deltaTime;
    }
    if (glfwGetKey(glfwGetCurrentContext(), GLFW_KEY_DOWN) == GLFW_PRESS) {
        m_PaddleRightPos.y -= m_PaddleSpeed * deltaTime;
    }
}

void Pong::ResetBall() {
    m_BallPos = glm::vec3(0.0f, 0.0f, 0.0f);
    m_BallVelocity = glm::vec3(0.5f, 0.5f, 0.0f); // Ball speed
}

void Pong::ResetPaddles() {
    m_PaddleLeftPos = glm::vec3(-0.9f, 0.0f, 0.0f);
    m_PaddleRightPos = glm::vec3(0.9f, 0.0f, 0.0f);
}

void Pong::CheckCollisions()
{

}



