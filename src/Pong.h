#include "Renderer.h"
#include "Shader.h"
#include "GLFW/glfw3.h"
#include <glm/glm.hpp>
#include "VertexArray.h"
#include "IndexBuffer.h"
#include "VertexBuffer.h"
#include "Shader.h"
#include "VertexBufferLayout.h"
#include <string>

#define GLM_ENABLE_EXPERIMENTAL

class Pong
{
private:
    //Vertex Array,Vertex Buffers, Index Buffers,Shaders,Renderer
    VertexArray m_VAO;
    VertexArray m_BallVAO;
    VertexBuffer* m_VBO;
    IndexBuffer* m_IBO;
    VertexBuffer* m_BallVBO;
    IndexBuffer* m_BallIBO;
    Shader* m_Shader;
    Renderer* m_Renderer;

    //Vec3 to store the posns
    glm::vec3 m_PaddleLeftPos;
    glm::vec3 m_PaddleRightPos;
    glm::vec3 m_BallPos;

    //to store the velocity of the ball and the paddle
    glm::vec3 m_BallVelocity;
    float m_PaddleSpeed;

    // Projections and View matrices
    glm::mat4 m_Projection;
    glm::mat4 m_View;

    // Reset the Ball and Paddles
    void ResetBall();
    void ResetPaddles();

    //Checking the Collisions
    void CheckCollisions();
public:
	Pong();
	~Pong();

    std::string p1, p2, winner;
    int sc1, sc2;
	void Init();
	void Update(float deltaTime); 
	void Render();    
	void ProcessInput(float deltaTime); 
};