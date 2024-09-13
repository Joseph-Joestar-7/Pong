#include "Renderer.h"
#include "Shader.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

#define GLM_ENABLE_EXPERIMENTAL

class Pong
{
private:
    VertexArray m_VAO;
    VertexArray m_BallVAO;
    VertexBuffer* m_VBO;
    IndexBuffer* m_IBO;
    VertexBuffer* m_BallVBO;
    IndexBuffer* m_BallIBO;
    Shader* m_Shader;
    Renderer* m_Renderer;

    glm::vec3 m_PaddleLeftPos;
    glm::vec3 m_PaddleRightPos;
    glm::vec3 m_BallPos;

    glm::vec3 m_BallVelocity;
    float m_PaddleSpeed;

    // Projections and View matrices
    glm::mat4 m_Projection;
    glm::mat4 m_View;

    // Helper functions
    void ResetBall();
    void ResetPaddles();
    void CheckCollisions();
public:
	Pong();
	~Pong();

	void Init();
	void Update(float deltaTime); 
	void Render();    
	void ProcessInput(float deltaTime); 
};