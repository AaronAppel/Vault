#include "Game.h"

#include "../Libraries/glew/GL/glew.h"
#include "../Libraries/glfw/GLFW/glfw3.h"
#include "../Libraries/imgui/imgui.h"
#include "../Libraries/imgui/imgui_impl_glfw_gl3.h"

void DisplayItems(std::vector<Item*> item, int numItems);
void DisplayCharacters(std::vector<Character*> chars, int numChars);
void DisplayUpdateFiles();

void RecompileFiles();

Interpreter g_Inter; // TODO: No globals!
std::vector<Item*> items;
std::vector<Character*> characters;
std::vector<std::string> itemFiles;
std::vector<std::string> characterFiles;

// Item files are .item, character files are .char
const char* itemDir = "Data/Items/";
const char* charDir = "Data/Characters/";

#define COLOR_WHITE 1,1,1,1

int main()
{
	const int width = 640, height = 360;
    GLFWwindow* window = Setup("ByteCode Game", width, height);
    glClearColor(COLOR_WHITE);

    itemFiles = ReadDir(itemDir);
    characterFiles = ReadDir(charDir);

    for (int i = 0; i < itemFiles.size(); i++)
    {
        Item* temp = g_Inter.InterperateItem(itemFiles[i].c_str());
        items.push_back(temp);
    }

    for (int i = 0; i < characterFiles.size(); i++)
    {
        Character* temp = g_Inter.InterperateCharacter(characterFiles[i].c_str());
        characters.push_back(temp);
    }

    ShaderProgram shader;
	shader.Init("Data/Shaders/Sprite2D.vert", "Data/Shaders/Sprite2D.frag", NULL);

    MeshFactory t_MeshFactory;
    Mesh* mesh = t_MeshFactory.CreateBox(vec2(0.5f, 0.5f));

    const GLenum texture = Load2DTexture("Data/Textures/null_texture.png", false);

    Sprite2D* sprite = new Sprite2D(); // Example image display

    sprite->SetPosition(vec3(0, 0, 0));
    sprite->SetScale(vec3(1,1,1)/2);
    sprite->SetMesh(mesh);
    sprite->SetShader(&shader);
    sprite->SetTexture(texture);

    while (!glfwWindowShouldClose(window))
    {
        /* input */
        glfwPollEvents();
        ImGui_ImplGlfwGL3_NewFrame();

        /* logic */

        /* render */
        glClear(GL_COLOR_BUFFER_BIT);

        DisplayUpdateFiles();
        DisplayItems(items, itemFiles.size());
        DisplayCharacters(characters, characterFiles.size());

        sprite->Draw();

        ImGui::Render();
        ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());
        glfwSwapBuffers(window);
    }

    // #TODO Clean up allocations like mesh, shader, sprite, and texture
    return 0;
}

void DisplayItems(std::vector<Item*> item, int numItems)
{
    ImGui::Begin("Items");
    for (int i = 0; i < numItems; i++)
    {
        ImGui::Text(item[i]->GetName().c_str());
        ImGui::Text("Cost: %i", item[i]->GetCost());
        ImGui::Separator();
    }
    ImGui::End();
}

void DisplayCharacters(std::vector<Character*> chars, int numChars)
{
    ImGui::Begin("Characters");
    for (int i = 0; i < numChars; i++)
    {
        ImGui::Text(chars[i]->GetName().c_str());
        ImGui::Text("MaxEnergy: %i", chars[i]->GetMaxEnergy());
        ImGui::Separator();
    }
    ImGui::End();
}

void DisplayUpdateFiles()
{
    ImGui::Begin("Update Files");
    if (ImGui::Button("Recompile"))
        RecompileFiles();
    ImGui::End();
}

void RecompileFiles()
{
    // TODO: Determine whether an object has been altered or changed.
    // do not delete everything.

    // delete old items, characters
    int size = items.size();
    for (int i = 0; i < size; i++)
    {
        delete items[i];
    }
    size = characters.size();
    for (int i = 0; i < size; i++)
    {
        delete characters[i];
    }
    items.clear();
    characters.clear();

    itemFiles.clear();
    characterFiles.clear();

	// create new items, characters
    itemFiles = ReadDir(itemDir);
    characterFiles = ReadDir(charDir);

    for (int i = 0; i < itemFiles.size(); i++)
    {
        items.push_back(g_Inter.InterperateItem(itemFiles[i].c_str()));
    }
    for (int i = 0; i < characterFiles.size(); i++)
    {
        characters.push_back(g_Inter.InterperateCharacter(characterFiles[i].c_str()));
    }
}
