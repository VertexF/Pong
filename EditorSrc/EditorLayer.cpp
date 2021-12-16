#include "PreComp.h"
#include "EditorLayer.h"

#include <glm/gtc/type_ptr.hpp>
#include <imgui.h>
#include <cmath>

namespace Tempest
{
    EditorLayer::EditorLayer() : Layer("Game"), _squareColour({ 0.8f, 0.3f, 0.2f, 1.f })
    {
        TEMPEST_PROFILE_FUNCTION();
        _cameraController = std::make_unique<OrthographicalCameraController>(1280.f / 720.f);

        _testText = std::make_unique<TextRenderer>(128.f);

        _soundDevice = SoundDevice::create();
        _soundBuffer = SoundBuffer::create();
        _mySource = std::make_shared<SoundSource>();

        _backgroundTexture = Texture2D::create("Assets/Textures/Checkerboard.png");
        _transCheck = Texture2D::create("Assets/Textures/alpha.png");

        _posX = 0.f;
        _posY = 0.f;
    }

    void EditorLayer::onAttach()
    {
        TEMPEST_PROFILE_FUNCTION();

        _cameraController->setZoomLevel(5.f);

        FramebufferSpec framebufferSpec;
        framebufferSpec.width = 1280;//Application::get().getWindow().getWidth();
        framebufferSpec.height = 720;//Application::get().getWindow().getHeight();
        _framebuffer = Framebuffer::create(framebufferSpec);

        _spellSoundBuffer = _soundBuffer->addSoundEffect("Assets/Audio/spell.wav");
        _magicFailSoundBuffer = _soundBuffer->addSoundEffect("Assets/Audio/magicfail.wav");
    }

    void EditorLayer::onDetach()
    {
        TEMPEST_PROFILE_FUNCTION();
    }

    void EditorLayer::onUpdate(TimeStep timeStep)
    {
        TEMPEST_PROFILE_FUNCTION();

        _cameraController->onUpdate(timeStep);

        _framebuffer->bind();
        RendererCommands::setClearColour({ 0.2f, 0.2f, 0.2f, 1.f });
        RendererCommands::clear();

        if (Input::isKeyPressed(TEMP_KEY_W)) 
        {
            _posY += 1.5f * timeStep;
        }

        if (Input::isKeyPressed(TEMP_KEY_S))
        {
            _posY -= 1.5f * timeStep;
        }

        if (Input::isKeyPressed(TEMP_KEY_A))
        {
            _posX -= 1.5f * timeStep;
        }

        if (Input::isKeyPressed(TEMP_KEY_D))
        {
            _posX += 1.5f * timeStep;
        }

        _cameraController->setCameraPosition({ _posX, _posY, 0.0f });

        Renderer2D::resetStats();

        Renderer2D::beginScene(_cameraController->getCamera());

        Renderer2D::drawQuad({ 1.f, 0.f, 0.5f }, { 30.f, 30.f }, _backgroundTexture, 20.f, { 0.4f, 0.8f, 0.8f, 1.f });
        Renderer2D::drawRotatedQuad({ _posX, _posY, 0.3f }, { 1.f, 1.f }, 0.f, _transCheck, 1.f, { 0.8f, 0.4f, 0.6f, 1.f });

        _testText->displayText({ -1.f, 3.f, 0.1f}, { 1.f, 1.f }, _squareColour, "The Game!");
        _testText->displayText({ _posX - 7.f, _posY + 4.f, 0.1f }, { 1.f, 1.f }, _squareColour, "0");

        Renderer2D::endScene();
        _framebuffer->unbind();
    }

    void EditorLayer::onEvent(Event& e)
    {
        _cameraController->onEvent(e);

        EventDispatcher dispatcher(e);
        dispatcher.dispatch<PressedKeyEvent>(std::bind(&EditorLayer::onKeyPressed, this, std::placeholders::_1));
        dispatcher.dispatch<ReleasedKeyEvent>(std::bind(&EditorLayer::onKeyReleased, this, std::placeholders::_1));
    }

    void EditorLayer::onImGuiRender()
    {
        TEMPEST_PROFILE_FUNCTION();

        // If you strip some features of, this demo is pretty much equivalent to calling DockSpaceOverViewport()!
        // In most cases you should be able to just call DockSpaceOverViewport() and ignore all the code below!
        // In this specific demo, we are not using DockSpaceOverViewport() because:
        // - we allow the host window to be floating/moveable instead of filling the viewport (when opt_fullscreen == false)
        // - we allow the host window to have padding (when opt_padding == true)
        // - we have a local menu bar in the host window (vs. you could use BeginMainMenuBar() + DockSpaceOverViewport() in your code!)
        // TL;DR; this demo is more complicated than what you would normally use.
        // If we removed all the options we are showcasing, this demo would become:
        //     void ShowExampleAppDockSpace()
        //     {
        //         ImGui::DockSpaceOverViewport(ImGui::GetMainViewport());
        //     }

        static bool opt_fullscreen = true;
        static bool opt_padding = false;
        static bool dockspaceShow = true;
        static ImGuiDockNodeFlags dockspace_flags = ImGuiDockNodeFlags_None;

        // We are using the ImGuiWindowFlags_NoDocking flag to make the parent window not dockable into,
        // because it would be confusing to have two docking targets within each others.
        ImGuiWindowFlags window_flags = ImGuiWindowFlags_MenuBar | ImGuiWindowFlags_NoDocking;
        if (opt_fullscreen)
        {
            const ImGuiViewport* viewport = ImGui::GetMainViewport();
            ImGui::SetNextWindowPos(viewport->WorkPos);
            ImGui::SetNextWindowSize(viewport->WorkSize);
            ImGui::SetNextWindowViewport(viewport->ID);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowRounding, 0.0f);
            ImGui::PushStyleVar(ImGuiStyleVar_WindowBorderSize, 0.0f);
            window_flags |= ImGuiWindowFlags_NoTitleBar | ImGuiWindowFlags_NoCollapse | ImGuiWindowFlags_NoResize | ImGuiWindowFlags_NoMove;
            window_flags |= ImGuiWindowFlags_NoBringToFrontOnFocus | ImGuiWindowFlags_NoNavFocus;
        }
        else
        {
            dockspace_flags &= ~ImGuiDockNodeFlags_PassthruCentralNode;
        }

        // When using ImGuiDockNodeFlags_PassthruCentralNode, DockSpace() will render our background
        // and handle the pass-thru hole, so we ask Begin() to not render a background.
        if (dockspace_flags & ImGuiDockNodeFlags_PassthruCentralNode)
            window_flags |= ImGuiWindowFlags_NoBackground;

        // Important: note that we proceed even if Begin() returns false (aka window is collapsed).
        // This is because we want to keep our DockSpace() active. If a DockSpace() is inactive,
        // all active windows docked into it will lose their parent and become undocked.
        // We cannot preserve the docking relationship between an active window and an inactive docking, otherwise
        // any change of dockspace/settings would lead to windows being stuck in limbo and never being visible.
        if (!opt_padding)
            ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0.0f, 0.0f));
        ImGui::Begin("DockSpace Demo", &dockspaceShow, window_flags);
        if (!opt_padding)
            ImGui::PopStyleVar();

        if (opt_fullscreen)
            ImGui::PopStyleVar(2);

        // Submit the DockSpace
        ImGuiIO& io = ImGui::GetIO();
        if (io.ConfigFlags & ImGuiConfigFlags_DockingEnable)
        {
            ImGuiID dockspace_id = ImGui::GetID("MyDockSpace");
            ImGui::DockSpace(dockspace_id, ImVec2(0.0f, 0.0f), dockspace_flags);
        }

        if (ImGui::BeginMenuBar())
        {
            if (ImGui::BeginMenu("File"))
            {
                if (ImGui::MenuItem("Close", "")) 
                {
                    Application::get().close();
                }

                ImGui::EndMenu();
            }

            ImGui::EndMenuBar();
        }

        ImGui::Begin("Settings");

        auto stats = Renderer2D::getStats();
        ImGui::Text("Renderer2D Stats:");
        ImGui::Text("Draw Calls: %d", stats.drawCalls);
        ImGui::Text("Quads: %d", stats.quadCount);
        ImGui::Text("Vertices: %d", stats.getTotalVertices());
        ImGui::Text("Indices: %d", stats.getTotalIndices());

        ImGui::ColorEdit4("Square Colour Picker", glm::value_ptr(_squareColour));

        uint32_t colourAttacheID = _framebuffer->getColourAttachmentRendererID();
        ImGui::Image((void*)colourAttacheID, ImVec2{ 1280, 720 }, ImVec2{ 0, 1 }, ImVec2{ 1, 0 });

        ImGui::End();

        ImGui::End();


    }

    bool EditorLayer::onKeyPressed(PressedKeyEvent& e)
    {
        switch (e.getKeyCode()) 
        {
        case TEMP_KEY_1:
            _mySource->play(_spellSoundBuffer);
            break;
        case TEMP_KEY_2:
            _mySource->play(_magicFailSoundBuffer);
            break;
        }

        return false;
    }

    bool EditorLayer::onKeyReleased(ReleasedKeyEvent& e) 
    {
        return false;
    }

}
