#pragma clang diagnostic push
#pragma ide diagnostic ignored "cppcoreguidelines-narrowing-conversions"

#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <spdlog/spdlog.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtx/vector_angle.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <engine/filesystem.hpp>
#include <engine/shader.hpp>
#include <engine/camera.hpp>
#include <engine/model.hpp>

#include <iostream>
#include <algorithm>
#include <boids/flock.hpp>
#include <boids/fish.hpp>

void framebuffer_size_callback(GLFWwindow *window, int width, int height);

void mouse_callback(GLFWwindow *window, double xpos, double ypos);

void scroll_callback(GLFWwindow *window, double xoffset, double yoffset);

void processInput(GLFWwindow *window);

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

// settings
const unsigned int SCR_WIDTH = 1024;
const unsigned int SCR_HEIGHT = 768;

// camera

float lastX = SCR_WIDTH / 2.0f;
float lastY = SCR_HEIGHT / 2.0f;
bool firstMouse = true;

// timing
float deltaTime = 0.0f;
float lastFrame = 0.0f;

struct PointLight {
    glm::vec3 position;
    glm::vec3 ambient;
    glm::vec3 diffuse;
    glm::vec3 specular;

    float constant;
    float linear;
    float quadratic;
};

struct ProgramState {
//    glm::vec3 clearColor = glm::vec3(0.05, 0.2, 0.3);
    glm::vec3 clearColor = glm::vec3(0.05, 0.05, 0.1);
    Flock* flock = nullptr;
    bool ImGuiEnabled = false;
    Camera camera;
    bool CameraFixedCheck = false;
    glm::vec3 backpackPosition = glm::vec3(0.0f);
    float fishScale = 1.0f;
    float fps = 0;
    PointLight pointLight{};
    ProgramState()
            : camera(glm::vec3(0.0f, 0.0f, 3.0f)) {}

    void SaveToFile(std::string filename);

    void LoadFromFile(const std::string& filename);
};

void ProgramState::SaveToFile(std::string filename) {
    std::ofstream out(filename);
    out << clearColor.r << '\n'
        << clearColor.g << '\n'
        << clearColor.b << '\n'
        << ImGuiEnabled << '\n'
        << camera.Position.x << '\n'
        << camera.Position.y << '\n'
        << camera.Position.z << '\n'
        << camera.Front.x << '\n'
        << camera.Front.y << '\n'
        << camera.Front.z << '\n';
}

void ProgramState::LoadFromFile(const std::string& filename) {
    std::ifstream in(filename);
    if (in) {
        in >> clearColor.r
           >> clearColor.g
           >> clearColor.b
           >> ImGuiEnabled
           >> camera.Position.x
           >> camera.Position.y
           >> camera.Position.z
           >> camera.Front.x
           >> camera.Front.y
           >> camera.Front.z;
    }
}

ProgramState *programState;

void DrawImGui(ProgramState *state);

int main() {
    // glfw: initialize and configure
    // ------------------------------
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

#ifdef __APPLE__
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    //logging config
    //--------------
    spdlog::set_pattern("[%H:%M:%S] [%l] %v");
#ifdef DEBUG
    spdlog::set_level(spdlog::level::debug);
#endif

    spdlog::debug("Debug mode is ON");

    // glfw window creation
    // --------------------
    GLFWwindow *window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "Boids", nullptr, nullptr);
    if (window == nullptr) {
        spdlog::error("Failed to create GLFW window");
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);
    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
    glfwSetCursorPosCallback(window, mouse_callback);
    glfwSetScrollCallback(window, scroll_callback);
    glfwSetKeyCallback(window, key_callback);
    // tell GLFW to capture our mouse
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    // glad: load all OpenGL function pointers
    // ---------------------------------------
    if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress)) {
        spdlog::error("Failed to initialize GLAD");
        return -1;
    }

    // tell stb_image.h to flip loaded texture's on the y-axis (before loading model).
    stbi_set_flip_vertically_on_load(true);

    programState = new ProgramState;
    programState->LoadFromFile("resources/program_state.txt");
    if (programState->ImGuiEnabled) {
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
    }
    // Init Imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO &io = ImGui::GetIO();
    (void) io;



    ImGui_ImplGlfw_InitForOpenGL(window, true);
    ImGui_ImplOpenGL3_Init("#version 330 core");

    // configure global opengl state
    // -----------------------------
    glEnable(GL_DEPTH_TEST);

    // build and compile shaders
    // -------------------------
    Shader boidShader("resources/shaders/boid.vs", "resources/shaders/boid.fs");

    // load models
    // -----------
    Model loadedModel("resources/objects/fish/fish.obj");
    loadedModel.SetShaderTextureNamePrefix("material.");

    //initialize flock
    //----------------
//    Fish::initialize();
    Flock flock;
    programState->flock = &flock;
    flock.setCubeDimension(30);
    int posCap = 20;
    int dposCap = 10;
    int numBoids = 500;
    for(int i = 0; i < numBoids; i++){
        flock.add_boid(new Boid(glm::vec3(frandom(-posCap, posCap), frandom(-posCap, posCap), frandom(-posCap, posCap)),
                                glm::vec3(frandom(-dposCap, dposCap), frandom(-dposCap, dposCap), frandom(-dposCap, dposCap))));
    }

    PointLight& pointLight = programState->pointLight;
    pointLight.position = glm::vec3(4.5f, 1.0f, 0.0f);
    pointLight.ambient = glm::vec3(1, 0.65, 0.65);
    pointLight.diffuse = glm::vec3(0.6, 0.6, 0.6);
    pointLight.specular = glm::vec3(1.0, 1.0, 1.0);

    pointLight.constant = 1.0f;
    pointLight.linear = 0.1f;
    pointLight.quadratic = 0.01f;

    // draw in wireframe
    //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);

    // render loop
    // -----------
    float time = 0;
    while (!glfwWindowShouldClose(window)) {
        // per-frame time logic
        // --------------------
        float currentFrame = glfwGetTime(); // NOLINT(cppcoreguidelines-narrowing-conversions)
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        //update framerate every second
        if(currentFrame - time > 1) {
            programState->fps = 1/deltaTime;
            time = currentFrame;
        }

        // input
        // -----
        processInput(window);


        // render
        // ------
        glClearColor(programState->clearColor.r, programState->clearColor.g, programState->clearColor.b, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        // render flock
        //-------------
        if(programState->fishScale != flock.getCollisionDistence()) {
            flock.mulScale(programState->fishScale);
        }
        flock.update(deltaTime*10);
        for(Boid* boid : flock.getBoids()) {
            //spdlog::debug("{0} {1} {2}", boid->getPos().x, boid->getPos().y, boid->getPos().z);
            boidShader.use();
            //pointLight.position = glm::vec3(1.0 * cos(currentFrame), 1.0f, 4.0 * sin(currentFrame));
            pointLight.position = flock.getCenterOfMass();
//            spdlog::debug("{0}", flock.getDiameter());
            pointLight.constant = abs(cos(2.0f*currentFrame)) * 0.7f + 0.3f;
            pointLight.ambient = glm::vec3(1 - std::min(18/flock.getDiameter() - 0.4f, 1.0f), pointLight.ambient.y, pointLight.ambient.z);
            boidShader.setVec3("pointLight.position", pointLight.position);
            boidShader.setVec3("pointLight.ambient", pointLight.ambient);
            boidShader.setVec3("pointLight.diffuse", pointLight.diffuse);
            boidShader.setVec3("pointLight.specular", pointLight.specular);
            boidShader.setFloat("pointLight.constant", pointLight.constant);
            boidShader.setFloat("pointLight.linear", pointLight.linear);
            boidShader.setFloat("pointLight.quadratic", pointLight.quadratic);
            boidShader.setVec3("viewPosition", programState->camera.Position);
            boidShader.setFloat("material.shininess", 50.0f);
            // viewBoid/projectionBoid transformations
            glm::mat4 projectionBoid = glm::perspective(glm::radians(programState->camera.Zoom),
                                                        (float) SCR_WIDTH / (float) SCR_HEIGHT, 0.1f, 100.0f);
            glm::mat4 viewBoid;
            if(programState->CameraFixedCheck){
                viewBoid = programState->camera.GetViewMatrix(flock.getCenterOfMass() - flock.getGeneralDirection() * 8.0f);
            } else {
                viewBoid = programState->camera.GetViewMatrix();
            }

            boidShader.setMat4("projection", projectionBoid);
            boidShader.setMat4("view", viewBoid);

            glm::mat4 boidModel = glm::mat4(1.0f);
            boidModel = glm::translate(boidModel,
                                       boid->getPos()); // translate it down so it's at the center of the scene
//            glm::mat4 RotationMatrix = glm::inverse(glm::lookAt(boid->getPos(), boid->getPos() + boid->getDirection(), glm::vec3(0.0f, 1.0f, 0.0f)));
//            boidModel *= RotationMatrix;
            float angle = glm::orientedAngle(glm::normalize(boid->getDirection()), glm::vec3(0,0,1), glm::vec3(0,0,1));

            boidModel = glm::rotate(boidModel, angle, glm::cross(glm::vec3(0,0,1), boid->getDirection()));
            boidModel = glm::scale(boidModel, glm::vec3(programState->fishScale / 2));    // it's a bit too big for our scene, so scale it down

            boidShader.setMat4("model", boidModel);
            loadedModel.Draw(boidShader);
//            boid->getModel().Draw(boidShader);
        }

        if (programState->ImGuiEnabled)
            DrawImGui(programState);

        // glfw: swap buffers and poll IO events (keys pressed/released, mouse moved etc.)
        // -------------------------------------------------------------------------------
        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    programState->SaveToFile("resources/program_state.txt");
    delete programState;
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();
    // glfw: terminate, clearing all previously allocated GLFW resources.
    // ------------------------------------------------------------------
    glfwTerminate();
    return 0;
}

// process all input: query GLFW whether relevant keys are pressed/released this frame and react accordingly
// ---------------------------------------------------------------------------------------------------------
void processInput(GLFWwindow *window) {
    if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        glfwSetWindowShouldClose(window, true);

    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        programState->camera.ProcessKeyboard(FORWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        programState->camera.ProcessKeyboard(BACKWARD, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        programState->camera.ProcessKeyboard(LEFT, deltaTime);
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        programState->camera.ProcessKeyboard(RIGHT, deltaTime);
}

// glfw: whenever the window size changed (by OS or user resize) this callback function executes
// ---------------------------------------------------------------------------------------------
void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
    // make sure the viewport matches the new window dimensions; note that width and
    // height will be significantly larger than specified on retina displays.
    glViewport(0, 0, width, height);
}

// glfw: whenever the mouse moves, this callback is called
// -------------------------------------------------------
void mouse_callback(GLFWwindow *window, double xpos, double ypos) {
    if (firstMouse) {
        lastX = xpos;
        lastY = ypos;
        firstMouse = false;
        programState->camera.ProcessMouseMovement(0, 0);
    }

    float xoffset =  lastX - xpos;
    float yoffset = ypos - lastY; // reversed since y-coordinates go from bottom to top

    lastX = xpos;
    lastY = ypos;

    int clickstate = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);

    if (clickstate == GLFW_PRESS && !programState->CameraFixedCheck)
        programState->camera.ProcessMouseMovement(xoffset, yoffset);
}

// glfw: whenever the mouse scroll wheel scrolls, this callback is called
// ----------------------------------------------------------------------
void scroll_callback(GLFWwindow *window, double xoffset, double yoffset) {
    programState->camera.ProcessMouseScroll(yoffset);
}

void DrawImGui(ProgramState *state) {
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplGlfw_NewFrame();
    ImGui::NewFrame();

    {
        static float f = 0.0f;
        ImGui::Begin("Settings");
        ImGui::DragFloat("Fish size", &state->fishScale, 0.05, 0.1, 4.0);
        ImGui::DragFloat("pointLight.constant", &state->pointLight.constant, 0.05, 0.0, 1.0);
        ImGui::DragFloat("pointLight.linear", &state->pointLight.linear, 0.05, 0.0, 1.0);
        ImGui::DragFloat("pointLight.quadratic", &state->pointLight.quadratic, 0.05, 0.0, 1.0);
        ImGui::Checkbox("Fix camera to center", &state->CameraFixedCheck);
        ImGui::Checkbox("Separation", &(state->flock->b_separate));
        ImGui::Checkbox("Alignment", &(state->flock->b_align));
        ImGui::Checkbox("Cohesion", &(state->flock->b_cohere));
        ImGui::End();
    }

    {
        ImGui::Begin("Camera");
        const Camera& c = state->camera;
        ImGui::Text("Camera position: (%f, %f, %f)", c.Position.x, c.Position.y, c.Position.z);
        ImGui::Text("(Yaw, Pitch): (%f, %f)", c.Yaw, c.Pitch);
        ImGui::Text("Camera front: (%f, %f, %f)", c.Front.x, c.Front.y, c.Front.z);
        ImGui::Text("Frame rate: (%d)", int(state->fps));
        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if (key == GLFW_KEY_F1 && action == GLFW_PRESS) {
        programState->ImGuiEnabled = !programState->ImGuiEnabled;
        if (programState->ImGuiEnabled) {
            programState->CameraFixedCheck = false;
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        } else {
            glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
        }
    }
    if (key == GLFW_KEY_SPACE && action == GLFW_PRESS) {
        if (programState->CameraFixedCheck) {
//            programState->
        }
    }
}

#pragma clang diagnostic pop