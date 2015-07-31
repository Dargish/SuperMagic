#include <SMOG/Material.h>

#include <json/json.h>
#include <fstream>
#include <iostream>
#include <stdexcept>


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
			default:
				throw std::runtime_error("Unrecognised MaterialValue::Type");
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
			throw std::runtime_error("Failed to load material " + filename);
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
			std::cerr << "Warning: Failed to find vertex shader in material " << filename << std::endl;
		}
		if (!fragment_shader.isNull())
		{
			m_fragmentShader = fragment_shader.asString();
		}
		else
		{
			std::cerr << "Warning: Failed to find fragment shader in material " << filename << std::endl;
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
			if (type == "rgb")
			{
				RGB rgb;
				rgb.r = value["r"].asFloat();
				rgb.g = value["g"].asFloat();
				rgb.b = value["b"].asFloat();
				set(*it, rgb);
			}
		}
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
		m_program.use();
		m_program.set(name, value);
	}

	void Material::set(const std::string& name, const RGB& value)
	{
		m_valueMap[name] = std::unique_ptr<MaterialValue>(new TypedMaterialValue<RGB>(value));
		m_program.use();
		m_program.set(name, value);
	}

	void Material::tryCompileProgram()
	{
		if (!m_vertexShader.empty() && !m_fragmentShader.empty())
		{
			m_program.clear();
			m_program.attach(Shader(m_vertexShader, Shader::kVertex));
			m_program.attach(Shader(m_fragmentShader, Shader::kFragment));
			m_program.link();
		}
	}
}