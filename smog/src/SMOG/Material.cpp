#include <SMOG/Material.h>
#include <SMOG/ShaderCache.h>
#include <SMOG/TextureCache.h>

#include <json/json.h>
#include <fstream>


SMOG_NAMESPACE_ENTER
{
	std::string MaterialValue::typeName(Type type)
	{
		switch(type)
		{
			case kFloat:
				return "float";
			case kRGB:
				return "rgb";
			case kTexture:
				return "texture";
			default:
				ERROR("Unrecognised MaterialValue::Type");
		}
	}

	Material Material::Load(const std::string& filename)
	{
		Material material;
		material.load(filename);
		return material;
	}

	Material::Material()
	{

	}

	void Material::load(const std::string& filename)
	{
		std::ifstream in(filename);
		if (!in.is_open())
		{
			ERROR("Failed to load material " + filename);
		}
		Json::Value material;
		in >> material;
		in.close();

		Json::Value vertex_shader = material["vertex_shader"];
		Json::Value fragment_shader = material["fragment_shader"];

		if (!vertex_shader.isNull())
		{
			m_vertexShader = vertex_shader.asString();
		}
		else
		{
			WARN("Warning: Failed to find vertex shader in material " + filename);
		}
		if (!fragment_shader.isNull())
		{
			m_fragmentShader = fragment_shader.asString();
		}
		else
		{
			WARN("Warning: Failed to find fragment shader in material " + filename);
		}
		tryCompileProgram();

		Json::Value values = material["values"];
		Json::Value::Members members = values.getMemberNames();
		for (Json::Value::Members::const_iterator it = members.begin(); it != members.end(); ++it)
		{			
			Json::Value value = values[*it];
			std::string type = value["type"].asString();
			if (type == "float")
			{
				set(*it, value["value"].asFloat());
			}
			else if (type == "rgb")
			{
				RGB rgb;
				rgb.r = value["r"].asFloat();
				rgb.g = value["g"].asFloat();
				rgb.b = value["b"].asFloat();
				set(*it, rgb);
			}
			else if (type == "texture")
			{
				set(*it, TextureCache::Load(value["filename"].asString()));
			}
		}
		apply();
	}

	void Material::save(const std::string& filename) const
	{
		Json::Value material;
		material["vertex_shader"] = m_vertexShader;
		material["fragment_shader"] = m_fragmentShader;
		Json::Value values;
		for (ValueMap::const_iterator it = m_valueMap.begin(); it != m_valueMap.end(); ++it)
		{
			Json::Value value;
			RGB rgb;
			switch(it->second->type())
			{
				case MaterialValue::kFloat:
					value["type"] = "float";
					value["value"] = it->second->as<float>()->value;
					break;
				case MaterialValue::kRGB:
					value["type"] = "rgb";
					rgb = it->second->as<RGB>()->value;
					value["r"] = rgb.r;
					value["g"] = rgb.g;
					value["b"] = rgb.b;
					break;
				case MaterialValue::kTexture:
					value["type"] = "texture";
					value["filename"] = it->second->as<TextureFile>()->value.filename();
					break;
				default:
					break;
			}
			values[it->first] = value;
		}
		material["values"] = values;
		std::ofstream out(filename, std::ofstream::out);
		out << material;
		out.close();
	}

	void Material::setVertexShader(const std::string& vertexShader)
	{
		m_vertexShader = vertexShader;
		tryCompileProgram();
	}

	void Material::setFragmentShader(const std::string& fragmentShader)
	{
		m_fragmentShader = fragmentShader;
		tryCompileProgram();
	}

	ShaderProgram& Material::program()
	{
		return m_program;
	}

	const ShaderProgram& Material::program() const
	{
		return m_program;
	}

	void Material::set(const std::string& name, float value)
	{
		m_valueMap[name] = std::unique_ptr<MaterialValue>(new TypedMaterialValue<float>(value));
	}

	void Material::set(const std::string& name, const RGB& value)
	{
		m_valueMap[name] = std::unique_ptr<MaterialValue>(new TypedMaterialValue<RGB>(value));
	}

	void Material::set(const std::string& name, const TextureFile& texture)
	{
		m_valueMap[name] = std::unique_ptr<MaterialValue>(new TypedMaterialValue<TextureFile>(texture));
	}

	void Material::apply() const
	{
		m_program.use();
		for (ValueMap::const_iterator it = m_valueMap.begin(); it != m_valueMap.end(); ++it)
		{
			switch(it->second->type())
			{
				case MaterialValue::kFloat:
					m_program.set(it->first, it->second->as<float>()->value);
					break;
				case MaterialValue::kRGB:
					m_program.set(it->first, it->second->as<RGB>()->value);
					break;
				case MaterialValue::kTexture:
					m_program.set(it->first, it->second->as<TextureFile>()->value);
					break;
				default:
					break;
			}
		}
	}

	void Material::tryCompileProgram()
	{
		if (!m_vertexShader.empty() && !m_fragmentShader.empty())
		{
			m_program.clear();
			m_program.attach(ShaderCache::Load(m_vertexShader, Shader::kVertex));
			m_program.attach(ShaderCache::Load(m_fragmentShader, Shader::kFragment));
			m_program.link();
		}
	}
}