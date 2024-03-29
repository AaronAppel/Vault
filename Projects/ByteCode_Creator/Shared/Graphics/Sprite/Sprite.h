#ifndef __Sprite_H__
#define __Sprite_H__

class Mesh;
class ShaderProgram;

class Sprite2D
{
public:
	Sprite2D();
	~Sprite2D();

	void Draw();

	void SetPosition(vec3 position) { m_Position = position; UpdateTransform(); };
	void SetScale(vec3 scale) { m_Scale = scale; UpdateTransform(); };
	void SetAngle(float angle) { m_Angle = angle; UpdateTransform(); };

	void SetTexture(GLuint texture) { m_TextureID = texture; };
	void SetMesh(Mesh* mesh) { m_Mesh = mesh; };
	void SetShader(ShaderProgram* shader) { m_Shader = shader; m_Mesh->SetupShaderAttributes(m_Shader); };

private:
	void UpdateTransform();

	vec3 m_Position = 0; // #TODO Consider using a vec2 instead
	vec3 m_Scale = 1;
	float m_Angle = 0;

	GLuint m_TextureID = NULL;

	ShaderProgram* m_Shader = nullptr;
	Mesh* m_Mesh = nullptr;
	mat4* m_Transform = nullptr;
};

#endif //__Sprite_H__
