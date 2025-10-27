
int main(int argc, char* argv[]) {
    neu::file::SetCurrentDirectory("Assets");
    LOG_INFO("current directory {}", neu::file::GetCurrentDirectory());

    // initialize engine
    LOG_INFO("initialize engine...");
    neu::GetEngine().Initialize();

    // initialize scene

    SDL_Event e;
    bool quit = false;

    //model
    auto model3d = std::make_shared<neu::Model>();
    model3d->Load("models/spot.obj");

    //shader
    //auto vs = neu::Resources().Get<neu::Shader>("Shaders/basic_lit.vert", GL_VERTEX_SHADER);
    //auto fs = neu::Resources().Get<neu::Shader>("Shaders/basic_lit.frag", GL_FRAGMENT_SHADER);

	//program
	auto program = neu::Resources().Get<neu::Program>("shaders/basic_lit.prog");
    program->Use();

	//texture
	neu::res_t<neu::Texture> texture = neu::Resources().Get<neu::Texture>("textures/spot_diffuse.png");
	program->SetUniform("u_texture", 0);

    //lights
    program->SetUniform("u_ambient_light", glm::vec3{ 0.5f });
	neu::Transform light{ { 2, 4 , 3 } };
    
    //transform
    neu::Transform transform{ { 0, 0 ,0 } };
	neu::Transform camera{ { 0, 0 , 3 } };
  
    //projection matrix
    float aspect = (float)neu::GetEngine().GetRenderer().GetWidth() / (float)neu::GetEngine().GetRenderer().GetHeight();
    glm::mat4 projection = glm::perspective(glm::radians(60.0f), aspect, 0.01f, 100.0f);
    program->SetUniform("u_projection", projection);

    // MAIN LOOP
    while (!quit) {
        while (SDL_PollEvent(&e)) {
            if (e.type == SDL_EVENT_QUIT) {
                quit = true;
            }
        }

        // update
        neu::GetEngine().Update();
        float dt = neu::GetEngine().GetTime().GetDeltaTime();

        if (neu::GetEngine().GetInput().GetKeyPressed(SDL_SCANCODE_ESCAPE)) quit = true;

        transform.rotation.y += dt * 90;
        program->SetUniform("u_model", transform.GetMatrix());
        
        //view matrix

		if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_A)) camera.position.x += 1.0f * dt;
		if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_D)) camera.position.x -= 1.0f * dt;
		if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_W)) camera.position.z += 1.0f * dt;
		if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_S)) camera.position.z -= 1.0f * dt;
		if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_Q)) camera.position.y += 1.0f * dt;
		if (neu::GetEngine().GetInput().GetKeyDown(SDL_SCANCODE_E)) camera.position.y -= 1.0f * dt;

        glm::mat4 view = glm::lookAt(camera.position, camera.position + glm::vec3{ 0, 0, -1 }, glm::vec3{ 0, 1, 0 });
        program->SetUniform("u_view", view);

        program->SetUniform("u_light.color", glm::vec3{ 0, 0, 4 });
		light.position.x = neu::math::sin(neu::GetEngine().GetTime().GetTime()) * 3.0f;
		program->SetUniform("u_light.position", glm::vec3(view * glm::vec4(light.position, 1.0f)));

        // draw 
        neu::GetEngine().GetRenderer().Clear();
        // start new ImGui frame
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplSDL3_NewFrame();
        ImGui::NewFrame();
        // set ImGui
        ImGui::Begin("Editor");
        ImGui::Text("Hello World");
        ImGui::Text("Press 'Esc' to quit.");
        ImGui::End();
        model3d->Draw(GL_TRIANGLES);
        // draw ImGui
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

        neu::GetEngine().GetRenderer().Present();
    }

    neu::GetEngine().Shutdown();

    return 0;
}
