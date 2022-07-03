#include"Renderer/ShaderProgram.h"
#include"Resources/ResourceManager.h"

GLfloat point[] = {
     0.0f,  0.5f, 0.0f,
     0.5f, -0.5f, 0.0f,
    -0.5f, -0.5f, 0.0f
};
GLfloat colors[] = {
    1.0f, 0.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 0.0f, 1.0f
};






namespace winSize {
    int x = 640;
    int y = 460;
}
void glfwWindowSizeCallback(GLFWwindow* pWindow, int width, int height) {
    winSize::x = width;
    winSize::y = height;
    glViewport(0, 0, winSize::x, winSize::y);//���� �������� ��� �� ����� ��������
//0,0 ��� ����
}

void glfwCallback(GLFWwindow* pWindow, int key, int scancode, int action, int mode) {
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
        glfwSetWindowShouldClose(pWindow, GL_TRUE);
    }
}



int main(int argc,char** argv)
{
    
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);//core profile ��� ������������ ������� opengl ���� �� �������� ��� ������� �� �������� ������������� ��������� ������ opengl
    /* Initialize the library */
    if (!glfwInit()) {//�������� ������� ������������� glwf
        std::cout << "glfwInit failed" << std::endl;
        return -1;
    }
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);//�������� ������ openGL
    // glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);//���� � ��� ����� ������ ������ 4 � 6, �� �� ������ �� ������ ������� ����

     /* Create a windowed mode window and its OpenGL context */
    GLFWwindow* pWindow = glfwCreateWindow(winSize::x, winSize::y, "Battle City", nullptr, nullptr);//�������� ����
    if (!pWindow)//���� ���� �� ���� ������� �������, �� ������� �� ���������
    {
        //������� ��������� �� ������
        std::cout << "glfwCreateWindow is falied\n";
        glfwTerminate();//����������� ��� �������
        return -1;
    }

    glfwSetWindowSizeCallback(pWindow, glfwWindowSizeCallback);
    glfwSetKeyCallback(pWindow, glfwCallback);

    /* Make the window's context current */
   //�� ������ �������� ������ ��� �������� ����, ���� � ��� ����� ���� ���������
   //� ��� ������� ���� � ��� ����� ���� ���� ���� ��  ��������
   //������� �� ������ ������� ������� ������ ����
    glfwMakeContextCurrent(pWindow);

    //�������������� ���������� ����
    if (!gladLoadGL()) {
        std::cout << "Can't load GLAD!" << std::endl;
        return -1;
    }

    std::cout << "Renderer: " << glGetString(GL_RENDERER) << std::endl;//���������� ����� ������������ ����� �����
    std::cout << "OpenGL version: " << glGetString(GL_VERSION) << std::endl;//���������� ����� ������������� ������ opengl



    glClearColor(1, 1, 0, 1);

    
    {
        ResourceManager resourceManager(*argv);
        auto pDefaultShaderProgram = resourceManager.loadShaders("DefaultShader", "res/shaders/vertex.txt", "res/shaders/fragment.txt");
        if (!pDefaultShaderProgram) {
            cerr << "Can't create shader program: " << "DefaultShader " << endl;
            return -1;
        }
       
        GLuint points_vbo = 0;
        glGenBuffers(1, &points_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(point), point, GL_STATIC_DRAW);

        GLuint colors_vbo = 0;
        glGenBuffers(1, &colors_vbo);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glBufferData(GL_ARRAY_BUFFER, sizeof(colors), colors, GL_STATIC_DRAW);

        GLuint vao = 0;
        glGenVertexArrays(1, &vao);
        glBindVertexArray(vao);

        glEnableVertexAttribArray(0);
        glBindBuffer(GL_ARRAY_BUFFER, points_vbo);
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

        glEnableVertexAttribArray(1);
        glBindBuffer(GL_ARRAY_BUFFER, colors_vbo);
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr);













        /* Loop until the user closes the window */
    //���� ���������, ����� ������� ���� �� ����� �������
        while (!glfwWindowShouldClose(pWindow))
        {
            /* Render here */
            glClear(GL_COLOR_BUFFER_BIT);//����� ���������� ������ �����
            //����� ����� ������ �����
            //������� ��� �������� �����
            /* Swap front and back buffers */
            pDefaultShaderProgram->use();
            glBindVertexArray(vao);
            glDrawArrays(GL_TRIANGLES, 0, 3);




            glfwSwapBuffers(pWindow);

            /* Poll for and process events */
            glfwPollEvents();//���� �������� glfw ������������ ��� ������� �� ���,
            //����� ��� ������� ������� , ��������� ������� �������, ��������� �������� ����,
            //�������� ���� , �� � ��������������� ������� ��������������
        }
    }

    glfwTerminate();
    return 0;
}