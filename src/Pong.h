#include "Renderer.h"
#include "Shader.h"
#include <glm/glm.hpp>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "VertexBufferLayout.h"

class Pong
{
private:
    VertexArray m_VAO;
    VertexBuffer* m_VBO;
    IndexBuffer* m_IBO;
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